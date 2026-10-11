# HDL Batch Installer - CMake build
#
# Builds the same sources as HDL-Batch-installer-SRC/HDL-Batch-installer.cbp (Code::Blocks)
# with MinGW-w64 + wxWidgets 3.2 (MSW). Intended for CI and for contributors who don't use
# Code::Blocks.
#
# Typical use from an MSYS2 MINGW64 shell:
#   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-wxwidgets3.2-msw
#   cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
#   cmake --build build

cmake_minimum_required(VERSION 3.16)

if(NOT WIN32)
    message(FATAL_ERROR
        "HDL Batch Installer currently only builds for Windows (MinGW-w64).\n"
        "It links against the prebuilt Windows library external/libps2hdd.dll and uses Win32 "
        "APIs for physical drive enumeration (GetPhysicalDrives.cpp) and Dokan/PFSFuse for "
        "mounting partitions (DokanMan.cpp).")
endif()

project(HDL-Batch-installer LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
# The Code::Blocks Release target uses plain -O2 (no -DNDEBUG), keep the same behaviour.
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(HDLBINST_STATIC_WX "Link wxWidgets statically (needs a static wxWidgets build)" OFF)
option(HDLBINST_STATIC_RUNTIME "Link libgcc/libstdc++ statically (as the Code::Blocks targets do)" ON)

# ---------------------------------------------------------------- wxWidgets
if(HDLBINST_STATIC_WX)
    set(wxWidgets_USE_STATIC ON)
endif()
set(wxWidgets_USE_UNICODE ON)

# core + base only, same as the Code::Blocks project. If linking ever reports missing
# wxURL/wxSocket symbols, add "net" to this list.
# Asking for 3.2 here makes CMake itself reject anything older, using the version
# that FindwxWidgets reports.
find_package(wxWidgets 3.2 REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
message(STATUS "wxWidgets version: ${wxWidgets_VERSION_STRING}")

# ---------------------------------------------------------------- sources
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/HDL-Batch-installer-SRC)

set(HDLBINST_SOURCES
    # src/DnDFile.cpp is intentionally NOT built: it defines a global `class DnDFile` that
    # duplicates the one PFSShellBrowser.cpp defines locally for its own use (the one actually
    # instantiated, via "new DnDFile(FileList)"). include/DnDFile.h is included from
    # HDL_Batch_installerMain.cpp but that class is never used there either. Building both
    # files gives two definitions of DnDFile::OnDropFiles with external linkage -> link error.
    ${SRC_DIR}/About.cpp
    ${SRC_DIR}/ArtMan.cpp
    ${SRC_DIR}/Component_error.cpp
    ${SRC_DIR}/Config.cpp
    ${SRC_DIR}/CopyHDD.cpp
    ${SRC_DIR}/DokanMan.cpp
    ${SRC_DIR}/GetPhysicalDrives.cpp
    ${SRC_DIR}/HDDFomatMan.cpp
    ${SRC_DIR}/HDDManager.cpp
    ${SRC_DIR}/HDL_Batch_installerApp.cpp
    ${SRC_DIR}/HDL_Batch_installerMain.cpp
    ${SRC_DIR}/MD5Man.cpp
    ${SRC_DIR}/MD5Report.cpp
    ${SRC_DIR}/NDBMan.cpp
    ${SRC_DIR}/PFSShell.cpp
    ${SRC_DIR}/PFSShellBrowser.cpp
    ${SRC_DIR}/Post_Install_Report.cpp
    ${SRC_DIR}/UpdateMan.cpp
    ${SRC_DIR}/common.cpp
    ${SRC_DIR}/gamename/database.cpp
    ${SRC_DIR}/gamename/parser.cpp
    ${SRC_DIR}/hdl-dump-recodes.cpp
    ${SRC_DIR}/mkpartdlg.cpp
    # resource.rc pulls in wx/msw/wx.rc, the manifest, icon and splash image
    ${SRC_DIR}/resource.rc
)

# Console subsystem on purpose (no WIN32 keyword): the program prints coloured status
# text to its console, matching the Code::Blocks "console application" target type.
add_executable(HDL-Batch-installer ${HDLBINST_SOURCES})

target_include_directories(HDL-Batch-installer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SRC_DIR}/include
    ${SRC_DIR}          # also lets windres find gfx/ and manifest/ referenced by resource.rc
    ${SRC_DIR}/xpm      # PFSShellBrowser.cpp includes folder.xpm, new_dir.xpm, delete.xpm and
                        # toparent.xpm with <>; Code::Blocks found them in the wxWidgets source
                        # tree (${#wx}/art), here we use the copies kept in this folder
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(HDL-Batch-installer PRIVATE BITS=64)
    set(HDLBINST_PS2HDD ${SRC_DIR}/external/libps2hdd)
else()
    target_compile_definitions(HDL-Batch-installer PRIVATE BITS=32)
    set(HDLBINST_PS2HDD ${SRC_DIR}/external/libps2hdd-x86)
    set_target_properties(HDL-Batch-installer PROPERTIES OUTPUT_NAME HDL-Batch-installer-x86)
endif()

# libps2hdd.a is the MinGW import library for the prebuilt libps2hdd.dll
target_link_libraries(HDL-Batch-installer PRIVATE
    ${wxWidgets_LIBRARIES}
    ${HDLBINST_PS2HDD}.a
    wininet rpcrt4 winmm
)

if(HDLBINST_STATIC_RUNTIME)
    target_link_options(HDL-Batch-installer PRIVATE -static-libgcc -static-libstdc++)
endif()
target_link_options(HDL-Batch-installer PRIVATE $<$<CONFIG:Release>:-s>)

# The exe can't start without libps2hdd.dll next to it.
add_custom_command(TARGET HDL-Batch-installer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HDLBINST_PS2HDD}.dll $<TARGET_FILE_DIR:HDL-Batch-installer>
    COMMENT "Copying libps2hdd.dll next to the executable")
