//
//  DASM.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include "DASM.h"

DASM::DASM(string FileName, BYTE Arch, BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder)
{
    this->BaseInit(CPUMode, AddressMode, ByteOrder);
    switch (Arch) {
        case INTEL_X86:
            this->INTEL_X86_Init();
            this->INTEL_X86_Exec(FileName);
            break;
        case AT_AND_T:
            this->AT_AND_T_Init();
            this->AT_AND_T_Exec(FileName);
            break;
        default:
            break;
    }
}

DASM::~DASM()
{
    
}

void DASM::BaseInit(BYTE DefaultCPUMode, BYTE DefaultAddressMode, BYTE DefaultByteOrder)
{
    this->SetDefaultCPUMode(DefaultCPUMode);
    this->SetDefaultAddressMode(DefaultAddressMode);
    this->SetDefaultByteOrder(DefaultByteOrder); 
}

void DASM::ResetMode()
{
    this->SetCPUMode(this->GetDefaultCPUMode());
    this->SetAddressMode(this->GetDefaultAddressMode());
}

void DASM::INTEL_X86_Init()
{
    for (int i = 0; i < 4; i++)
    {
        InstructionDef::GetPrefix(i) = InstructionDef::InitPrefix(i);
    }
    InstructionDef::GetSinglePrefixName() = InstructionDef::InitSinglePrefixName();
    InstructionDef::GetOpcode() = InstructionDef::InitOpcode();
    InstructionDef::GetReg(REGSIZE_8) = InstructionDef::InitReg(REGSIZE_8);
    InstructionDef::GetReg(REGSIZE_16) = InstructionDef::InitReg(REGSIZE_16);
    InstructionDef::GetReg(REGSIZE_32) = InstructionDef::InitReg(REGSIZE_32);
    InstructionDef::GetReg(ADDRESSSIZE_16) = InstructionDef::InitReg(ADDRESSSIZE_16);
    InstructionDef::GetReg(SEGMENT_REG) = InstructionDef::InitReg(SEGMENT_REG);
    InstructionDef::GetAddressHead() = InstructionDef::InitAddressHead();
}

void DASM::AT_AND_T_Init()
{
    
}

void DASM::INTEL_X86_Exec(string FileName)
{
    ifstream ExeFile(FileName);
    ExeFile.seekg(1024);
    int Line = 0;
    Instruction *CntInstruction = new Instruction();
    stringstream BinStream;
    stringstream AsmStream;
    long long InstructionStartPos = ExeFile.tellg();
    long long PrefixPos[4];
    memset(PrefixPos, -1, sizeof(PrefixPos));
    BYTE PrefixConflicting = NO_PREFIX_CONFLICTION;
    while (ExeFile)
    {
        if (Line > 60)
            break;
        BYTE CntByte = this->ReadByte(ExeFile);
        BinStream << this->FormatByte(CntByte) << " ";
        string BinByte;
        string AsmVal;
        if (PrefixConflicting != NO_PREFIX_CONFLICTION)
        {
            Line++;
            cout << setw(4) << setfill('0') << Line << " ";
            while (BinStream >> BinByte)
            {
                cout << BinByte << " ";
            }
            cout << "| ";
            string Val = InstructionDef::GetSinglePrefixName()[CntByte];
            AsmStream << Val + " ";
            while (AsmStream >> AsmVal)
            {
                cout << AsmVal << " ";
            }
            cout << endl;
            this->StringStreamClear(AsmStream);
            this->StringStreamClear(BinStream);
            this->ResetMode();
            if (ExeFile.tellg() == PrefixPos[PrefixConflicting])
            {
                InstructionStartPos = ExeFile.tellg();
                PrefixConflicting = NO_PREFIX_CONFLICTION;
            }
            continue;
        }

        // 判断指令前缀
        // 第一组
        if (InstructionDef::GetPrefix(0).find(CntByte) != InstructionDef::GetPrefix(0).end())
        {
            if (CntInstruction->GetRepeatPrefix() != NULL_VAL)
            {
                ExeFile.seekg(InstructionStartPos);
                PrefixConflicting = 0;
                CntInstruction->Clear();
                this->StringStreamClear(AsmStream);
                this->StringStreamClear(BinStream);
                continue;
            }
            string Val = InstructionDef::GetPrefix(0)[CntByte];
            AsmStream << Val + " ";
            switch (CntByte) {
                case REPEAT_PREFIX_LOCK:
                    break;
                case REPEAT_PREFIX_REP: // REPEAT_PREFIX_REPE, REPEAT_PREFIX_REPZ
                    break;
                case REPEAT_PREFIX_REPNE: // REPEAT_PREFIX_REPNZ
                    break;
                default:
                    break;
            }
            CntInstruction->SetRepeatPrefix(CntByte);
            PrefixPos[0] = ExeFile.tellg();
            continue;
        }
        // 第二组
        if (InstructionDef::GetPrefix(1).find(CntByte) != InstructionDef::GetPrefix(1).end())
        {
            if (CntInstruction->GetSegmentPrefix() != NULL_VAL)
            {
                ExeFile.seekg(InstructionStartPos);
                PrefixConflicting = 1;
                CntInstruction->Clear();
                this->StringStreamClear(AsmStream);
                this->StringStreamClear(BinStream);
                continue;
            }
            switch (CntByte) {
                case SEGMENT_PREFIX_ES:
                    this->SetDefaultSegmentRegister(REG_ES);
                    break;
                case SEGMENT_PREFIX_CS:
                    this->SetDefaultSegmentRegister(REG_CS);
                    break;
                case SEGMENT_PREFIX_SS:
                    this->SetDefaultSegmentRegister(REG_SS);
                    break;
                case SEGMENT_PREFIX_DS:
                    this->SetDefaultSegmentRegister(REG_DS);
                    break;
                case SEGMENT_PREFIX_FS:
                    this->SetDefaultSegmentRegister(REG_FS);
                    break;
                case SEGMENT_PREFIX_GS:
                    this->SetDefaultSegmentRegister(REG_GS);
                    break;
                default:
                    break;
            }
            CntInstruction->SetSegmentPrefix(CntByte);
            PrefixPos[1] = ExeFile.tellg();
            continue;
        }
        // 第三组
        if (InstructionDef::GetPrefix(2).find(CntByte) != InstructionDef::GetPrefix(2).end())
        {
            if (CntInstruction->GetOperandPrefix() != NULL_VAL)
            {
                ExeFile.seekg(InstructionStartPos);
                PrefixConflicting = 2;
                CntInstruction->Clear();
                this->StringStreamClear(AsmStream);
                this->StringStreamClear(BinStream);
                continue;
            }
            switch (CntByte) {
                case OPERAND_PREFIX:
                    switch (this->GetCPUMode()) {
                        case CPU_MODE_32:
                            this->SetCPUMode(CPU_MODE_16);
                            break;
                        case CPU_MODE_16:
                            this->SetCPUMode(CPU_MODE_32);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            CntInstruction->SetOperandPrefix(CntByte);
            PrefixPos[2] = ExeFile.tellg();
            continue;
        }
        // 第四组
        if (InstructionDef::GetPrefix(3).find(CntByte) != InstructionDef::GetPrefix(3).end())
        {
            if (CntInstruction->GetAddressPrefix() != NULL_VAL)
            {
                ExeFile.seekg(InstructionStartPos);
                PrefixConflicting = 3;
                CntInstruction->Clear();
                this->StringStreamClear(AsmStream);
                this->StringStreamClear(BinStream);
                continue;
            }
            switch (CntByte) {
                case ADDRESS_PREFIX:
                    switch (this->GetCPUMode()) {
                        case CPU_MODE_32:
                            this->SetAddressMode(ADDRESS_MODE_16);
                            break;
                        case CPU_MODE_16:
                            this->SetAddressMode(ADDRESS_MODE_32);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            CntInstruction->SetAddressPrefix(CntByte);
            PrefixPos[3] = ExeFile.tellg();
            continue;
        }
    
        BYTE DISP8, I8, R8, RM8, R16, RM16, R32, RM32;
        BYTE MOD, Opcode2, RM, MODRM;
        BYTE Base, Index, Scale, SIB;
        WORD I16, DISP16;
        DWORD I32, DISP32;
        switch (CntByte) {
            case OPCODE_ADD + RM8_R8:
            case OPCODE_ADD + RM16_R16:
            case OPCODE_ADD + R8_RM8:
            case OPCODE_ADD + R16_RM16:
            case OPCODE_ADD + AL_I8:
            case OPCODE_ADD + RAX_I16:
            case OPCODE_OR + RM8_R8:
            case OPCODE_OR + RM16_R16:
            case OPCODE_OR + R8_RM8:
            case OPCODE_OR + R16_RM16:
            case OPCODE_OR + AL_I8:
            case OPCODE_OR + RAX_I16:
            case OPCODE_ADC + RM8_R8:
            case OPCODE_ADC + RM16_R16:
            case OPCODE_ADC + R8_RM8:
            case OPCODE_ADC + R16_RM16:
            case OPCODE_ADC + AL_I8:
            case OPCODE_ADC + RAX_I16:
            case OPCODE_SBB + RM8_R8:
            case OPCODE_SBB + RM16_R16:
            case OPCODE_SBB + R8_RM8:
            case OPCODE_SBB + R16_RM16:
            case OPCODE_SBB + AL_I8:
            case OPCODE_SBB + RAX_I16:
            case OPCODE_AND + RM8_R8:
            case OPCODE_AND + RM16_R16:
            case OPCODE_AND + R8_RM8:
            case OPCODE_AND + R16_RM16:
            case OPCODE_AND + AL_I8:
            case OPCODE_AND + RAX_I16:
            case OPCODE_SUB + RM8_R8:
            case OPCODE_SUB + RM16_R16:
            case OPCODE_SUB + R8_RM8:
            case OPCODE_SUB + R16_RM16:
            case OPCODE_SUB + AL_I8:
            case OPCODE_SUB + RAX_I16:
            case OPCODE_XOR + RM8_R8:
            case OPCODE_XOR + RM16_R16:
            case OPCODE_XOR + R8_RM8:
            case OPCODE_XOR + R16_RM16:
            case OPCODE_XOR + AL_I8:
            case OPCODE_XOR + RAX_I16:
            case OPCODE_CMP + RM8_R8:
            case OPCODE_CMP + RM16_R16:
            case OPCODE_CMP + R8_RM8:
            case OPCODE_CMP + R16_RM16:
            case OPCODE_CMP + AL_I8:
            case OPCODE_CMP + RAX_I16:
                AsmStream << InstructionDef::GetOpcode()[CntByte - GET_RM(CntByte)] << " ";
                switch (GET_RM(CntByte)) {
                    case RM8_R8:
                        this->ProcessMODRM_RM8_R8(ExeFile, BinStream, AsmStream);
                        break;
                    case RM16_R16:
                        this->ProcessMODRM_RM16_R16(ExeFile, BinStream, AsmStream, CntByte);
                        break;
                    case R8_RM8:
                        this->ProcessMODRM_R8_RM8(ExeFile, BinStream, AsmStream);
                        break;
                    case R16_RM16:
                        this->ProcessMODRM_RM16_R16(ExeFile, BinStream, AsmStream, CntByte);
                        break;
                    case AL_I8:
                        this->ProcessMODRM_AL_I8(ExeFile, BinStream, AsmStream);
                        break;
                    case RAX_I16:
                        this->ProcessMODRM_RAX_I16(ExeFile, BinStream, AsmStream);
                        break;
                    default:
                        AsmStream << "??? ";
                        break;
                }
                break;
            case OPCODE_NOP:
                AsmStream << InstructionDef::GetOpcode()[OPCODE_NOP];
                break;
            default:
                AsmStream << "??? ";
                break;
        }
    
        //
        CntInstruction->Clear();
        Line++;
        cout << setw(4) << setfill('0') << Line << " ";
        while (BinStream >> BinByte)
        {
            cout << BinByte << " ";
        }
        cout << "| ";
        while (AsmStream >> AsmVal)
        {
            cout << AsmVal << " ";
        }
        cout << endl;
        this->StringStreamClear(AsmStream);
        this->StringStreamClear(BinStream);
        this->ResetMode();
        InstructionStartPos = ExeFile.tellg();
    }
    cout << endl;
    ExeFile.close();
}

void DASM::AT_AND_T_Exec(string FileName)
{
    
}

void DASM::SetDefaultCPUMode(BYTE DefaultCPUMode)
{
    this->DefaultCPUMode = DefaultCPUMode;
}

BYTE DASM::GetDefaultCPUMode()
{
    return this->DefaultCPUMode;
}

void DASM::SetDefaultAddressMode(BYTE DefaultAddressMode)
{
    this->DefaultAddressMode = DefaultAddressMode;
}

BYTE DASM::GetDefaultAddressMode()
{
    return this->DefaultAddressMode;
}

void DASM::SetCPUMode(BYTE CPUMode)
{
    this->CPUMode = CPUMode;
}

BYTE DASM::GetCPUMode()
{
    return this->CPUMode;
}

void DASM::SetAddressMode(BYTE AddressMode)
{
    this->AddressMode = AddressMode;
}

BYTE DASM::GetAddressMode()
{
    return this->AddressMode;
}

void DASM::SetDefaultSegmentRegister(BYTE Register)
{
    this->DefaultSegmentRegister = Register;
}

BYTE DASM::GetDefaultSegmentRegister()
{
    return this->DefaultSegmentRegister;
}

void DASM::SetDefaultByteOrder(BYTE DefaultByteOrder)
{
    this->DefaultByteOrder = DefaultByteOrder;
}

BYTE DASM::GetDefaultByteOrder()
{
    return this->DefaultByteOrder;
}

BYTE DASM::ReadByte(ifstream &ExeFile)
{
    BYTE CntByte = 0;
    if (ExeFile)
    {
        ExeFile.read((char*)&CntByte, 1);
    }
    return CntByte;
}

WORD DASM::ReadWord(ifstream &ExeFile)
{
    BYTE CntByte[2];
    for (int i = 0; i < 2; i++)
    {
        CntByte[i] = this->ReadByte(ExeFile);
    }
    return MAKE_WORD(CntByte[0], CntByte[1]);
}

DWORD DASM::ReadDWord(ifstream &ExeFile)
{
    WORD CntWord[2];
    for (int i = 0; i < 2; i++)
    {
        CntWord[i] = this->ReadWord(ExeFile);
    }
    return MAKE_DWORD_2(CntWord[0], CntWord[1]);
}

string DASM::FormatByte(BYTE CntByte)
{
    stringstream BinStream;
    BinStream << setiosflags(ios::uppercase) << setfill('0') << setw(2) << hex << (int)CntByte;
    string RetVal = "";
    BinStream >> RetVal;
    return RetVal;
}

string DASM::FormatBinWord(WORD CntWord)
{
    string RetVal =
    this->FormatByte(GET_1ST_BYTE_FROM_WORD(CntWord)) + " " +
    this->FormatByte(GET_2ND_BYTE_FROM_WORD(CntWord));
    return RetVal;
}

string DASM::FormatAsmWord(WORD CntWord)
{
    string RetVal = "";
    if (this->GetDefaultByteOrder() == UDASM_LITTLE_ENDIAN)
    {
        RetVal =
        this->FormatByte(GET_2ND_BYTE_FROM_WORD(CntWord)) +
        this->FormatByte(GET_1ST_BYTE_FROM_WORD(CntWord));
    }
    else if (this->GetDefaultByteOrder() == UDASM_BIG_ENDIAN)
    {
        RetVal =
        this->FormatByte(GET_1ST_BYTE_FROM_WORD(CntWord)) +
        this->FormatByte(GET_2ND_BYTE_FROM_WORD(CntWord));
    }
    return RetVal;
}

string DASM::FormatBinDWord(DWORD CntDWord)
{
    string RetVal =
    this->FormatByte(GET_1ST_BYTE_FROM_DWORD(CntDWord)) + " " +
    this->FormatByte(GET_2ND_BYTE_FROM_DWORD(CntDWord)) + " " +
    this->FormatByte(GET_3RD_BYTE_FROM_DWORD(CntDWord)) + " " +
    this->FormatByte(GET_4TH_BYTE_FROM_DWORD(CntDWord));
    return RetVal;
}

string DASM::FormatAsmDWord(DWORD CntDWord)
{
    string RetVal = "";
    if (this->GetDefaultByteOrder() == UDASM_LITTLE_ENDIAN)
    {
        RetVal =
        this->FormatByte(GET_4TH_BYTE_FROM_DWORD(CntDWord)) +
        this->FormatByte(GET_3RD_BYTE_FROM_DWORD(CntDWord)) +
        this->FormatByte(GET_2ND_BYTE_FROM_DWORD(CntDWord)) +
        this->FormatByte(GET_1ST_BYTE_FROM_DWORD(CntDWord));
    }
    else if (this->GetDefaultByteOrder() == UDASM_BIG_ENDIAN)
    {
        RetVal =
        this->FormatByte(GET_1ST_BYTE_FROM_DWORD(CntDWord)) +
        this->FormatByte(GET_2ND_BYTE_FROM_DWORD(CntDWord)) +
        this->FormatByte(GET_3RD_BYTE_FROM_DWORD(CntDWord)) +
        this->FormatByte(GET_4TH_BYTE_FROM_DWORD(CntDWord));
    }
    return RetVal;
}

void DASM::ProcessMODRM_RM8_R8(ifstream &ExeFile, stringstream &BinStream, stringstream &AsmStream)
{
    BYTE DISP8, I8, R8, RM8, R16, RM16, R32, RM32;
    BYTE MOD, Opcode2, RM, MODRM;
    BYTE Base, Index, Scale, SIB;
    WORD I16, DISP16;
    DWORD I32, DISP32;
    MODRM = this->ReadByte(ExeFile);
    BinStream << this->FormatByte(MODRM) << " ";
    MOD = GET_MOD(MODRM);
    R8 = GET_REG(MODRM);
    RM8 = GET_RM(MODRM);
    switch (MOD)
    {
        case MOD_M_NO_DISPLACEMENT:
        case MOD_M_DISPLACEMENT_8:
        case MOD_M_DISPLACEMENT_16:
            switch (RM8)
            {
                case RM_ONLY_DISPLACEMENT_16_FLAG:
                    switch (this->GetCPUMode())
                    {
                        case CPU_MODE_16:
                            DISP16 = this->ReadWord(ExeFile);
                            BinStream << this->FormatBinWord(DISP16) << " ";
                            AsmStream 
                            << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                            << "[" << this->FormatAsmWord(DISP16) << "], "
                            << InstructionDef::GetReg(REGSIZE_8)[R8];
                            break;
                        case CPU_MODE_32:
                            DISP32 = this->ReadDWord(ExeFile);
                            BinStream << this->FormatBinDWord(DISP32) << " ";
                            AsmStream 
                            << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                            << "[" << this->FormatAsmDWord(DISP32) << "], "
                            << InstructionDef::GetReg(REGSIZE_8)[R8];
                            break;
                        default:
                            break;
                    }
                    break;
                case RM_SIB_FLAG:
                    SIB = this->ReadByte(ExeFile);
                    Scale = GET_SCALE(SIB);
                    Index = GET_INDEX(SIB);
                    Base = GET_BASE(SIB);
                    BinStream << this->FormatByte(SIB) << " ";
                    if (Base == RM_ONLY_DISPLACEMENT_16_FLAG)
                    {
                        AsmStream 
                        << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                        << "[" << InstructionDef::GetReg(REGSIZE_32)[REG_EAX_32] << "], "
                        << InstructionDef::GetReg(REGSIZE_8)[REG_AL_8];
                        break;
                    }
                    if (Index == RM_SIB_FLAG)
                    {
                        switch (this->GetCPUMode())
                        {
                            case CPU_MODE_16:
                                DISP16 = this->ReadWord(ExeFile);
                                BinStream << this->FormatBinWord(DISP16) << " ";
                                AsmStream 
                                << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                                << "[" << this->FormatAsmWord(DISP16) << "], "
                                << InstructionDef::GetReg(REGSIZE_8)[REG_AL_8];
                                break;
                            case CPU_MODE_32:
                                DISP32 = this->ReadDWord(ExeFile);
                                BinStream << this->FormatBinDWord(DISP32) << " ";
                                AsmStream 
                                << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                                << "[" << this->FormatAsmDWord(DISP32) << "], "
                                << InstructionDef::GetReg(REGSIZE_8)[REG_AL_8];  
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    AsmStream 
                    << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                    << "[" << InstructionDef::GetReg(REGSIZE_32)[Base] << " + "
                    << InstructionDef::GetReg(REGSIZE_8)[Index] << " ";
                    if (Scale != 0)
                    {
                        AsmStream << "* " << (2 << Scale); 
                    }
                    switch (MOD)
                    {
                        case MOD_M_NO_DISPLACEMENT:
                            break;
                        case MOD_M_DISPLACEMENT_8:
                            DISP8 = this->ReadByte(ExeFile);
                            BinStream << this->FormatByte(DISP8) << " ";
                            AsmStream << "+ " << this->FormatByte(DISP8) << "h";
                            break;
                        case MOD_M_DISPLACEMENT_16:
                            switch (this->GetCPUMode())
                            {
                                case CPU_MODE_16:
                                    DISP16 = this->ReadWord(ExeFile);
                                    BinStream << this->FormatBinWord(DISP16) << " ";
                                    AsmStream << "+ " << this->FormatAsmWord(DISP16);
                                    break;
                                case CPU_MODE_32:
                                    DISP32 = this->ReadDWord(ExeFile);
                                    BinStream << this->FormatBinDWord(DISP32) << " ";
                                    AsmStream << "+ " << this->FormatAsmDWord(DISP32);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                    AsmStream 
                    << "], " << InstructionDef::GetReg(REGSIZE_8)[R8];
                    break;
                default:
                    switch (this->GetAddressMode())
                    {
                        case ADDRESS_MODE_16:
                            AsmStream 
                            << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                            << "[" << InstructionDef::GetReg(ADDRESSSIZE_16)[RM8] << "], "
                            << InstructionDef::GetReg(REGSIZE_8)[R8];
                            break;
                        case ADDRESS_MODE_32:
                            AsmStream 
                            << InstructionDef::GetAddressHead()[ADDRESSHEAD_8] << " "
                            << "[" << InstructionDef::GetReg(REGSIZE_32)[RM8] << "], "
                            << InstructionDef::GetReg(REGSIZE_8)[R8];
                            break;
                        default:
                            break;
                    }
                    break;
            } 
            break;
        case MOD_R_NO_DISPLACEMENT:
            AsmStream
            << InstructionDef::GetReg(REGSIZE_8)[RM8] << ", "
            << InstructionDef::GetReg(REGSIZE_8)[R8];
            break;
        default:
            break;
    }
}
//01 01/111/100 10/000/001 33
void DASM::ProcessMODRM_RM16_R16(ifstream &ExeFile, stringstream &BinStream, stringstream &AsmStream, BYTE Opcode)
{
    BYTE DISP8 = 0, I8 = 0;
    BYTE MOD = 0, Opcode2 = 0, REG = 0, RM = 0, MODRM = 0;
    BYTE Base = 0, Index = 0, Scale = 0, SIB = 0;
    WORD I16 = 0, DISP16 = 0;
    DWORD I32 = 0, DISP32 = 0;
    string Operand[2];
    MODRM = this->ReadByte(ExeFile);
    BinStream << this->FormatByte(MODRM) << " ";
    MOD = GET_MOD(MODRM);
    REG = GET_REG(MODRM);
    RM = GET_RM(MODRM);
    switch (MOD)
    {
        case MOD_M_NO_DISPLACEMENT:
        case MOD_M_DISPLACEMENT_8:
        case MOD_M_DISPLACEMENT_16:
            switch (this->GetCPUMode())
            {
                case CPU_MODE_16:
                    Operand[0] += InstructionDef::GetAddressHead()[ADDRESSHEAD_16] + " ";
                    break;
                case CPU_MODE_32:
                    Operand[0] += InstructionDef::GetAddressHead()[ADDRESSHEAD_32] + " ";
                    break;
                default:
                    break;
            }
            switch (this->GetAddressMode()) {
                case ADDRESS_MODE_16: // 16 Bits Addressing
                    Operand[0] += "[";
                    switch (MOD) {
                        case MOD_M_NO_DISPLACEMENT:
                            if (RM == RM_ADDRESS16_SMALL_FLAG)
                            {
                                I16 = this->ReadWord(ExeFile);
                                BinStream << this->FormatBinWord(I16) << " ";
                                Operand[0] += "small " + this->FormatAsmWord(I16) + "h]";
                            }
                            break;
                        case MOD_M_DISPLACEMENT_8:
                            DISP8 = this->ReadByte(ExeFile);
                            BinStream << this->FormatByte(DISP8) << " ";
                            Operand[0] += InstructionDef::GetReg(ADDRESSSIZE_16)[RM] + " + " + this->FormatByte(DISP8) + "h]";
                            break;
                        case MOD_M_DISPLACEMENT_16:
                            DISP16 = this->ReadWord(ExeFile);
                            BinStream << this->FormatBinWord(DISP16) << " ";
                            Operand[0] += InstructionDef::GetReg(ADDRESSSIZE_16)[RM] + " + " + this->FormatAsmWord(DISP16) + "h]";
                            break;
                        default:
                            break;
                    }
                    switch (this->GetCPUMode())
                    {
                        case CPU_MODE_16:
                            Operand[1] += InstructionDef::GetReg(REGSIZE_16)[REG];
                            break;
                        case CPU_MODE_32:
                            Operand[1] += InstructionDef::GetReg(REGSIZE_32)[REG];
                            break;
                        default:
                            break;
                    }
                    break;
                case ADDRESS_MODE_32: // 32 Bits Addressing
                    if (MOD == MOD_M_NO_DISPLACEMENT && RM == RM_ONLY_DISPLACEMENT_16_FLAG)
                    {
                        Operand[0] += "[" + InstructionDef::GetReg(REGSIZE_32)[REG_EAX_32] + "]";
                        switch (this->GetCPUMode())
                        {
                            case CPU_MODE_16:
                                Operand[1] += InstructionDef::GetReg(REGSIZE_16)[REG_AX_16];
                                break;
                            case CPU_MODE_32:
                                Operand[1] += InstructionDef::GetReg(REGSIZE_32)[REG_EAX_32];
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    switch (RM)
                    {
                        case RM_SIB_FLAG:
                            SIB = this->ReadByte(ExeFile);
                            Scale = GET_SCALE(SIB);
                            Index = GET_INDEX(SIB);
                            Base = GET_BASE(SIB);
                            BinStream << this->FormatByte(SIB) << " ";
                            if (Base == RM_ONLY_DISPLACEMENT_16_FLAG)
                            {
                                DISP32 = this->ReadDWord(ExeFile);
                                BinStream << this->FormatBinDWord(DISP32) << " ";
                                Operand[0] += "[" + this->FormatAsmDWord(DISP32) + "h";
                            }
                            /*if (Index == RM_SIB_FLAG)
                            {
                                switch (this->GetCPUMode())
                                {
                                    case CPU_MODE_16:
                                        DISP16 = this->ReadWord(ExeFile);
                                        BinStream << this->FormatBinWord(DISP16) << " ";
                                        Operand[0] += "[" + this->FormatAsmWord(DISP16) + "h]";
                                        Operand[1] += InstructionDef::GetReg(REGSIZE_16)[REG_AX_16];
                                        break;
                                    case CPU_MODE_32:
                                        DISP32 = this->ReadDWord(ExeFile);
                                        BinStream << this->FormatBinDWord(DISP32) << " ";
                                        Operand[0] += "[" + this->FormatAsmDWord(DISP32) + "h]";
                                        Operand[1] += InstructionDef::GetReg(REGSIZE_32)[REG_EAX_32];
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            }*/
                            else
                            {
                                Operand[0] += "[" + InstructionDef::GetReg(REGSIZE_32)[Base];
                            }
                            if (Index != RM_SIB_FLAG)
                            {
                                Operand[0] += " + " + InstructionDef::GetReg(REGSIZE_32)[Index];
                                if (Scale != 0)
                                {
                                    Operand[0] += " * " + string(1, BYTE(1 << Scale) + '0');
                                }
                            }
                            switch (MOD)
                            {
                                case MOD_M_NO_DISPLACEMENT:
                                    break;
                                case MOD_M_DISPLACEMENT_8:
                                    DISP8 = this->ReadByte(ExeFile);
                                    BinStream << this->FormatByte(DISP8) << " ";
                                    Operand[0] += " + " + this->FormatByte(DISP8) + "h";
                                    break;
                                case MOD_M_DISPLACEMENT_16:
                                    switch (this->GetCPUMode())
                                    {
                                        case CPU_MODE_16:
                                            DISP16 = this->ReadWord(ExeFile);
                                            BinStream << this->FormatBinWord(DISP16) << " ";
                                            Operand[0] += " + " + this->FormatAsmWord(DISP16);
                                            break;
                                        case CPU_MODE_32:
                                            DISP32 = this->ReadDWord(ExeFile);
                                            BinStream << this->FormatBinDWord(DISP32) << " ";
                                            Operand[0] += " + " + this->FormatAsmWord(DISP32);
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            Operand[0] += "]";
                            switch (this->GetCPUMode())
                            {
                                case CPU_MODE_16:
                                    Operand[1] += InstructionDef::GetReg(REGSIZE_16)[REG];
                                    break;
                                case CPU_MODE_32:
                                    Operand[1] += InstructionDef::GetReg(REGSIZE_32)[REG];
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            switch (MOD) {
                                case MOD_M_DISPLACEMENT_8:
                                    I8 = this->ReadByte(ExeFile);
                                    BinStream << this->FormatByte(I8) << " ";
                                    break;
                                case MOD_M_DISPLACEMENT_16:
                                    I16 = this->ReadWord(ExeFile);
                                    BinStream << this->FormatBinWord(I16) << " ";
                                default:
                                    break;
                            }
                            switch (this->GetAddressMode())
                            {
                                case ADDRESS_MODE_16:
                                    Operand[0] += "[" + InstructionDef::GetReg(ADDRESSSIZE_16)[RM];
                                    switch (MOD) {
                                        case MOD_M_DISPLACEMENT_8:
                                            Operand[0] += " + " + this->FormatByte(I8) + "h";
                                            break;
                                        case MOD_M_DISPLACEMENT_16:
                                            Operand[0] += " + " + this->FormatAsmWord(I16) + "h";
                                        default:
                                            break;
                                    }
                                    Operand[0] += "]";
                                    Operand[1] += InstructionDef::GetReg(REGSIZE_16)[REG];
                                    break;
                                case ADDRESS_MODE_32:
                                    Operand[0] += "[" + InstructionDef::GetReg(REGSIZE_32)[RM];
                                    switch (MOD) {
                                        case MOD_M_DISPLACEMENT_8:
                                            Operand[0] += " + " + this->FormatByte(I8) + "h";
                                            break;
                                        case MOD_M_DISPLACEMENT_16:
                                            Operand[0] += " + " + this->FormatAsmWord(I16) + "h";
                                        default:
                                            break;
                                    }
                                    Operand[0] += "]";
                                    Operand[1] += InstructionDef::GetReg(REGSIZE_32)[REG];
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case MOD_R_NO_DISPLACEMENT:
            switch (this->GetCPUMode())
            {
                case CPU_MODE_16:
                    Operand[0] += InstructionDef::GetReg(REGSIZE_16)[RM];
                    Operand[1] += InstructionDef::GetReg(REGSIZE_16)[REG];
                    break;
                case CPU_MODE_32:
                    Operand[0] += InstructionDef::GetReg(REGSIZE_32)[RM];
                    Operand[1] += InstructionDef::GetReg(REGSIZE_32)[REG];
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    if (GET_D_BIT(Opcode) == 0x00) // Judge Operands Order
    {
        AsmStream << Operand[0] << ", " << Operand[1];
    }
    else
    {
        AsmStream << Operand[1] << ", " << Operand[0];
    }
}

void DASM::ProcessMODRM_R8_RM8(ifstream &ExeFile, stringstream &BinStream, stringstream &AsmStream)
{
    
}

void DASM::ProcessMODRM_R16_RM16(ifstream &ExeFile, stringstream &BinStream, stringstream &AsmStream)
{

}

void DASM::ProcessMODRM_AL_I8(ifstream &ExeFile, stringstream &BinStream, stringstream &AsmStream)
{
    BYTE DISP8, I8, R8, RM8, R16, RM16, R32, RM32;
    BYTE MOD, Opcode2, RM, MODRM;
    BYTE Base, Index, Scale, SIB;
    WORD I16, DISP16;
    DWORD I32, DISP32;
    I8 = this->ReadByte(ExeFile);
    BinStream << this->FormatByte(I8) << " ";
    AsmStream 
    << InstructionDef::GetReg(REGSIZE_8)[REG_AL_8] << ", "
    << this->FormatByte(I8) << "h";
}

void DASM::ProcessMODRM_RAX_I16(ifstream &ExeFile, stringstream &BinStream, stringstream &AsmStream)
{
    BYTE DISP8, I8, R8, RM8, R16, RM16, R32, RM32;
    BYTE MOD, Opcode2, RM, MODRM;
    BYTE Base, Index, Scale, SIB;
    WORD I16, DISP16;
    DWORD I32, DISP32;
    switch (this->GetCPUMode()) {
        case CPU_MODE_16:
            I16 = this->ReadWord(ExeFile);
            BinStream << this->FormatBinWord(I16) << " ";
            AsmStream 
            << InstructionDef::GetReg(REGSIZE_16)[REG_AX_16] << ", "
            << this->FormatAsmWord(I16);
            break;
        case CPU_MODE_32:
            I32 = this->ReadDWord(ExeFile);
            BinStream << this->FormatBinDWord(I32) << " ";
            AsmStream 
            << InstructionDef::GetReg(REGSIZE_32)[REG_EAX_32] << ", "
            << this->FormatAsmDWord(I32);
            break;
        default:
            break;
    }
}

void DASM::StringStreamClear(stringstream &SStream)
{
    SStream.clear();
    SStream.str("");
}