//
//  main.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include <iostream>
#include "DASM.h"

void OutputVersionInfo()
{
    cout << "---------------------------------------------" << endl;
    cout << "Uranux Disassembler (UDASM) 1.2 " << endl;
    cout << "Author: uranux1993@163.com      " << endl;
    cout << "Copyright 2014 Uranux, All Rights Reserved" << endl;
    cout << "---------------------------------------------" << endl;
}

int main(int argc, const char **argv)
{
    OutputVersionInfo();
    if (argc != 13)
    {
        cout << "Arguments Error!" << endl;
        return -1;
    }
    
    string Arch = argv[1];
    BYTE Arch_;
    if (Arch == "INTEL_X86")
        Arch_ = INTEL_X86;
    else if (Arch == "AT_AND_T")
        Arch_ = AT_AND_T;
    else
    {
        cout << "Hardware Architecture \"" << Arch << "\" Not Supported!" << endl;
        return -1;
    }
    
    string CPUMode = argv[2];
    BYTE CPUMode_;
    if (CPUMode == "CPU_MODE_16")
        CPUMode_ = CPU_MODE_16;
    else if (CPUMode == "CPU_MODE_32")
        CPUMode_ = CPU_MODE_32;
    else
    {
        cout << "CPU Working Mode \"" << CPUMode << "\" Not Supported!" << endl;
        return -1;
    }
    
    string AddressMode = argv[3];
    BYTE AddressMode_;
    if (AddressMode == "ADDRESS_MODE_16")
        AddressMode_ = ADDRESS_MODE_16;
    else if (AddressMode == "ADDRESS_MODE_32")
        AddressMode_ = ADDRESS_MODE_32;
    else
    {
        cout << "CPU Addressing Mode \"" << AddressMode << "\" Not Supported!" << endl;
        return -1;
    }
    
    string ByteOrder = argv[4];
    BYTE ByteOrder_;
    if (ByteOrder == "UDASM_LITTLE_ENDIAN")
        ByteOrder_ = UDASM_LITTLE_ENDIAN;
    else if (ByteOrder == "UDASM_BIG_ENDIAN")
        ByteOrder_ = UDASM_BIG_ENDIAN;
    else
    {
        cout << "Byte Order \"" << ByteOrder << "\" Not Supported!" << endl;
        return -1;
    }
    
    cout << Arch << endl;
    cout << CPUMode << endl;
    cout << AddressMode << endl;
    cout << ByteOrder << endl;
    
    string InputFileName = argv[5];
    string OutputAddrFileName = argv[6];
    string OutputBinFileName = argv[7];
    string OutputAsmFileName = argv[8];
    DWORD ImageLoadAddress = atoi(argv[9]);
    DWORD TextSectionRawDataAddress = atoi(argv[10]);
    DWORD TextSectionRawDataLen = atoi(argv[11]);
    DWORD TextSectionLoadAddress = atoi(argv[12]);
    
    cout << InputFileName << endl;
    cout << "0x";
    cout << setiosflags(ios::uppercase) << setfill('0') << right << setw(8) << hex << ImageLoadAddress + TextSectionLoadAddress;
    cout << "~0x";
    cout << setiosflags(ios::uppercase) << setfill('0') << right << setw(8) << hex << ImageLoadAddress + TextSectionLoadAddress + TextSectionRawDataLen << endl;
    cout << "---------------------------------------------" << endl;
    
    DASM *UDASM = new DASM(Arch_,              // Hardware Architecture (Intel x86 / AT&T)
                           CPUMode_,           // CPU Working Mode (16 / 32)
                           AddressMode_,       // CPU Addressing Mode (16 / 32)
                           ByteOrder_,         // Byte Order (Little Endian / Big Endian)
                           InputFileName,      // Binary File for Disassemble
                           OutputAddrFileName, // Output File : Address
                           OutputBinFileName,  // Output File : Binary (In Hex)
                           OutputAsmFileName,  // Output File : Assembly
                           ImageLoadAddress,        // The Loaded Address of Input Executable File (IEF)(In Dec)
                           TextSectionRawDataAddress,      // The Start of Text-Segment Offset Address of IEF (In Dec)
                           TextSectionRawDataLen,     // The End of Text-Segment Offset Address of IEF (In Dec)
                           TextSectionLoadAddress
                           );
    
    UDASM->Disassemble(); // Do Disassembly
    
    delete UDASM;
    
    return 0;
}

