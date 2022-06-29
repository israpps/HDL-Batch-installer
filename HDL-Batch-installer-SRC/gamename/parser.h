/***************************************************************
 * Name:      parser.h
 * Purpose:   Code for Internal database parsing
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-03-31
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/macro-vault.h"
#include "database.h"
using namespace std;
std::string get_gamename(std::string ELF,int workingmode,bool database_enabled);
#endif // PARSER_H_INCLUDED
