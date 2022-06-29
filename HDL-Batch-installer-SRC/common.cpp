/***************************************************************
 * Name:      common.cpp
 * Purpose:   General-purpose code used by HDLBinst
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-10-07
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include <string>

std::string DMA_TABLE[8]
{
    "*m0",
    "*m1",
    "*m2",
    "*u0",
    "*u1",
    "*u2",
    "*u3",
    "*u4",
};

std::string DMA_ALIAS[8]
{
    "MDMA 0",/// "*m0"
    "MDMA 1",/// "*m1"
    "MDMA 2",/// "*m2"
    "UDMA 0",/// "*u0"
    "UDMA 1",/// "*u1"
    "UDMA 2",/// "*u2"
    "UDMA 3",/// "*u3"
    "UDMA 4",/// "*u4"
};
