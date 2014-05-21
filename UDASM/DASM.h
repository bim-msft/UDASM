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
#define UDASM_UNKNOWN_ENDIAN  0x02

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
    BYTE Arch;
    BYTE CPUMode;
    BYTE AddressMode;
    ifstream InputFile;
    ofstream OutputAddrFile;
    ofstream OutputBinFile;
    ofstream OutputAsmFile;
    stringstream AddrStream;
    stringstream AsmStream;
    stringstream BinStream;
    DWORD LoadAddress;
    DWORD OffsetAddress;
    DWORD OffsetAddressEnd;
    DWORD CntAddress;
public:
    DASM(BYTE Arch, BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder, string InputFileName, string OutputAddrFileName, string OutputBinFileName, string OutputAsmFileName, DWORD LoadAddress, DWORD OffsetAddress, DWORD OffsetAddressEnd);
    ~DASM();
    
    void Disassemble();
    void FileInit(string InputFileName, string OutputAddrFileName, string OutputBinFileName, string OutputAsmFileName, DWORD LoadAddress, DWORD OffsetAddress, DWORD OffsetAddressEnd);
    void BaseInit(BYTE Arch, BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder);
    void ResetMode();
    void INTEL_X86_Init();
    void AT_AND_T_Init();
    void INTEL_X86_Exec();
    void AT_AND_T_Exec();
    string FormatAddress(DWORD Address);
    void OutputLineAndReset();
    void SetArch(BYTE Arch);
    BYTE GetArch();
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
    void SetOffsetAddressEnd(DWORD OffsetAddressEnd);
    DWORD GetOffsetAddressEnd();
    void AddressInc(DWORD IncVal);
    void SetCntAddress(DWORD CntAddress);
    DWORD GetCntAddress();
    stringstream& GetAsmStream();
    stringstream& GetBinStream();
    ifstream& GetInputFile();
    ofstream& GetOutputAddrFile();
    ofstream& GetOutputBinFile();
    ofstream& GetOutputAsmFile();
    BYTE ReadByte();
    WORD ReadWord(BYTE ByteOrder = UDASM_UNKNOWN_ENDIAN);
    DWORD ReadDWord(BYTE ByteOrder = UDASM_UNKNOWN_ENDIAN);
    string FormatByte(BYTE CntByte, BYTE SMod = UNSIGNED);
    string FormatBinWord(WORD CntWord);
    string FormatAsmWord(WORD CntWord);
    string FormatBinDWord(DWORD CntDWord);
    string FormatAsmDWord(DWORD CntDWord);
    string ParseMemoryOperand(BYTE Opcode, BYTE MODRM, BYTE OpSize = OPSIZE_8_16_32);
    string ParseRegisterOperand(BYTE Opcode, BYTE REG, BYTE OpSize = OPSIZE_8_16_32);
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
