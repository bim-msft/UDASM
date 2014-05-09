//
//  InstructionDef.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include "InstructionDef.h"

map<BYTE, string> InstructionDef::InitPrefix(BYTE GroupID)
{
    map<BYTE, string> RetVal;
    switch (GroupID) {
        case 0:
            RetVal[REPEAT_PREFIX_LOCK] = "lock";
            RetVal[REPEAT_PREFIX_REP] = "rep";
            RetVal[REPEAT_PREFIX_REPE] = "repe";
            RetVal[REPEAT_PREFIX_REPZ] = "repz";
            RetVal[REPEAT_PREFIX_REPNE] = "repne";
            RetVal[REPEAT_PREFIX_REPNZ] = "repnz";
            break;
        case 1:
            RetVal[SEGMENT_PREFIX_ES] = "es";
            RetVal[SEGMENT_PREFIX_CS] = "cs";
            RetVal[SEGMENT_PREFIX_SS] = "ss";
            RetVal[SEGMENT_PREFIX_DS] = "ds";
            RetVal[SEGMENT_PREFIX_FS] = "fs";
            RetVal[SEGMENT_PREFIX_GS] = "gs";
            break;
        case 2:
            RetVal[OPERAND_PREFIX] = "";
            break;
        case 3:
            RetVal[ADDRESS_PREFIX] = "";
            break;
        default:
            break;
    }
    return RetVal;
}

map<BYTE, string> InstructionDef::InitSinglePrefixName()
{
    map<BYTE, string> RetVal;
    RetVal[REPEAT_PREFIX_LOCK] = "prefix [lock]";
    RetVal[REPEAT_PREFIX_REP] = "prefix [rep]";
    RetVal[REPEAT_PREFIX_REPE] = "prefix [repe]";
    RetVal[REPEAT_PREFIX_REPZ] = "prefix [repz]";
    RetVal[REPEAT_PREFIX_REPNE] = "prefix [repne]";
    RetVal[REPEAT_PREFIX_REPNZ] = "prefix [repnz]";
    RetVal[SEGMENT_PREFIX_ES] = "prefix [es]";
    RetVal[SEGMENT_PREFIX_CS] = "prefix [cs]";
    RetVal[SEGMENT_PREFIX_SS] = "prefix [ss]";
    RetVal[SEGMENT_PREFIX_DS] = "prefix [ds]";
    RetVal[SEGMENT_PREFIX_FS] = "prefix [fs]";
    RetVal[SEGMENT_PREFIX_GS] = "prefix [gs]";
    RetVal[OPERAND_PREFIX] = "prefix [operand size switch]";
    RetVal[ADDRESS_PREFIX] = "prefix [address size switch]";
    return RetVal;
}

map<BYTE, string> InstructionDef::InitOpcode()
{
    map<BYTE, string> RetVal;
    RetVal[OPCODE_ADD] = "add";
    RetVal[OPCODE_PUSH_ES] = "push";
    RetVal[OPCODE_POP_ES] = "pop";
    RetVal[OPCODE_OR] = "or";
    RetVal[OPCODE_PUSH_CS] = "push";
    RetVal[OPCODE_POP_CS] = "pop";
    RetVal[OPCODE_ADC] = "adc";
    RetVal[OPCODE_PUSH_SS] = "push";
    RetVal[OPCODE_POP_SS] = "pop";
    RetVal[OPCODE_SBB] = "sbb";
    RetVal[OPCODE_PUSH_DS] = "push";
    RetVal[OPCODE_POP_DS] = "pop";
    RetVal[OPCODE_AND] = "and";
    RetVal[OPCODE_DAA] = "daa";
    RetVal[OPCODE_SUB] = "sub";
    RetVal[OPCODE_DAS] = "das";
    RetVal[OPCODE_XOR] = "xor";
    RetVal[OPCODE_AAA] = "aaa";
    RetVal[OPCODE_CMP] = "cmp";
    RetVal[OPCODE_AAS] = "aas";
    RetVal[OPCODE_INC] = "inc";
    RetVal[OPCODE_DEC] = "dec";
    RetVal[OPCODE_MOV] = "mov";
    RetVal[OPCODE_PUSH] = "push";
    RetVal[OPCODE_POP] = "pop";
    RetVal[OPCODE_PUSH_I16_I32] = "push";
    RetVal[OPCODE_NOP] = "nop";
    return RetVal;
}

map<BYTE, string> InstructionDef::InitReg(BYTE GroupID)
{
    map<BYTE, string> RetVal;
    switch (GroupID)
    {
        case REGSIZE_8:
            RetVal[REG_AL_8] = "al";
            RetVal[REG_CL_8] = "cl";
            RetVal[REG_DL_8] = "dl";
            RetVal[REG_BL_8] = "bl";
            RetVal[REG_AH_8] = "ah";
            RetVal[REG_CH_8] = "ch";
            RetVal[REG_DH_8] = "dh";
            RetVal[REG_BH_8] = "bh";
            break;
        case REGSIZE_16:
            RetVal[REG_AX_16] = "ax";
            RetVal[REG_CX_16] = "cx";
            RetVal[REG_DX_16] = "dx";
            RetVal[REG_BX_16] = "bx";
            RetVal[REG_SP_16] = "sp";
            RetVal[REG_BP_16] = "bp";
            RetVal[REG_SI_16] = "si";
            RetVal[REG_DI_16] = "di";
            break;
        case REGSIZE_32:
            RetVal[REG_EAX_32] = "eax";
            RetVal[REG_ECX_32] = "ecx";
            RetVal[REG_EDX_32] = "edx";
            RetVal[REG_EBX_32] = "ebx";
            RetVal[REG_ESP_32] = "esp";
            RetVal[REG_EBP_32] = "ebp";
            RetVal[REG_ESI_32] = "esi";
            RetVal[REG_EDI_32] = "edi";
            break;
        case ADDRESSSIZE_16:
            RetVal[REG_ADDRESS16_BX_SI] = "bx + si";
            RetVal[REG_ADDRESS16_BX_DI] = "bx + di";
            RetVal[REG_ADDRESS16_BP_SI] = "bp + si";
            RetVal[REG_ADDRESS16_BP_DI] = "bp + di";
            RetVal[REG_ADDRESS16_BX] = "bx";
            RetVal[REG_ADDRESS16_BP] = "bp";
            RetVal[REG_ADDRESS16_SI] = "si";
            RetVal[REG_ADDRESS16_DI] = "di";
            break;
        case SEGMENT_REG:
            RetVal[REG_CS] = "cs";
            RetVal[REG_DS] = "ds";
            RetVal[REG_ES] = "es";
            RetVal[REG_FS] = "fs";
            RetVal[REG_GS] = "gs";
            RetVal[REG_SS] = "ss";
            break;
        default:
            break;
    }
    return RetVal;
}

map<BYTE, string> InstructionDef::InitAddressHead()
{
    map<BYTE, string> RetVal;
    RetVal[ADDRESSHEAD_8] = "byte ptr";
    RetVal[ADDRESSHEAD_16] = "word ptr";
    RetVal[ADDRESSHEAD_32] = "dword ptr";
    return RetVal;
}

map<BYTE, string>& InstructionDef::GetPrefix(BYTE GroupID)
{
    return InstructionDef::Prefix[GroupID];
}

map<BYTE, string>& InstructionDef::GetSinglePrefixName()
{
    return InstructionDef::SinglePrefixName;
}

map<BYTE, string>& InstructionDef::GetOpcode()
{
    return InstructionDef::Opcode;
}

map<BYTE, string>& InstructionDef::GetReg(BYTE GroupID)
{
    return InstructionDef::Reg[GroupID];
}

map<BYTE, string>& InstructionDef::GetAddressHead()
{
    return InstructionDef::AddressHead;
}

map<BYTE, string> InstructionDef::Prefix[4];
map<BYTE, string> InstructionDef::SinglePrefixName;
map<BYTE, string> InstructionDef::Opcode;
map<BYTE, string> InstructionDef::Reg[5];
map<BYTE, string> InstructionDef::AddressHead;



