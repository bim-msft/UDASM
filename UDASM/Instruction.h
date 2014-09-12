//
//  Instruction.h
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#ifndef __UDASM__Instruction__
#define __UDASM__Instruction__

#include "Intelx86Def.h"

#define NULL_VAL 0x00

class Instruction
{
private:
    BYTE RepeatPrefix;
    BYTE SegmentPrefix;
    BYTE OperandPrefix;
    BYTE AddressPrefix;
    DWORD Opcode;
    BYTE ModeRM;
    BYTE SIB;
    DWORD Displacement;
    DWORD Immediate;
    
public:
    Instruction();
    Instruction(BYTE *);
    ~Instruction();
    
    void Clear();
    
    void SetRepeatPrefix(BYTE);
    void SetSegmentPrefix(BYTE);
    void SetOperandPrefix(BYTE);
    void SetAddressPrefix(BYTE);
    void SetOpcode(DWORD);
    void SetModeRM(BYTE);
    void SetSIB(BYTE);
    void SetDisplacement(DWORD);
    void SetImmediate(DWORD);
    
    BYTE GetRepeatPrefix();
    BYTE GetSegmentPrefix();
    BYTE GetOperandPrefix();
    BYTE GetAddressPrefix();
    DWORD GetOpcode();
    BYTE GetModeRM();
    BYTE GetSIB();
    DWORD GetDisplacement();
    DWORD GetImmediate();
};

#endif /* defined(__UDASM__Instruction__) */
