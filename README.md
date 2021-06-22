# HDL Batch installer


[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![project status](https://img.shields.io/badge/Project%20status-Active-00cc22)
[![wxWidgets version](https://img.shields.io/badge/wxWidgets-3.0.5-blue)](https://www.wxwidgets.org/downloads/#v3.0.5)

[![Release HDL Batch Installer](https://github.com/israpps/HDL-Batch-installer/actions/workflows/Repack-and-release.yml/badge.svg)](https://github.com/israpps/HDL-Batch-installer/actions/workflows/Repack-and-release.yml)
[![GitHub release (by tag)](https://img.shields.io/github/downloads/israpps/HDL-Batch-installer/Latest/total?label=Downloads%20%5BLatest%5D)](https://github.com/israpps/HDL-Batch-installer/releases)

#### A GUI for HDL Dump.

 Made by Matias Israelson (AKA:El_isra)

> Originally this was a personal project to practice C++ & give a try to wxWidgets...
>
> But at the end I decided to share it here on github.
When the project gets into a decent state I'll upload it to PSX-place

### Currently implemented features (unchecked elements are WIP)

----

- [x] Install multiple Games at once
- [x] Extract multiple Games at once
- [x] Automatically assign the original Game Title before Installation
- [X] Inject MiniOPL into the game partition (to launch the Game From HDD-OSD)
- [X] Inject MBR.KELF into the HDD
- [ ] Modify Partitions Header (custom title & icon and more)
- [ ] Edit Game Title

---


# Game Name Database:

Just like HDL Batch, this GUI will automatically search the Game Title for the PS2 ISO you're about to Install.

the program has an Internal Database with `14342` Game Titles!

however, you can use an external database Instead.

when the program can't find the Game Title on the Database (or the Database is disabled) the name of the ISO file will be Used Instead (without the extension)

#### If you find a Game ID that isn´t registered in our database Open a new [__Database Update Request__](https://github.com/israpps/HDL-Batch-installer/issues/new?assignees=&labels=Database+issue&template=database-update-request.md&title=Database+update+Request)

## Create Custom Database:


the sintax of the Database entry is:
```Bash
GAME_ID;GAMENAME
```
and the file must end with the line:
```
END_OF_DATABASE
```
the file must be named `gamename.DB`, and it must remain with the Program

an example of a simple databse with 3 games:
```bash
SLUS_201.47;Aliens vs Predator - Extinction
SLPM_551.98;Naxat Soft Reachmania Vol.1 - CR Galaxy Angel [Naxat Best]
XSPL_670.01;Wonder Zone
END_OF_DATABASE
```
