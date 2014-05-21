//
//  BaseDef.h
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#ifndef UDASM_BaseDef_h
#define UDASM_BaseDef_h

#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#define MAKE_WORD(A, B) (((A) << 8) + B)
#define MAKE_DWORD_2(A, B) (((A) << 16) + B)
#define MAKE_DWORD_4(A, B, C, D) (((MAKE_WORD(A, B)) << 16) + (MAKE_WORD(C, D)))
#define GET_1ST_BYTE_FROM_WORD(A) ((A) >> 8)
#define GET_2ND_BYTE_FROM_WORD(A) ((A) & 0x00FF)
#define GET_1ST_BYTE_FROM_DWORD(A) ((A) >> 24)
#define GET_2ND_BYTE_FROM_DWORD(A) ((A) >> 16)
#define GET_3RD_BYTE_FROM_DWORD(A) ((A) >> 8)
#define GET_4TH_BYTE_FROM_DWORD(A) ((A) & 0x000000FF)
#define GET_1ST_BIT(A) ((A) >> 7)
#define GET_2ND_BIT(A) (((A) >> 6) & 0x01)
#define GET_3RD_BIT(A) (((A) >> 5) & 0x01)
#define GET_4TH_BIT(A) (((A) >> 4) & 0x01)
#define GET_5TH_BIT(A) (((A) >> 3) & 0x01)
#define GET_6TH_BIT(A) (((A) >> 2) & 0x01)
#define GET_7TH_BIT(A) (((A) >> 1) & 0x01)
#define GET_8TH_BIT(A) ((A) & 0x01)

#define NULL_STR ""


#endif
