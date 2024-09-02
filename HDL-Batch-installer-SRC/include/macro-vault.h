/***************************************************************
 * Name:      macro-vault.h
 * Purpose:   Code for Multiple macro definitions used along all the program
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-03-31
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#ifndef MACRO_VAULT
#define MACRO_VAULT
#define ISRA_WINDOWS
#ifdef ISRA_WINDOWS
#include <windows.h>
#include <iostream>
#include <string>
#define COLOR_INT(args)     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),args);
#define COLOR(args)         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),std::stoi(#args,0,16));
#else
#define COLOR_INT(args)
#define COLOR(args)
#endif //ISRA_WINDOWS


///disc media identifiers
#define MEDIA_DVD 0
#define MEDIA_CD 1


//------------------------------------------Debug
#ifdef INTERNAL_LOG
#define ACTIVATE_DEBUG_LOG() wxStreamToTextRedirector redirect(DEBUG);
#else
#define ACTIVATE_DEBUG_LOG()
#endif
//------------------------------------------

///hdl_silent.h || hdl_silent.cpp
#define NO_MATCH "///"
#define DATABASE_SPLIT_TOKEN ";"

#define DB_INTERNAL 0
#define DB_EXTERNAL 1

#define NOT_FOUND std::string::npos
#define RD3S(CURRENT, TOTAL) ((CURRENT*100)/TOTAL) // regla de tres simples

#endif //MACRO_VAULT
