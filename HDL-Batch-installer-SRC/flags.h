/***************************************************************
 * Name:      Component_error.h
 * Purpose:   Flags
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef FLAGS_H_INCLUDED
#define FLAGS_H_INCLUDED

enum HDLAPP
{
    REDIRECT_OUTPUT = 1 << 0, // binary 0001
    IS_FIRST_INIT = 1 << 1, // binary 0010
    /*C = 1 << 2, // binary 0100
    D = 1 << 3  // binary 1000
    //*/
};
enum HDLFRAME
{
    FORCE_HIGH_DEBUG_LEVEL = 1 << 0,
};
#endif // FLAGS_H_INCLUDED
