//
//  main.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include <iostream>
#include "DASM.h"

int main(int argc, const char **argv)
{
    if (argc != 12)
    {
        return -1;
    }
    
    string Arch = argv[1];
    BYTE Arch_;
    if (Arch == "INTEL_X86")
        Arch_ = INTEL_X86;
    else if (Arch == "AT_AND_T")
        Arch_ = AT_AND_T;
    else
        return -1;
    
    string CPUMode = argv[2];
    BYTE CPUMode_;
    if (CPUMode == "CPU_MODE_16")
        CPUMode_ = CPU_MODE_16;
    else if (CPUMode == "CPU_MODE_32")
        CPUMode_ = CPU_MODE_32;
    else
        return -1;
    
    string AddressMode = argv[3];
    BYTE AddressMode_;
    if (AddressMode == "ADDRESS_MODE_16")
        AddressMode_ = ADDRESS_MODE_16;
    else if (AddressMode == "ADDRESS_MODE_32")
        AddressMode_ = ADDRESS_MODE_32;
    else
        return -1;
    
    string ByteOrder = argv[4];
    BYTE ByteOrder_;
    if (ByteOrder == "UDASM_LITTLE_ENDIAN")
        ByteOrder_ = UDASM_LITTLE_ENDIAN;
    else if (ByteOrder == "UDASM_BIG_ENDIAN")
        ByteOrder_ = UDASM_BIG_ENDIAN;
    else
        return -1;
    
    string InputFileName = argv[5];
    string OutputAddrFileName = argv[6];
    string OutputBinFileName = argv[7];
    string OutputAsmFileName = argv[8];
    DWORD LoadAddress = atoi(argv[9]);
    DWORD OffsetAddress = atoi(argv[10]);
    DWORD OffsetAddressEnd = atoi(argv[11]);
    
    DASM *UDASM = new DASM(Arch_, CPUMode_, AddressMode_, ByteOrder_, InputFileName, OutputAddrFileName, OutputBinFileName, OutputAsmFileName, LoadAddress, OffsetAddress, OffsetAddressEnd);
    UDASM->Disassemble();
    delete UDASM;
    return 0;
}

