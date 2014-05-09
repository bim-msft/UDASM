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
#define OPCODE_ADD                   0x00 // 0x00 ~ 0x05 (+RM)
#define OPCODE_PUSH_ES               0x06 // 0x06
#define OPCODE_POP_ES                0x07 // 0x07
#define OPCODE_OR                    0x08 // 0x08 ~ 0x0D (+RM)
#define OPCODE_PUSH_CS               0x0E // 0x0E
#define OPCODE_POP_CS                0x0F // 0x0F
#define OPCODE_ADC                   0x10 // 0x10 ~ 0x15 (+RM)
#define OPCODE_PUSH_SS               0x16 // 0x16
#define OPCODE_POP_SS                0x17 // 0x17
#define OPCODE_SBB                   0x18 // 0x18 ~ 0x1D (+RM)
#define OPCODE_PUSH_DS               0x1E // 0x1E
#define OPCODE_POP_DS                0x1F // 0x1F
#define OPCODE_AND                   0x20 // 0x20 ~ 0x25 (+RM)
#define OPCODE_DAA                   0x27 // 0x27
#define OPCODE_SUB                   0x28 // 0x28 ~ 0x2D (+RM)
#define OPCODE_DAS                   0x2F // 0x2F
#define OPCODE_XOR                   0x30 // 0x30 ~ 0x35 (+RM)
#define OPCODE_AAA                   0x37 // 0x37
#define OPCODE_CMP                   0x38 // 0x38 ~ 0x3D (+RM)
#define OPCODE_AAS                   0x3F // 0x3F
#define OPCODE_INC                   0x40 // 0x40 ~ 0x47 (+REG)
#define OPCODE_DEC                   0x48 // 0x48 ~ 0x4F (+REG)
#define OPCODE_PUSH                  0x50 // 0x50 ~ 0x57 (+REG)
#define OPCODE_POP                   0x58 // 0x58 ~ 0x65 (+REG)
#define OPCODE_PUSH_I16_I32          0x68 // 0x68
#define OPCODE_MOV                   0x88 // 0x88 ~ 0x8D (+RM)
#define OPCODE_NOP                   0x90 // 0x90
// Mode in Opcode Byte (RM)
#define RM8_R8                       0x00
#define RM16_R16                     0x01
#define R8_RM8                       0x02
#define R16_RM16                     0x03
#define AL_I8                        0x04
#define RAX_I16                      0x05
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
#define REG_CS                       0x00
#define REG_DS                       0x01
#define REG_ES                       0x02
#define REG_FS                       0x03
#define REG_GS                       0x04
#define REG_SS                       0x05
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

class InstructionDef
{
private:
    static map<BYTE, string> Prefix[4];
    static map<BYTE, string> SinglePrefixName;
    static map<BYTE, string> Opcode;
    static map<BYTE, string> Reg[5];
    static map<BYTE, string> AddressHead;
public:
    static map<BYTE, string> InitPrefix(BYTE GroupID);
    static map<BYTE, string> InitSinglePrefixName();
    static map<BYTE, string> InitOpcode();
    static map<BYTE, string> InitReg(BYTE GroupID);
    static map<BYTE, string> InitAddressHead();
    static map<BYTE, string>& GetPrefix(BYTE GroupID);
    static map<BYTE, string>& GetSinglePrefixName();
    static map<BYTE, string>& GetOpcode();
    static map<BYTE, string>& GetReg(BYTE GroupID);
    static map<BYTE, string>& GetAddressHead();
};

#endif
