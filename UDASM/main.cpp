//
//  main.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include <iostream>
#include "DASM.h"

int main(int argc, const char * argv[])
{
    DASM *UDASM = new DASM("/Users/uranux/putty.exe", 0x00400000, 0x00001000, INTEL_X86, CPU_MODE_32, ADDRESS_MODE_32, UDASM_LITTLE_ENDIAN);
    delete UDASM;
    return 0;
}

