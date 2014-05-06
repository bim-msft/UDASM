//
//  Instruction.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include "Instruction.h"

Instruction::Instruction()
{
    this->Clear();
}

Instruction::Instruction(BYTE *Val)
{
    this->SetRepeatPrefix(Val[0]);
    this->SetSegmentPrefix(Val[1]);
    this->SetOperandPrefix(Val[2]);
    this->SetAddressPrefix(Val[3]);
    this->SetOpcode(MAKE_DWORD_4(Val[4], Val[5], Val[6], Val[7]));
    this->SetModeRM(Val[8]);
    this->SetSIB(Val[9]);
    this->SetDisplacement(MAKE_DWORD_4(Val[10], Val[11], Val[12], Val[13]));
    this->SetImmediate(MAKE_DWORD_4(Val[14], Val[15], Val[16], Val[17]));
}

Instruction::~Instruction()
{
    
}

void Instruction::Clear()
{
    this->SetRepeatPrefix(NULL_VAL);
    this->SetSegmentPrefix(NULL_VAL);
    this->SetOperandPrefix(NULL_VAL);
    this->SetAddressPrefix(NULL_VAL);
    this->SetOpcode(NULL_VAL);
    this->SetModeRM(NULL_VAL);
    this->SetSIB(NULL_VAL);
    this->SetDisplacement(NULL_VAL);
    this->SetImmediate(NULL_VAL);
}

void Instruction::SetRepeatPrefix(BYTE Val)
{
    this->RepeatPrefix = Val;
}

void Instruction::SetSegmentPrefix(BYTE Val)
{
    this->SegmentPrefix = Val;
}

void Instruction::SetOperandPrefix(BYTE Val)
{
    this->OperandPrefix = Val;
}

void Instruction::SetAddressPrefix(BYTE Val)
{
    this->AddressPrefix = Val;
}

void Instruction::SetOpcode(DWORD Val)
{
    this->Opcode = Val;
}

void Instruction::SetModeRM(BYTE Val)
{
    this->ModeRM = Val;
}

void Instruction::SetSIB(BYTE Val)
{
    this->SIB = Val;
}

void Instruction::SetDisplacement(DWORD Val)
{
    this->Displacement = Val;
}

void Instruction::SetImmediate(DWORD Val)
{
    this->Immediate = Val;
}

BYTE Instruction::GetRepeatPrefix()
{
    return this->RepeatPrefix;
}

BYTE Instruction::GetSegmentPrefix()
{
    return this->SegmentPrefix;
}

BYTE Instruction::GetOperandPrefix()
{
    return this->OperandPrefix;
}

BYTE Instruction::GetAddressPrefix()
{
    return this->AddressPrefix;
}

DWORD Instruction::GetOpcode()
{
    return this->Opcode;
}

BYTE Instruction::GetModeRM()
{
    return this->ModeRM;
}

BYTE Instruction::GetSIB()
{
    return this->SIB;
}

DWORD Instruction::GetDisplacement()
{
    return this->Displacement;
}

DWORD Instruction::GetImmediate()
{
    return this->Immediate;
}