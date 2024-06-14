/***************************************************************
 * Name:      parser.cpp
 * Purpose:   Code for Internal database parsing
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-03-31
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#include "parser.h"
std::string get_gamename(std::string ELF,int workingmode,bool database_enabled)
{
    bool external_db_fail = false;
    COLOR(08) cout << "> searching [" <<ELF<<"]\n";
    COLOR(07)
    if (database_enabled == false)
        return NO_MATCH;

    if (workingmode == DB_EXTERNAL)
    {
        std::ifstream file;
        file.open("gamename.DB");
        int line_numbr = 0;
        std::string str, ret;

        if ( file.fail() )
        {
            external_db_fail = true;
            COLOR(0c) cout << "ERROR, can't access external database (gamename.DB)...\n";
            COLOR(08) cout << "$ Switching to internal database\n";
            COLOR(07)
            goto EXTERNAL_DATABASE_ACCESS_FAILED;
        }

        while (std::getline(file, str))
        {
            line_numbr++;
            if (str.find("END_OF_DATABASE") != std::string::npos)
                return NO_MATCH;

            if (str[0]=='#')///skip lines that start with '#' on external database
                continue;

            if (str.find(DATABASE_SPLIT_TOKEN) == std::string::npos)
            {
                COLOR(0e) std::cout << "Warning, missing split token at external database line [" << line_numbr <<"], skipping entry...\n";
                COLOR(07) continue;
            }

            if (str.substr(0,str.find_first_of(DATABASE_SPLIT_TOKEN)) == ELF)
            {
                COLOR(08)
                cout << "$ found match! [" << str.substr(str.find_first_of(DATABASE_SPLIT_TOKEN) + 1) << "]\n";
                COLOR(07)
                return str.substr(str.find_first_of(DATABASE_SPLIT_TOKEN) + 1);
            }
        }
    }
EXTERNAL_DATABASE_ACCESS_FAILED:

    if (workingmode == DB_INTERNAL || external_db_fail)
    {
        std::string S = GameNameDB[ELF];
        if (S == "") {
            return NO_MATCH;
        } else {
            return S;
        }
    }
    return NO_MATCH;///if nothing worked, assume that there was no match
}
