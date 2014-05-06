//
//  InstructionDef.h
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#ifndef UDASM_InstructionDef_h
#define UDASM_InstructionDef_h

#include "BaseDef.h"

/* 指令前缀(Prefix) */
// 第一组
#define REPEAT_PREFIX_LOCK  0xF0
#define REPEAT_PREFIX_REP   0xF3
#define REPEAT_PREFIX_REPE  0xF3
#define REPEAT_PREFIX_REPZ  0xF3
#define REPEAT_PREFIX_REPNE 0xF2
#define REPEAT_PREFIX_REPNZ 0xF2
// 第二组
#define SEGMENT_PREFIX_ES   0x26
#define SEGMENT_PREFIX_CS   0x2E
#define SEGMENT_PREFIX_SS   0x36
#define SEGMENT_PREFIX_DS   0x3E
#define SEGMENT_PREFIX_FS   0x64
#define SEGMENT_PREFIX_GS   0x65
// 第三组
#define OPERAND_PREFIX      0x66 // 操作数大小改写指令
// 第四组
#define ADDRESS_PREFIX      0x67 // 地址大小改写指令

/* 操作码(Opcode) */
#define OPCODE_ADD  0x00
#define OPCODE_OR   0x08
#define OPCODE_ADC  0x10
#define OPCODE_SBB  0x18
#define OPCODE_AND  0x20
#define OPCODE_SUB  0x28
#define OPCODE_XOR  0x30
#define OPCODE_CMP  0x38

#define RM8_R8      0x00
#define RM16_R16    0x01
#define R8_RM8      0x02
#define R16_RM16    0x03
#define AL_I8       0x04
#define RAX_I16     0x05
//01 111 101
#define OPCODE2_ADD 0x00
#define OPCODE2_OR  0x01
#define OPCODE2_ADC 0x02
#define OPCODE2_SBB 0x03
#define OPCODE2_AND 0x04
#define OPCODE2_SUB 0x05
#define OPCODE2_XOR 0x06
#define OPCODE2_CMP 0x07

#define OPCODE_NOP  0x90

/* ModR/M */
#define MOD_M_NO_DISPLACEMENT 0x00
#define MOD_M_DISPLACEMENT_8  0x01
#define MOD_M_DISPLACEMENT_16 0x02
#define MOD_R_NO_DISPLACEMENT 0x03

#define REG_AL_8   0x00
#define REG_CL_8   0x01
#define REG_DL_8   0x02
#define REG_BL_8   0x03
#define REG_AH_8   0x04
#define REG_CH_8   0x05
#define REG_DH_8   0x06
#define REG_BH_8   0x07
#define REG_AX_16  0x00
#define REG_CX_16  0x01
#define REG_DX_16  0x02
#define REG_BX_16  0x03
#define REG_SP_16  0x04
#define REG_BP_16  0x05
#define REG_SI_16  0x06
#define REG_DI_16  0x07
#define REG_EAX_32 0x00
#define REG_ECX_32 0x01
#define REG_EDX_32 0x02
#define REG_EBX_32 0x03
#define REG_ESP_32 0x04
#define REG_EBP_32 0x05
#define REG_ESI_32 0x06
#define REG_EDI_32 0x07
#define REG_ADDRESS16_BX_SI 0x00
#define REG_ADDRESS16_BX_DI 0x01
#define REG_ADDRESS16_BP_SI 0x02
#define REG_ADDRESS16_BP_DI 0x03
#define REG_ADDRESS16_SI    0x04
#define REG_ADDRESS16_DI    0x05
#define REG_ADDRESS16_BP    0x06 // small 1234h
#define REG_ADDRESS16_BX    0x07

#define RM_SIB_FLAG 0x04
#define RM_ONLY_DISPLACEMENT_16_FLAG 0x05

#define REGSIZE_8      0x00
#define REGSIZE_16     0x01
#define REGSIZE_32     0x02
#define ADDRESSSIZE_16 0x03

#define ADDRESSHEAD_8  0x00
#define ADDRESSHEAD_16 0x01
#define ADDRESSHEAD_32 0x02

#define GET_MOD(A) (((A) >> 6) & 0x03)
#define GET_OPCODE2(A) (((A) >> 3) & 0x07)
#define GET_REG(A) GET_OPCODE2(A)
#define GET_RM(A) ((A) & 0x07)

#define GET_SCALE(A) (((A) >> 6) & 0x03)
#define GET_INDEX(A) (((A) >> 3) & 0x07)
#define GET_BASE(A) ((A) & 0x07)

class InstructionDef
{
private:
    static map<BYTE, string> Prefix[4];
    static map<BYTE, string> SinglePrefixName;
    static map<BYTE, string> Opcode;
    static map<BYTE, string> RM;
    static map<BYTE, string> Reg[4];
    static map<BYTE, string> AddressHead;
public:
    static map<BYTE, string> InitPrefix(BYTE GroupID);
    static map<BYTE, string> InitSinglePrefixName();
    static map<BYTE, string> InitOpcode();
    static map<BYTE, string> InitRM();
    static map<BYTE, string> InitReg(BYTE GroupID);
    static map<BYTE, string> InitAddressHead();
    
    static map<BYTE, string>& GetPrefix(BYTE GroupID);
    static map<BYTE, string>& GetSinglePrefixName();
    static map<BYTE, string>& GetOpcode();
    static map<BYTE, string>& GetRM();
    static map<BYTE, string>& GetReg(BYTE GroupID);
    static map<BYTE, string>& GetAddressHead();
};

#endif
