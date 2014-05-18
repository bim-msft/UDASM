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
    ifstream ExeFile;
    stringstream AsmStream;
    stringstream BinStream;
    DWORD LoadAddress;
    DWORD OffsetAddress;
    DWORD CntAddress;
public:
    DASM(string FileName,  DWORD LoadAddress, DWORD OffsetAddress, BYTE Arch, BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder);
    ~DASM();
    
    void FileInit(string FileName, DWORD LoadAddress, DWORD OffsetAddress);
    void BaseInit(BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder);
    void ResetMode();
    void INTEL_X86_Init();
    void AT_AND_T_Init();
    void INTEL_X86_Exec();
    void AT_AND_T_Exec();
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
    void SetLoadAddress(DWORD LoadAddress);
    DWORD GetLoadAddress();
    void SetOffsetAddress(DWORD OffsetAddress);
    DWORD GetOffsetAddress();
    void AddressInc(DWORD IncVal);
    void SetCntAddress(DWORD CntAddress);
    DWORD GetCntAddress();
    stringstream& GetAsmStream();
    stringstream& GetBinStream();
    ifstream& GetExeFile();
    BYTE ReadByte();
    WORD ReadWord();
    DWORD ReadDWord();
    string FormatByte(BYTE CntByte, BYTE SMod = UNSIGNED);
    string FormatBinWord(WORD CntWord);
    string FormatAsmWord(WORD CntWord);
    string FormatBinDWord(DWORD CntDWord);
    string FormatAsmDWord(DWORD CntDWord);
    string ParseMemoryOperand(BYTE Opcode, BYTE MODRM, BYTE OpSize = OPSIZE_8_16_32);
    string ParseRegisterOperand(BYTE Opcode, BYTE REG);
    string ParseImmediateOperand(BYTE Opcode);
    string ParseImmediateOperand_I8(BYTE SMod = UNSIGNED);
    string ParseImmediateOperand_I16();
    string ParseImmediateOperand_I32();
    string ParseImmediateOperand_I16_I32();
    string ParseDisplacement(BYTE MOD);
    string ParseMODRM_RM(BYTE Opcode, BYTE MODRM, BYTE OpSize = OPSIZE_8_16_32);
    string ParseMODRM_RM_R(BYTE Opcode, BYTE MODRM, BYTE OpSize = OPSIZE_8_16_32);
    string ParseMODRM_RM_IMM(BYTE Opcode, BYTE MODRM, BYTE OpSize = OPSIZE_8_16_32);
    string ParseMODRM_R_RM_IMM(BYTE Opcode, BYTE MODRM, BYTE OpSize = OPSIZE_8_16_32);
    void StringStreamClear(stringstream &SStream);
};

#endif /* defined(__UDASM__DASM__) */
