//
//  DASM.h
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#ifndef __UDASM__DASM__
#define __UDASM__DASM__

#include "InstructionDef.h"
#include "Instruction.h"

/* Hardware Arch */
#define INTEL_X86             0x00
#define AT_AND_T              0x01

/* CPU Working Mode */
#define CPU_MODE_16           0x01
#define CPU_MODE_32           0x02

/* CPU Addressing Mode */
#define ADDRESS_MODE_16       0x01
#define ADDRESS_MODE_32       0x02

/* Byte Order */
#define UDASM_BIG_ENDIAN      0x00
#define UDASM_LITTLE_ENDIAN   0x01

/* Exception Code */
#define NO_PREFIX_CONFLICTION 0xFF

class DASM
{
private:
    Instruction CntInstruction;
    BYTE DefaultCPUMode;
    BYTE DefaultAddressMode;
    BYTE DefaultByteOrder;
    BYTE DefaultSegmentRegister;
    BYTE CPUMode;
    BYTE AddressMode;
public:
    DASM(string FileName, BYTE Arch, BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder);
    ~DASM();
    
    void BaseInit(BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder);
    void ResetMode();
    void INTEL_X86_Init();
    void AT_AND_T_Init();
    void INTEL_X86_Exec(string FileName);
    void AT_AND_T_Exec(string FileName);
    void SetDefaultCPUMode(BYTE DefaultCPUMode);
    BYTE GetDefaultCPUMode();
    void SetDefaultAddressMode(BYTE DefaultAddressMode);
    BYTE GetDefaultAddressMode();
    void SetCPUMode(BYTE CPUMode);
    BYTE GetCPUMode();
    void SetAddressMode(BYTE AddressMode);
    BYTE GetAddressMode();
    void SetDefaultSegmentRegister(BYTE Register);
    BYTE GetDefaultSegmentRegister();
    void SetDefaultByteOrder(BYTE DefaultByteOrder);
    BYTE GetDefaultByteOrder();
    BYTE ReadByte(ifstream &ExeFile);
    WORD ReadWord(ifstream &ExeFile);
    DWORD ReadDWord(ifstream &ExeFile);
    string FormatByte(BYTE CntByte);
    string FormatBinWord(WORD CntWord);
    string FormatAsmWord(WORD CntWord);
    string FormatBinDWord(DWORD CntDWord);
    string FormatAsmDWord(DWORD CntDWord);
    string ParseMemoryOperand(ifstream &ExeFile, stringstream &BinStream, BYTE Opcode, BYTE MODRM);
    string ParseRegisterOperand(BYTE Opcode, BYTE REG);
    string ParseImmediateOperand(ifstream &ExeFile, stringstream &BinStream, BYTE Opcode);
    string ParseImmediateOperand_I8(ifstream &ExeFile, stringstream &BinStream);
    string ParseImmediateOperand_I16(ifstream &ExeFile, stringstream &BinStream);
    string ParseImmediateOperand_I32(ifstream &ExeFile, stringstream &BinStream);
    string ParseImmediateOperand_I16_I32(ifstream &ExeFile, stringstream &BinStream);
    string ParseDisplacement(ifstream &ExeFile, stringstream &BinStream, BYTE MOD);
    string ParseMODRM_RM(ifstream &ExeFile, stringstream &BinStream, BYTE Opcode, BYTE MODRM);
    string ParseMODRM_RM_RM(ifstream &ExeFile, stringstream &BinStream, BYTE Opcode, BYTE MODRM);
    string ParseMODRM_RM_IMM(ifstream &ExeFile, stringstream &BinStream, BYTE Opcode, BYTE MODRM);
    void StringStreamClear(stringstream &SStream);
};

#endif /* defined(__UDASM__DASM__) */
