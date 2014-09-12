//
//  Intelx86Def.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include "Intelx86Def.h"

map<BYTE, string> Intelx86Def::InitPrefix(BYTE GroupID)
{
    map<BYTE, string> RetVal;
    switch (GroupID) {
        case 0:
            RetVal[REPEAT_PREFIX_LOCK] = "LOCK";
            RetVal[REPEAT_PREFIX_REP] = "REP";
            //RetVal[REPEAT_PREFIX_REPE] = "REPE";
            //RetVal[REPEAT_PREFIX_REPZ] = "REPZ";
            RetVal[REPEAT_PREFIX_REPNE] = "REPNE";
            //RetVal[REPEAT_PREFIX_REPNZ] = "REPNZ";
            break;
        case 1:
            RetVal[SEGMENT_PREFIX_ES] = "ES";
            RetVal[SEGMENT_PREFIX_CS] = "CS";
            RetVal[SEGMENT_PREFIX_SS] = "SS";
            RetVal[SEGMENT_PREFIX_DS] = "DS";
            RetVal[SEGMENT_PREFIX_FS] = "FS";
            RetVal[SEGMENT_PREFIX_GS] = "GS";
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

map<BYTE, string> Intelx86Def::InitSinglePrefixName()
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

map<BYTE, string> Intelx86Def::InitOpcode()
{
    map<BYTE, string> RetVal;
    RetVal[OPCODE_ADD] = "ADD";
    RetVal[OPCODE_PUSH_ES] = "PUSH";
    RetVal[OPCODE_POP_ES] = "POP";
    RetVal[OPCODE_OR] = "OR";
    RetVal[OPCODE_PUSH_CS] = "PUSH";
    
    RetVal[OPCODE_ADC] = "ADC";
    RetVal[OPCODE_PUSH_SS] = "PUSH";
    RetVal[OPCODE_POP_SS] = "POP";
    RetVal[OPCODE_SBB] = "SBB";
    RetVal[OPCODE_PUSH_DS] = "PUSH";
    RetVal[OPCODE_POP_DS] = "POP";
    RetVal[OPCODE_AND] = "AND";
    RetVal[OPCODE_DAA] = "DAA";
    RetVal[OPCODE_SUB] = "SUB";
    RetVal[OPCODE_DAS] = "DAS";
    RetVal[OPCODE_XOR] = "XOR";
    RetVal[OPCODE_AAA] = "AAA";
    RetVal[OPCODE_CMP] = "CMP";
    RetVal[OPCODE_AAS] = "AAS";
    RetVal[OPCODE_INC] = "INC";
    RetVal[OPCODE_DEC] = "DEC";
    RetVal[OPCODE_PUSH] = "PUSH";
    RetVal[OPCODE_POP] = "POP";
    RetVal[OPCODE_PUSH_I16_I32] = "PUSH";
    RetVal[OPCODE_IMUL_I16_I32_3OP] = "IMUL";
    RetVal[OPCODE_PUSH_I8] = "PUSH";
    RetVal[OPCODE_IMUL_I8_3OP] = "IMUL";
    RetVal[OPCODE_INS] = "INS";
    RetVal[OPCODE_OUTS] = "OUTS";
    RetVal[OPCODE_JO] = "JO";
    RetVal[OPCODE_JNO] = "JNO";
    RetVal[OPCODE_JB] = "JB";
    RetVal[OPCODE_JNB] = "JNB";
    RetVal[OPCODE_JE] = "JE";
    RetVal[OPCODE_JNE] = "JNE";
    RetVal[OPCODE_JBE] = "JBE";
    RetVal[OPCODE_JA] = "JA";
    RetVal[OPCODE_JS] = "JS";
    RetVal[OPCODE_JNS] = "JNS";
    RetVal[OPCODE_JPE] = "JPE";
    RetVal[OPCODE_JPO] = "JPO";
    RetVal[OPCODE_JL] = "JL";
    RetVal[OPCODE_JGE] = "JGE";
    RetVal[OPCODE_JLE] = "JLE";
    RetVal[OPCODE_JG] = "JG";
    RetVal[OPCODE_TEST] = "TEST";
    RetVal[OPCODE_XCHG] = "XCHG";
    RetVal[OPCODE_MOV] = "MOV";
    RetVal[OPCODE_LEA] = "LEA";
    RetVal[OPCODE_POP_RM16_RM32] = "POP";
    RetVal[OPCODE_NOP] = "NOP";
    RetVal[OPCODE_XCHG_RAX_R] = "XCHG";
    RetVal[OPCODE_CWDE] = "CWDE";
    RetVal[OPCODE_CDQ] = "CDQ";
    RetVal[OPCODE_CALL_FAR] = "CALL";
    RetVal[OPCODE_WAIT] = "WAIT";
    RetVal[OPCODE_PUSHFD] = "PUSHFD";
    RetVal[OPCODE_POPFD] = "POPFD";
    RetVal[OPCODE_SAHF] = "SAHF";
    RetVal[OPCODE_LAHF] = "LAHF";
    RetVal[OPCODE_MOV_RAX_M_ONLY_DISP] = "MOV";
    RetVal[OPCODE_MOVS] = "MOVS";
    RetVal[OPCODE_CMPS] = "CMPS";
    RetVal[OPCODE_TEST_RAX_IMM] = "TEST";
    RetVal[OPCODE_STOS] = "STOS";
    RetVal[OPCODE_LODS] = "LODS";
    RetVal[OPCODE_SCAS] = "SCAS";
    RetVal[OPCODE_MOV_R_IMM] = "MOV";
    RetVal[OPCODE_RETN_I16] = "RETN";
    RetVal[OPCODE_RETN] = "RETN";
    RetVal[OPCODE_LES] = "LES";
    RetVal[OPCODE_LDS] = "LDS";
    RetVal[OPCODE_MOV_RM_IMM] = "MOV";
    RetVal[OPCODE_ENTER] = "ENTER";
    RetVal[OPCODE_LEAVE] = "LEAVE";
    RetVal[OPCODE_RETF_I16] = "RETF";
    RetVal[OPCODE_RETF] = "RETF";
    RetVal[OPCODE_INT3] = "INT3";
    RetVal[OPCODE_INT] = "INT";
    RetVal[OPCODE_INTO] = "INTO";
    RetVal[OPCODE_IRETD] = "IRETD";
    RetVal[OPCODE_AAM] = "AAM";
    RetVal[OPCODE_AAD] = "AAD";
    RetVal[OPCODE_SALC] = "SALC";
    RetVal[OPCODE_XLAT] = "XLAT";
    RetVal[OPCODE_LOOPNZ] = "LOOPNZ";
    RetVal[OPCODE_LOOPZ] = "LOOPZ";
    RetVal[OPCODE_LOOP] = "LOOP";
    RetVal[OPCODE_JECXZ] = "JECXZ";
    RetVal[OPCODE_IN] = "IN";
    RetVal[OPCODE_OUT] = "OUT";
    RetVal[OPCODE_CALL_NEAR] = "CALL";
    RetVal[OPCODE_JMP_NEAR] = "JMP";
    RetVal[OPCODE_JMP_FAR] = "JMP";
    RetVal[OPCODE_JMP] = "JMP";
    RetVal[OPCODE_IN_DX] = "IN";
    RetVal[OPCODE_OUT_DX] = "OUT";
    RetVal[OPCODE_INT1] = "INT1";
    RetVal[OPCODE_HLT] = "HLT";
    RetVal[OPCODE_CMC] = "CMC";
    RetVal[OPCODE_CLC] = "CLC";
    RetVal[OPCODE_STC] = "STC";
    RetVal[OPCODE_CLI] = "CLI";
    RetVal[OPCODE_STI] = "STI";
    RetVal[OPCODE_CLD] = "CLD";
    RetVal[OPCODE_STD] = "STD";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSecondOpcode()
{
    map<BYTE, string> RetVal;
    RetVal[SECOND_OPCODE_JO] = "JO";
    RetVal[SECOND_OPCODE_JNO] = "JNO";
    RetVal[SECOND_OPCODE_JB] = "JB";
    RetVal[SECOND_OPCODE_JNB] = "JNB";
    RetVal[SECOND_OPCODE_JE] = "JE";
    RetVal[SECOND_OPCODE_JNE] = "JNE";
    RetVal[SECOND_OPCODE_JBE] = "JBE";
    RetVal[SECOND_OPCODE_JA] = "JA";
    RetVal[SECOND_OPCODE_JS] = "JS";
    RetVal[SECOND_OPCODE_JNS] = "JNS";
    RetVal[SECOND_OPCODE_JPE] = "JPE";
    RetVal[SECOND_OPCODE_JPO] = "JPO";
    RetVal[SECOND_OPCODE_JL] = "JL";
    RetVal[SECOND_OPCODE_JGE] = "JGE";
    RetVal[SECOND_OPCODE_JLE] = "JLE";
    RetVal[SECOND_OPCODE_JG] = "JG";
    
    RetVal[SECOND_OPCODE_SETO] = "SETO";
    RetVal[SECOND_OPCODE_SETNO] = "SETNO";
    RetVal[SECOND_OPCODE_SETB] = "SETB";
    RetVal[SECOND_OPCODE_SETNB] = "SETNB";
    RetVal[SECOND_OPCODE_SETE] = "SETE";
    RetVal[SECOND_OPCODE_SETNE] = "SETNE";
    RetVal[SECOND_OPCODE_SETBE] = "SETBE";
    RetVal[SECOND_OPCODE_SETA] = "SETA";
    RetVal[SECOND_OPCODE_SETS] = "SETS";
    RetVal[SECOND_OPCODE_SETNS] = "SETNS";
    RetVal[SECOND_OPCODE_SETPE] = "SETPE";
    RetVal[SECOND_OPCODE_SETPO] = "SETPO";
    RetVal[SECOND_OPCODE_SETL] = "SETL";
    RetVal[SECOND_OPCODE_SETGE] = "SETGE";
    RetVal[SECOND_OPCODE_SETLE] = "SETLE";
    RetVal[SECOND_OPCODE_SETG] = "SETG";
    
    RetVal[SECOND_OPCODE_PUSH_FS] = "PUSH";
    RetVal[SECOND_OPCODE_POP_FS] = "POP";
    RetVal[SECOND_OPCODE_CPUID] = "CPUID";
    RetVal[SECOND_OPCODE_BT] = "BT";
    RetVal[SECOND_OPCODE_SHLD_I8] = "SHLD";
    RetVal[SECOND_OPCODE_SHLD_CL] = "SHLD";
    RetVal[SECOND_OPCODE_PUSH_GS] = "PUSH";
    RetVal[SECOND_OPCODE_POP_GS] = "POP";
    RetVal[SECOND_OPCODE_RSM] = "RSM";
    RetVal[SECOND_OPCODE_BTS] = "BTS";
    RetVal[SECOND_OPCODE_SHRD_I8] = "SHRD";
    RetVal[SECOND_OPCODE_SHRD_CL] = "SHRD";
    RetVal[SECOND_OPCODE_FXSAVE] = "FXSAVE";
    RetVal[SECOND_OPCODE_IMUL] = "IMUL";
    
    RetVal[SECOND_OPCODE_CMPXCHG] = "CMPXCHG";
    RetVal[SECOND_OPCODE_LSS] = "LSS";
    RetVal[SECOND_OPCODE_BTR] = "BTR";
    RetVal[SECOND_OPCODE_LFS] = "LFS";
    RetVal[SECOND_OPCODE_LGS] = "LGS";
    RetVal[SECOND_OPCODE_MOVZX] = "MOVZX";
    RetVal[SECOND_OPCODE_UD1] = "UD1";
    RetVal[SECOND_OPCODE_BTC] = "BTC";
    RetVal[SECOND_OPCODE_BSF] = "BSF";
    RetVal[SECOND_OPCODE_BSR] = "BSR";
    RetVal[SECOND_OPCODE_MOVSX] = "MOVSX";
    
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_TestGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_TEST_0] = "TEST";
    RetVal[SUB_OPCODE_TEST_1] = "TEST";
    RetVal[SUB_OPCODE_NOT] = "NOT";
    RetVal[SUB_OPCODE_NEG] = "NEG";
    RetVal[SUB_OPCODE_MUL] = "MUL";
    RetVal[SUB_OPCODE_IMUL] = "IMUL";
    RetVal[SUB_OPCODE_DIV] = "DIV";
    RetVal[SUB_OPCODE_IDIV] = "IDIV";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_AddGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_ADD] = "ADD";
    RetVal[SUB_OPCODE_OR] = "OR";
    RetVal[SUB_OPCODE_ADC] = "ADC";
    RetVal[SUB_OPCODE_SBB] = "SBB";
    RetVal[SUB_OPCODE_AND] = "AND";
    RetVal[SUB_OPCODE_SUB] = "SUB";
    RetVal[SUB_OPCODE_XOR] = "XOR";
    RetVal[SUB_OPCODE_CMP] = "CMP";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_RolGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_ROL] = "ROL";
    RetVal[SUB_OPCODE_ROR] = "ROR";
    RetVal[SUB_OPCODE_RCL] = "RCL";
    RetVal[SUB_OPCODE_RCR] = "RCR";
    RetVal[SUB_OPCODE_SHL] = "SHL";
    RetVal[SUB_OPCODE_SHR] = "SHR";
    RetVal[SUB_OPCODE_SAL] = "SAL";
    RetVal[SUB_OPCODE_SAR] = "SAR";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_FaddGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_FADD] = "FADD";
    RetVal[SUB_OPCODE_FMUL] = "FMUL";
    RetVal[SUB_OPCODE_FCOM] = "FCOM";
    RetVal[SUB_OPCODE_FCOMP] = "FCOMP";
    RetVal[SUB_OPCODE_FSUB] = "FSUB";
    RetVal[SUB_OPCODE_FSUBR] = "FSUBR";
    RetVal[SUB_OPCODE_FDIV] = "FDIV";
    RetVal[SUB_OPCODE_FDIVR] = "FDIVR";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_FldGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_FLD] = "FLD";
    RetVal[SUB_OPCODE_FST] = "FST";
    RetVal[SUB_OPCODE_FSTP] = "FSTP";
    RetVal[SUB_OPCODE_FLDENV] = "FLDENV";
    RetVal[SUB_OPCODE_FLDCW] = "FLDCW";
    RetVal[SUB_OPCODE_FSTENV] = "FSTENV";
    RetVal[SUB_OPCODE_FSTCW] = "FSTCW";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_Fld64Group()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_FLD] = "FLD";
    RetVal[SUB_OPCODE_FISTTP] = "FISTTP";
    RetVal[SUB_OPCODE_FST] = "FST";
    RetVal[SUB_OPCODE_FSTP] = "FSTP";
    RetVal[SUB_OPCODE_FRSTOR] = "FRSTOR";
    RetVal[SUB_OPCODE_FSAVE] = "FSAVE";
    RetVal[SUB_OPCODE_FSTSW] = "FSTSW";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_FiaddGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_FIADD] = "FIADD";
    RetVal[SUB_OPCODE_FIMUL] = "FIMUL";
    RetVal[SUB_OPCODE_FICOM] = "FICOM";
    RetVal[SUB_OPCODE_FICOMP] = "FICOMP";
    RetVal[SUB_OPCODE_FISUB] = "FISUB";
    RetVal[SUB_OPCODE_FISUBR] = "FISUBR";
    RetVal[SUB_OPCODE_FIDIV] = "FIDIV";
    RetVal[SUB_OPCODE_FIDIVR] = "FIDIVR";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_FildGroup()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_FILD] = "FILD";
    RetVal[SUB_OPCODE_FISTTP] = "FISTTP";
    RetVal[SUB_OPCODE_FIST] = "FIST";
    RetVal[SUB_OPCODE_FISTP] = "FISTP";
    RetVal[SUB_OPCODE_FLD_TBYTE] = "FLD";
    RetVal[SUB_OPCODE_FSTP_TBYTE] = "FSTP";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_Fild16Group()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_FILD] = "FILD";
    RetVal[SUB_OPCODE_FISTTP] = "FISTTP";
    RetVal[SUB_OPCODE_FIST] = "FIST";
    RetVal[SUB_OPCODE_FISTP] = "FISTP";
    RetVal[SUB_OPCODE_FBLD_TBYTE] = "FBLD";
    RetVal[SUB_OPCODE_FILD64] = "FILD";
    RetVal[SUB_OPCODE_FBSTP_TBYTE] = "FBSTP";
    RetVal[SUB_OPCODE_FISTP64] = "FISTP";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_Inc8Group()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_INC] = "INC";
    RetVal[SUB_OPCODE_DEC] = "DEC";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitSubOpcode_Inc16_32Group()
{
    map<BYTE, string> RetVal;
    RetVal[SUB_OPCODE_INC] = "INC";
    RetVal[SUB_OPCODE_DEC] = "DEC";
    RetVal[SUB_OPCODE_CALL_NEAR] = "CALL";
    RetVal[SUB_OPCODE_CALL_FAR] = "CALL";
    RetVal[SUB_OPCODE_JMP_NEAR] = "JMP";
    RetVal[SUB_OPCODE_JMP_FAR] = "JMP";
    RetVal[SUB_OPCODE_PUSH] = "PUSH";
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitReg(BYTE GroupID)
{
    map<BYTE, string> RetVal;
    switch (GroupID)
    {
        case REGSIZE_8:
            RetVal[REG_AL_8] = "AL";
            RetVal[REG_CL_8] = "CL";
            RetVal[REG_DL_8] = "DL";
            RetVal[REG_BL_8] = "BL";
            RetVal[REG_AH_8] = "AH";
            RetVal[REG_CH_8] = "CH";
            RetVal[REG_DH_8] = "DH";
            RetVal[REG_BH_8] = "BH";
            break;
        case REGSIZE_16:
            RetVal[REG_AX_16] = "AX";
            RetVal[REG_CX_16] = "CX";
            RetVal[REG_DX_16] = "DX";
            RetVal[REG_BX_16] = "BX";
            RetVal[REG_SP_16] = "SP";
            RetVal[REG_BP_16] = "BP";
            RetVal[REG_SI_16] = "SI";
            RetVal[REG_DI_16] = "DI";
            break;
        case REGSIZE_32:
            RetVal[REG_EAX_32] = "EAX";
            RetVal[REG_ECX_32] = "ECX";
            RetVal[REG_EDX_32] = "EDX";
            RetVal[REG_EBX_32] = "EBX";
            RetVal[REG_ESP_32] = "ESP";
            RetVal[REG_EBP_32] = "EBP";
            RetVal[REG_ESI_32] = "ESI";
            RetVal[REG_EDI_32] = "EDI";
            break;
        case ADDRESSSIZE_16:
            RetVal[REG_ADDRESS16_BX_SI] = "BX + SI";
            RetVal[REG_ADDRESS16_BX_DI] = "BX + DI";
            RetVal[REG_ADDRESS16_BP_SI] = "BP + SI";
            RetVal[REG_ADDRESS16_BP_DI] = "BP + DI";
            RetVal[REG_ADDRESS16_BX] = "BX";
            RetVal[REG_ADDRESS16_BP] = "BP";
            RetVal[REG_ADDRESS16_SI] = "SI";
            RetVal[REG_ADDRESS16_DI] = "DI";
            break;
        case SEGMENT_REG:
            RetVal[REG_CS] = "CS";
            RetVal[REG_DS] = "DS";
            RetVal[REG_ES] = "ES";
            RetVal[REG_FS] = "FS";
            RetVal[REG_GS] = "GS";
            RetVal[REG_SS] = "SS";
            RetVal[REG_SEG6] = "SEG6:";
            RetVal[REG_SEG7] = "SEG7:";
            break;
        case FLOAT_REG: // TODO
            break;
        default:
            break;
    }
    return RetVal;
}

map<BYTE, string> Intelx86Def::InitAddressHead()
{
    map<BYTE, string> RetVal;
    RetVal[ADDRESSHEAD_8] = "BYTE PTR";
    RetVal[ADDRESSHEAD_16] = "WORD PTR";
    RetVal[ADDRESSHEAD_32] = "DWORD PTR";
    RetVal[ADDRESSHEAD_64] = "QWORD PTR";
    RetVal[ADDRESSHEAD_F] = "FWORD PTR";
    RetVal[ADDRESSHEAD_NULL] = "";
    RetVal[ADDRESSHEAD_TBYTE] = "TBYTE PTR";
    return RetVal;
}

map<BYTE, string>& Intelx86Def::GetPrefix(BYTE GroupID)
{
    return Intelx86Def::Prefix[GroupID];
}

map<BYTE, string>& Intelx86Def::GetSinglePrefixName()
{
    return Intelx86Def::SinglePrefixName;
}

map<BYTE, string>& Intelx86Def::GetOpcode()
{
    return Intelx86Def::Opcode;
}

map<BYTE, string>& Intelx86Def::GetSecondOpcode()
{
    return Intelx86Def::SecondOpcode;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_TestGroup()
{
    return Intelx86Def::SubOpcode_TestGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_AddGroup()
{
    return Intelx86Def::SubOpcode_AddGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_RolGroup()
{
    return Intelx86Def::SubOpcode_RolGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_FaddGroup()
{
    return Intelx86Def::SubOpcode_FaddGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_FldGroup()
{
    return Intelx86Def::SubOpcode_FldGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_Fld64Group()
{
    return Intelx86Def::SubOpcode_Fld64Group;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_FiaddGroup()
{
    return Intelx86Def::SubOpcode_FiaddGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_FildGroup()
{
    return Intelx86Def::SubOpcode_FildGroup;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_Fild16Group()
{
    return Intelx86Def::SubOpcode_Fild16Group;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_Inc8Group()
{
    return Intelx86Def::SubOpcode_Inc8Group;
}

map<BYTE, string>& Intelx86Def::GetSubOpcode_Inc16_32Group()
{
    return Intelx86Def::SubOpcode_Inc16_32Group;
}

map<BYTE, string>& Intelx86Def::GetReg(BYTE GroupID)
{
    return Intelx86Def::Reg[GroupID];
}

map<BYTE, string>& Intelx86Def::GetAddressHead()
{
    return Intelx86Def::AddressHead;
}

map<BYTE, string> Intelx86Def::Prefix[4];
map<BYTE, string> Intelx86Def::SinglePrefixName;
map<BYTE, string> Intelx86Def::Opcode;
map<BYTE, string> Intelx86Def::SecondOpcode;
map<BYTE, string> Intelx86Def::SubOpcode_TestGroup;
map<BYTE, string> Intelx86Def::SubOpcode_AddGroup;
map<BYTE, string> Intelx86Def::SubOpcode_RolGroup;
map<BYTE, string> Intelx86Def::SubOpcode_FaddGroup;
map<BYTE, string> Intelx86Def::SubOpcode_FldGroup;
map<BYTE, string> Intelx86Def::SubOpcode_Fld64Group;
map<BYTE, string> Intelx86Def::SubOpcode_FiaddGroup;
map<BYTE, string> Intelx86Def::SubOpcode_FildGroup;
map<BYTE, string> Intelx86Def::SubOpcode_Fild16Group;
map<BYTE, string> Intelx86Def::SubOpcode_Inc8Group;
map<BYTE, string> Intelx86Def::SubOpcode_Inc16_32Group;
map<BYTE, string> Intelx86Def::Reg[7];
map<BYTE, string> Intelx86Def::AddressHead;



