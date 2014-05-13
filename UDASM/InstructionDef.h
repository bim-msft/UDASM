//
//  InstructionDef.h
//  UDASM
//
//  Basic Definations For Intelx86 Arch
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#ifndef UDASM_InstructionDef_h
#define UDASM_InstructionDef_h

#include "BaseDef.h"

/* Instruction Prefix */
// Group 1 (Repeat Prefix)
#define REPEAT_PREFIX_LOCK           0xF0 // 0xF0
#define REPEAT_PREFIX_REP            0xF3 // 0xF3
#define REPEAT_PREFIX_REPE           0xF3
#define REPEAT_PREFIX_REPZ           0xF3
#define REPEAT_PREFIX_REPNE          0xF2 // 0xF2
#define REPEAT_PREFIX_REPNZ          0xF2
// Group 2 (Default Segment Register Switch)
#define SEGMENT_PREFIX_ES            0x26 // 0x26
#define SEGMENT_PREFIX_CS            0x2E // 0x2E
#define SEGMENT_PREFIX_SS            0x36 // 0x36
#define SEGMENT_PREFIX_DS            0x3E // 0x3E
#define SEGMENT_PREFIX_FS            0x64 // 0x64
#define SEGMENT_PREFIX_GS            0x65 // 0x65
// Group 3 (Operands Size Switch (16/32))
#define OPERAND_PREFIX               0x66 // 0x66
// Group 4 (Addressing Size Switch (16/32))
#define ADDRESS_PREFIX               0x67 // 0x67

/* Opcode */
// Opcode Byte
#define OPCODE_ADD                   0x00 // 0x00 ~ 0x05 (+RM 5)
#define OPCODE_PUSH_ES               0x06 // 0x06
#define OPCODE_POP_ES                0x07 // 0x07
#define OPCODE_OR                    0x08 // 0x08 ~ 0x0D (+RM 5)
#define OPCODE_PUSH_CS               0x0E // 0x0E
#define OPCODE_POP_CS                0x0F // 0x0F
#define OPCODE_ADC                   0x10 // 0x10 ~ 0x15 (+RM 5)
#define OPCODE_PUSH_SS               0x16 // 0x16
#define OPCODE_POP_SS                0x17 // 0x17
#define OPCODE_SBB                   0x18 // 0x18 ~ 0x1D (+RM 5)
#define OPCODE_PUSH_DS               0x1E // 0x1E
#define OPCODE_POP_DS                0x1F // 0x1F
#define OPCODE_AND                   0x20 // 0x20 ~ 0x25 (+RM 5)
#define OPCODE_DAA                   0x27 // 0x27
#define OPCODE_SUB                   0x28 // 0x28 ~ 0x2D (+RM 5)
#define OPCODE_DAS                   0x2F // 0x2F
#define OPCODE_XOR                   0x30 // 0x30 ~ 0x35 (+RM 5)
#define OPCODE_AAA                   0x37 // 0x37
#define OPCODE_CMP                   0x38 // 0x38 ~ 0x3D (+RM 5)
#define OPCODE_AAS                   0x3F // 0x3F
#define OPCODE_INC                   0x40 // 0x40 ~ 0x47 (+REG 8)
#define OPCODE_DEC                   0x48 // 0x48 ~ 0x4F (+REG 8)
#define OPCODE_PUSH                  0x50 // 0x50 ~ 0x57 (+REG 8)
#define OPCODE_POP                   0x58 // 0x58 ~ 0x65 (+REG 8)
#define OPCODE_PUSH_I16_I32          0x68 // 0x68
#define OPCODE_IMUL_I16_I32_3OP      0x69 // 0x69
#define OPCODE_PUSH_I8               0x6A // 0x6A
#define OPCODE_IMUL_I8_3OP           0x6B // 0x6B
#define OPCODE_INS                   0x6C // 0x6C ~ 0x6D (W Bit)
#define OPCODE_OUTS                  0x6E // 0x6E ~ 0x6F (W Bit)
#define OPCODE_JO                    0x70 // 0x70
#define OPCODE_JNO                   0x71 // 0x71
#define OPCODE_JB                    0x72 // 0x72
#define OPCODE_JNB                   0x73 // 0x73
#define OPCODE_JE                    0x74 // 0x74
#define OPCODE_JNE                   0x75 // 0x75
#define OPCODE_JBE                   0x76 // 0x76
#define OPCODE_JA                    0x77 // 0x77
#define OPCODE_JS                    0x78 // 0x78
#define OPCODE_JNS                   0x79 // 0x79
#define OPCODE_JPE                   0x7A // 0x7A
#define OPCODE_JPO                   0x7B // 0x7B
#define OPCODE_JL                    0x7C // 0x7C
#define OPCODE_JGE                   0x7D // 0x7D
#define OPCODE_JLE                   0x7E // 0x7E
#define OPCODE_JG                    0x7F // 0x7F
#define OPCODE_ADD_GROUP             0x80 // 0x80 ~ 0x83
#define SUB_OPCODE_ADD               0x00 // [ADD GROUP]
#define SUB_OPCODE_OR                0x01 // [ADD GROUP]
#define SUB_OPCODE_ADC               0x02 // [ADD GROUP]
#define SUB_OPCODE_SBB               0x03 // [ADD GROUP]
#define SUB_OPCODE_AND               0x04 // [ADD GROUP]
#define SUB_OPCODE_SUB               0x05 // [ADD GROUP]
#define SUB_OPCODE_XOR               0x06 // [ADD GROUP]
#define SUB_OPCODE_CMP               0x07 // [ADD GROUP]
#define OPCODE_TEST                  0x84 // 0x84 ~ 0x85 (+RM 2)
#define OPCODE_XCHG                  0x86 // 0x86 ~ 0x87 (+RM 2)
#define OPCODE_MOV                   0x88 // 0x88 ~ 0x8E (+RM 6)
#define OPCODE_UNDEFINED_8F          0x8F // 0x8F
#define OPCODE_NOP                   0x90 // 0x90
#define OPCODE_XCHG_RAX_R            0x91 // 0x91 ~ 0x97
#define OPCODE_CWDE                  0x98 // 0x98
#define OPCODE_CDQ                   0x99 // 0x99
#define OPCODE_CALL_FAR              0x9A // 0x9A
#define OPCODE_WAIT                  0x9B // 0x9B
#define OPCODE_PUSHFD                0x9C // 0x9C
#define OPCODE_POPFD                 0x9D // 0x9D
#define OPCODE_SAHF                  0x9E // 0x9E
#define OPCODE_LAHF                  0x9F // 0x9F
#define OPCODE_MOV_RAX_M_ONLY_DISP   0xA0 // 0xA0 ~ 0xA3
#define OPCODE_MOVS                  0xA4 // 0xA4 ~ 0xA5
#define OPCODE_CMPS                  0xA6 // 0xA6 ~ 0xA7
#define OPCODE_TEST_RAX_IMM          0xA8 // 0xA8 ~ 0xA9 (+RM 2)
#define OPCODE_STOS                  0xAA // 0xAA ~ 0xAB (+RM 2)
#define OPCODE_LODS                  0xAC // 0xAC ~ 0xAD (+RM 2)
#define OPCODE_SCAS                  0xAE // 0xAE ~ 0xAF (+RM 2)
#define OPCODE_MOV_R_IMM             0xB0 // 0xB0 ~ 0xBF (+REG 8 * RM 2)
#define OPCODE_ROL_M_I8              0xC0 // 0xC0 ~ 0xC1 (+RM 2)
#define OPCODE_RETN_I16              0xC2 // 0xC2
#define OPCODE_RETN                  0xC3 // 0xC3
#define OPCODE_CALL_NEAR             0xE8 // 0x8E
#define OPCODE_TEST_GROUP            0xF6 // 0xF6 ~ 0xF7 (+RM 2)
#define SUB_OPCODE_TEST_0            0x00 // [TEST GROUP]
#define SUB_OPCODE_TEST_1            0x01 // [TEST GROUP]
#define SUB_OPCODE_NOT               0x02 // [TEST GROUP]
#define SUB_OPCODE_NEG               0x03 // [TEST GROUP]
#define SUB_OPCODE_MUL               0x04 // [TEST GROUP]
#define SUB_OPCODE_IMUL              0x05 // [TEST GROUP]
#define SUB_OPCODE_DIV               0x06 // [TEST GROUP]
#define SUB_OPCODE_IDIV              0x07 // [TEST GROUP]
// Mode in Opcode Byte (RM)
#define RM8_R8                       0x00
#define RM16_R16                     0x01
#define R8_RM8                       0x02
#define R16_RM16                     0x03
#define AL_I8                        0x04
#define RAX_I16                      0x05
#define SEGR_RM                      0x06
// Special Opcode Bit
#define GET_D_BIT(A)                 (((A) >> 1) & 0x01) // For Non-Immediate Number Instruction (Operands Order Switch)
#define GET_S_BIT(A)                 (((A) >> 1) & 0x01) // For Immediate Number Instruction (Signed Or Unsigned)
#define GET_W_BIT(A)                 ((A) & 0x01) // Operands Size Switch (8 - 16/32)

/* ModR/M */
// Mod
#define MOD_M_NO_DISPLACEMENT        0x00
#define MOD_M_DISPLACEMENT_8         0x01
#define MOD_M_DISPLACEMENT_16_32     0x02
#define MOD_R_NO_DISPLACEMENT        0x03
// Register Name (8 Bits)
#define REG_AL_8                     0x00
#define REG_CL_8                     0x01
#define REG_DL_8                     0x02
#define REG_BL_8                     0x03
#define REG_AH_8                     0x04
#define REG_CH_8                     0x05
#define REG_DH_8                     0x06
#define REG_BH_8                     0x07
// Register Name (16 Bits)
#define REG_AX_16                    0x00
#define REG_CX_16                    0x01
#define REG_DX_16                    0x02
#define REG_BX_16                    0x03
#define REG_SP_16                    0x04
#define REG_BP_16                    0x05
#define REG_SI_16                    0x06
#define REG_DI_16                    0x07
// Register Name (32 Bits)
#define REG_EAX_32                   0x00
#define REG_ECX_32                   0x01
#define REG_EDX_32                   0x02
#define REG_EBX_32                   0x03
#define REG_ESP_32                   0x04
#define REG_EBP_32                   0x05
#define REG_ESI_32                   0x06
#define REG_EDI_32                   0x07
// Register Name (For 16-Bits Addressing)
#define REG_ADDRESS16_BX_SI          0x00
#define REG_ADDRESS16_BX_DI          0x01
#define REG_ADDRESS16_BP_SI          0x02
#define REG_ADDRESS16_BP_DI          0x03
#define REG_ADDRESS16_SI             0x04
#define REG_ADDRESS16_DI             0x05
#define REG_ADDRESS16_BP             0x06 // small 1234h ????
#define REG_ADDRESS16_BX             0x07
// Register Name (Segment Registers)
#define REG_ES                       0x00
#define REG_CS                       0x01
#define REG_SS                       0x02
#define REG_DS                       0x03
#define REG_FS                       0x04
#define REG_GS                       0x05
#define REG_SEG6                     0x06
#define REG_SEG7                     0x07
// Special Values For RM
#define RM_SIB_FLAG                  0x04 // Only For 32-Bits Addressing Mode 
#define RM_ONLY_DISPLACEMENT_32_FLAG 0x05 // Only When AddressMode == 32 Bits && Mod == MOD_M_NO_DISPLACEMENT(0x00)
#define RM_ONLY_DISPLACEMENT_16_FLAG 0x06 // Only When AddressMode == 16 Bits && Mod == MOD_M_NO_DISPLACEMENT(0x00)
// Index For InstructionDef::Reg
#define REGSIZE_8                    0x00
#define REGSIZE_16                   0x01
#define REGSIZE_32                   0x02
#define ADDRESSSIZE_16               0x03 // For 16-Bits Addressing
#define SEGMENT_REG                  0x04 // For Segment Registers
// Index For InstructionDef::AddressHead
#define ADDRESSHEAD_8                0x00 // byte ptr
#define ADDRESSHEAD_16               0x01 // word ptr
#define ADDRESSHEAD_32               0x02 // dword ptr
// Macros For Prasing MODR/M
#define GET_MOD(A)                   (((A) >> 6) & 0x03)
#define GET_OPCODE2(A)               (((A) >> 3) & 0x07)
#define GET_REG(A)                   GET_OPCODE2(A)
#define GET_RM(A)                    ((A) & 0x07)

/* SIB */
#define GET_SCALE(A)                 (((A) >> 6) & 0x03)
#define GET_INDEX(A)                 (((A) >> 3) & 0x07)
#define GET_BASE(A)                  ((A) & 0x07)

// Size of Operands
#define OPSIZE_8                     0x00
#define OPSIZE_16                    0x01
#define OPSIZE_32                    0x02
#define OPSIZE_16_32                 0x03
#define OPSIZE_ALL                   0x04

class InstructionDef
{
private:
    static map<BYTE, string> Prefix[4];
    static map<BYTE, string> SinglePrefixName;
    static map<BYTE, string> Opcode;
    static map<BYTE, string> SubOpcode_TestGroup;
    static map<BYTE, string> SubOpcode_AddGroup;
    static map<BYTE, string> Reg[5];
    static map<BYTE, string> AddressHead;
public:
    static map<BYTE, string> InitPrefix(BYTE GroupID);
    static map<BYTE, string> InitSinglePrefixName();
    static map<BYTE, string> InitOpcode();
    static map<BYTE, string> InitSubOpcode_TestGroup();
    static map<BYTE, string> InitSubOpcode_AddGroup();
    static map<BYTE, string> InitReg(BYTE GroupID);
    static map<BYTE, string> InitAddressHead();
    static map<BYTE, string>& GetPrefix(BYTE GroupID);
    static map<BYTE, string>& GetSinglePrefixName();
    static map<BYTE, string>& GetOpcode();
    static map<BYTE, string>& GetSubOpcode_TestGroup();
    static map<BYTE, string>& GetSubOpcode_AddGroup();
    static map<BYTE, string>& GetReg(BYTE GroupID);
    static map<BYTE, string>& GetAddressHead();
};

#endif
