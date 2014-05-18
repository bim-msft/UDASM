//
//  DASM.cpp
//  UDASM
//
//  Created by Uranux on 14-4-29.
//  Copyright (c) 2014年 Uranux. All rights reserved.
//

#include "DASM.h"

DASM::DASM(string FileName,  DWORD LoadAddress, DWORD OffsetAddress, BYTE Arch, BYTE CPUMode, BYTE AddressMode, BYTE ByteOrder)
{
    this->BaseInit(CPUMode, AddressMode, ByteOrder);
    this->FileInit(FileName, LoadAddress, OffsetAddress);
    switch (Arch) {
        case INTEL_X86:
            this->INTEL_X86_Init();
            this->INTEL_X86_Exec();
            break;
        case AT_AND_T:
            this->AT_AND_T_Init();
            this->AT_AND_T_Exec();
            break;
        default:
            break;
    }
}

DASM::~DASM()
{
    
}

void DASM::FileInit(string FileName, DWORD LoadAddress, DWORD OffsetAddress)
{
    this->GetExeFile() = ifstream(FileName);
    this->SetLoadAddress(LoadAddress);
    this->SetOffsetAddress(OffsetAddress);
    this->SetCntAddress(LoadAddress + OffsetAddress);
    this->GetAsmStream() = stringstream();
    this->GetBinStream() = stringstream();
}

void DASM::BaseInit(BYTE DefaultCPUMode, BYTE DefaultAddressMode, BYTE DefaultByteOrder)
{
    this->SetDefaultCPUMode(DefaultCPUMode);
    this->SetDefaultAddressMode(DefaultAddressMode);
    this->SetDefaultByteOrder(DefaultByteOrder);
    this->ResetMode();
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
    InstructionDef::GetSubOpcode_TestGroup() = InstructionDef::InitSubOpcode_TestGroup();
    InstructionDef::GetSubOpcode_AddGroup() = InstructionDef::InitSubOpcode_AddGroup();
    InstructionDef::GetSubOpcode_RolGroup() = InstructionDef::InitSubOpcode_RolGroup();
    InstructionDef::GetSubOpcode_FaddGroup() = InstructionDef::InitSubOpcode_FaddGroup();
    InstructionDef::GetSubOpcode_FldGroup() = InstructionDef::InitSubOpcode_FldGroup();
    InstructionDef::GetSubOpcode_Fld64Group() = InstructionDef::InitSubOpcode_Fld64Group();
    InstructionDef::GetSubOpcode_FiaddGroup() = InstructionDef::InitSubOpcode_FiaddGroup();
    InstructionDef::GetSubOpcode_FildGroup() = InstructionDef::InitSubOpcode_FildGroup();
    InstructionDef::GetSubOpcode_Fild16Group() = InstructionDef::InitSubOpcode_Fild16Group();
    InstructionDef::GetSubOpcode_Inc8Group() = InstructionDef::InitSubOpcode_Inc8Group();
    InstructionDef::GetSubOpcode_Inc16_32Group() = InstructionDef::InitSubOpcode_Inc16_32Group();
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

void DASM::INTEL_X86_Exec()
{
    this->GetExeFile().seekg(this->GetOffsetAddress());
    Instruction *CntInstruction = new Instruction();
    long long InstructionStartPos = this->GetExeFile().tellg();
    long long PrefixPos[4];
    memset(PrefixPos, -1, sizeof(PrefixPos));
    BYTE PrefixConflicting = NO_PREFIX_CONFLICTION;
    while (this->GetExeFile())
    {
        if (this->GetCntAddress() >= 0x402000)
            break;
        BYTE CntByte = this->ReadByte();
        string BinByte;
        string AsmVal;
        if (PrefixConflicting != NO_PREFIX_CONFLICTION)
        {
            cout << setiosflags(ios::uppercase) << setw(8) << setfill('0') << hex << this->GetCntAddress() << " | ";
            this->SetCntAddress(this->GetLoadAddress() + (DWORD)(this->GetExeFile().tellg()));
            while (this->GetBinStream() >> BinByte)
            {
                cout << BinByte << " ";
            }
            cout << "| ";
            string Val = InstructionDef::GetSinglePrefixName()[CntByte];
            this->GetAsmStream() << Val + " ";
            while (this->GetAsmStream() >> AsmVal)
            {
                cout << AsmVal << " ";
            }
            cout << endl;
            this->StringStreamClear(this->GetAsmStream());
            this->StringStreamClear(this->GetBinStream());
            this->ResetMode();
            if (this->GetExeFile().tellg() == PrefixPos[PrefixConflicting])
            {
                InstructionStartPos = this->GetExeFile().tellg();
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
                this->GetExeFile().seekg(InstructionStartPos);
                PrefixConflicting = 0;
                CntInstruction->Clear();
                this->StringStreamClear(this->GetAsmStream());
                this->StringStreamClear(this->GetBinStream());
                continue;
            }
            string Val = InstructionDef::GetPrefix(0)[CntByte];
            this->GetAsmStream() << Val + " ";
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
            PrefixPos[0] = this->GetExeFile().tellg();
            continue;
        }
        // 第二组
        if (InstructionDef::GetPrefix(1).find(CntByte) != InstructionDef::GetPrefix(1).end())
        {
            if (CntInstruction->GetSegmentPrefix() != NULL_VAL)
            {
                this->GetExeFile().seekg(InstructionStartPos);
                PrefixConflicting = 1;
                CntInstruction->Clear();
                this->StringStreamClear(this->GetAsmStream());
                this->StringStreamClear(this->GetBinStream());
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
            PrefixPos[1] = this->GetExeFile().tellg();
            continue;
        }
        // 第三组
        if (InstructionDef::GetPrefix(2).find(CntByte) != InstructionDef::GetPrefix(2).end())
        {
            if (CntInstruction->GetOperandPrefix() != NULL_VAL)
            {
                this->GetExeFile().seekg(InstructionStartPos);
                PrefixConflicting = 2;
                CntInstruction->Clear();
                this->StringStreamClear(this->GetAsmStream());
                this->StringStreamClear(this->GetBinStream());
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
            PrefixPos[2] = this->GetExeFile().tellg();
            continue;
        }
        // 第四组
        if (InstructionDef::GetPrefix(3).find(CntByte) != InstructionDef::GetPrefix(3).end())
        {
            if (CntInstruction->GetAddressPrefix() != NULL_VAL)
            {
                this->GetExeFile().seekg(InstructionStartPos);
                PrefixConflicting = 3;
                CntInstruction->Clear();
                this->StringStreamClear(this->GetAsmStream());
                this->StringStreamClear(this->GetBinStream());
                continue;
            }
            switch (CntByte) {
                case ADDRESS_PREFIX:
                    switch (this->GetAddressMode()) {
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
            PrefixPos[3] = this->GetExeFile().tellg();
            continue;
        }
        BYTE MODRM;
        BYTE I8;
        WORD I16;
        DWORD I32;
        DWORD TargetAddress;
        string Operand[2];
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
            case OPCODE_MOV + RM8_R8:
            case OPCODE_MOV + RM16_R16:
            case OPCODE_MOV + R8_RM8:
            case OPCODE_MOV + R16_RM16:
            case OPCODE_MOV + AL_I8:
            //case OPCODE_MOV + RAX_I16:
            case OPCODE_MOV + SEGR_RM:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte - GET_RM(CntByte)] << " ";
                switch (GET_RM(CntByte)) {
                    case RM8_R8:
                    case RM16_R16:
                    case R8_RM8:
                    case R16_RM16:
                        MODRM = this->ReadByte();
                        this->GetAsmStream() << this->ParseMODRM_RM_R(CntByte, MODRM);
                        break;
                    case AL_I8:
                    case RAX_I16:
                        this->GetAsmStream() << this->ParseRegisterOperand(CntByte, REG_EAX_32) << ", ";
                        this->GetAsmStream() << this->ParseImmediateOperand(CntByte);
                        break;
                    case SEGR_RM:
                        MODRM = this->ReadByte();
                        this->GetAsmStream() << InstructionDef::GetReg(SEGMENT_REG)[GET_REG(MODRM)] << ", ";
                        if (GET_MOD(MODRM) == MOD_R_NO_DISPLACEMENT)
                        {
                            this->GetAsmStream() << InstructionDef::GetReg(REGSIZE_16)[GET_RM(MODRM)];
                        }
                        else
                        {
                            this->GetAsmStream() << this->ParseMemoryOperand(CntByte, MODRM, OPSIZE_16);
                        }
                        break;
                    default:
                        this->GetAsmStream() << "??? ";
                        break;
                }
                break;
            case OPCODE_INC + REG_EAX_32:
            case OPCODE_INC + REG_ECX_32:
            case OPCODE_INC + REG_EDX_32:
            case OPCODE_INC + REG_EBX_32:
            case OPCODE_INC + REG_ESP_32:
            case OPCODE_INC + REG_EBP_32:
            case OPCODE_INC + REG_ESI_32:
            case OPCODE_INC + REG_EDI_32:
            case OPCODE_DEC + REG_EAX_32:
            case OPCODE_DEC + REG_ECX_32:
            case OPCODE_DEC + REG_EDX_32:
            case OPCODE_DEC + REG_EBX_32:
            case OPCODE_DEC + REG_ESP_32:
            case OPCODE_DEC + REG_EBP_32:
            case OPCODE_DEC + REG_ESI_32:
            case OPCODE_DEC + REG_EDI_32:
            case OPCODE_PUSH + REG_EAX_32:
            case OPCODE_PUSH + REG_ECX_32:
            case OPCODE_PUSH + REG_EDX_32:
            case OPCODE_PUSH + REG_EBX_32:
            case OPCODE_PUSH + REG_ESP_32:
            case OPCODE_PUSH + REG_EBP_32:
            case OPCODE_PUSH + REG_ESI_32:
            case OPCODE_PUSH + REG_EDI_32:
            case OPCODE_POP + REG_EAX_32:
            case OPCODE_POP + REG_ECX_32:
            case OPCODE_POP + REG_EDX_32:
            case OPCODE_POP + REG_EBX_32:
            case OPCODE_POP + REG_ESP_32:
            case OPCODE_POP + REG_EBP_32:
            case OPCODE_POP + REG_ESI_32:
            case OPCODE_POP + REG_EDI_32:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte - GET_RM(CntByte)] << " ";
                this->GetAsmStream() << InstructionDef::GetReg(this->GetCPUMode())[GET_RM(CntByte)];
                break;
            case OPCODE_PUSH_ES:
            case OPCODE_POP_ES:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << InstructionDef::GetReg(SEGMENT_REG)[REG_ES];
                break;
            case OPCODE_PUSH_CS:
            case OPCODE_POP_CS:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << InstructionDef::GetReg(SEGMENT_REG)[REG_CS];
                break;
            case OPCODE_PUSH_SS:
            case OPCODE_POP_SS:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << InstructionDef::GetReg(SEGMENT_REG)[REG_SS];
                break;
            case OPCODE_PUSH_DS:
            case OPCODE_POP_DS:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << InstructionDef::GetReg(SEGMENT_REG)[REG_DS];
                break;
            case OPCODE_PUSH_I16_I32:
            case OPCODE_PUSH_I8:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << (GET_7TH_BIT(CntByte) == 0x00 ? this->ParseImmediateOperand_I16_I32() : this->ParseImmediateOperand_I8(SIGNED));
                break;
            case OPCODE_TEST_GROUP + RM8_R8:
            case OPCODE_TEST_GROUP + RM16_R16:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_TestGroup()[GET_OPCODE2(MODRM)] << " ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_TEST_0:
                    case SUB_OPCODE_TEST_1:
                        this->GetAsmStream() << this->ParseMODRM_RM_IMM(CntByte, MODRM);
                        break;
                    default:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM);
                        break;
                }
                break;
            case OPCODE_IMUL_I16_I32_3OP:
            case OPCODE_IMUL_I8_3OP:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << this->ParseMODRM_R_RM_IMM(CntByte, MODRM);
                break;
            case OPCODE_INS + RM8_R8:
            case OPCODE_INS + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte - GET_W_BIT(CntByte)] << " ";
                this->GetAsmStream() << this->ParseMemoryOperand(CntByte, REG_EDI_32) << ", dx";
                break;
            case OPCODE_OUTS + RM8_R8:
            case OPCODE_OUTS + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte - GET_W_BIT(CntByte)] << " ";
                this->GetAsmStream() << "dx, " << this->ParseMemoryOperand(CntByte, REG_ESI_32);
                break;
            case OPCODE_JO:
            case OPCODE_JNO:
            case OPCODE_JB:
            case OPCODE_JNB:
            case OPCODE_JE:
            case OPCODE_JNE:
            case OPCODE_JBE:
            case OPCODE_JA:
            case OPCODE_JS:
            case OPCODE_JNS:
            case OPCODE_JPE:
            case OPCODE_JPO:
            case OPCODE_JL:
            case OPCODE_JGE:
            case OPCODE_JLE:
            case OPCODE_JG:
            case OPCODE_LOOPNZ:
            case OPCODE_LOOPZ:
            case OPCODE_LOOP:
            case OPCODE_JECXZ:
            case OPCODE_JMP:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << "short ";
                I8 = this->ReadByte();
                TargetAddress = CntAddress + (char)I8 + (DWORD)(this->GetExeFile().tellg() - InstructionStartPos);
                this->GetCPUMode() == CPU_MODE_16 ? TargetAddress &= 0x0000FFFF : 0;
                this->GetAsmStream() << setiosflags(ios::uppercase) << setw(this->GetCPUMode() == CPU_MODE_16 ? 4 : 8) << setfill('0') << hex << TargetAddress << "h";
                break;
            case OPCODE_ADD_GROUP:
            case OPCODE_ADD_GROUP + 0x01:
            case OPCODE_ADD_GROUP + 0x02:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_AddGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM_IMM(CntByte, MODRM);
                break;
            case OPCODE_ADD_GROUP + 0x03:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_AddGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM) << ", ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_OR:
                    case SUB_OPCODE_AND:
                    case SUB_OPCODE_XOR:
                        this->GetAsmStream() << this->ParseImmediateOperand_I8(EXTEND_I16_I32);
                        break;
                    default:
                        this->GetAsmStream() << this->ParseImmediateOperand_I8(SIGNED);
                        break;
                }
                break;
            case OPCODE_TEST + RM8_R8:
            case OPCODE_TEST + RM16_R16:
            case OPCODE_XCHG + RM8_R8:
            case OPCODE_XCHG + RM16_R16:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte & 0xFE] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM) << ", " << this->ParseRegisterOperand(CntByte, GET_REG(MODRM));
                break;
            case OPCODE_XCHG_RAX_R:
            case OPCODE_XCHG_RAX_R + 0x01:
            case OPCODE_XCHG_RAX_R + 0x02:
            case OPCODE_XCHG_RAX_R + 0x03:
            case OPCODE_XCHG_RAX_R + 0x04:
            case OPCODE_XCHG_RAX_R + 0x05:
            case OPCODE_XCHG_RAX_R + 0x06:
                this->GetAsmStream() << InstructionDef::GetOpcode()[OPCODE_XCHG_RAX_R] << " ";
                this->GetAsmStream() << InstructionDef::GetReg(this->GetCPUMode())[REG_EAX_32] << ", " << InstructionDef::GetReg(this->GetCPUMode())[GET_RM(CntByte)];
                break;
            case OPCODE_CALL_FAR:
            case OPCODE_JMP_FAR:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << "far ";
                I32 = this->ReadDWord();
                I16 = this->ReadWord();
                this->GetAsmStream() << this->FormatAsmWord(I16) << "h:" << this->FormatAsmDWord(I32) << "h";
                break;
            case OPCODE_MOV_RAX_M_ONLY_DISP:
            case OPCODE_MOV_RAX_M_ONLY_DISP + 0x01:
            case OPCODE_MOV_RAX_M_ONLY_DISP + 0x02:
            case OPCODE_MOV_RAX_M_ONLY_DISP + 0x03:
                this->GetAsmStream() << InstructionDef::GetOpcode()[OPCODE_MOV_RAX_M_ONLY_DISP] << " ";
                Operand[0] = this->ParseMemoryOperand(CntByte, this->GetAddressMode() == ADDRESSHEAD_32 ? 0x05 : 0x06);
                Operand[1] = this->ParseRegisterOperand(CntByte, REG_EAX_32);
                this->GetAsmStream() << (GET_D_BIT(CntByte) ? (Operand[0] + ", " + Operand[1]) : (Operand[1] + ", " + Operand[0]));
                break;
            case OPCODE_MOVS:
            case OPCODE_MOVS + 0x01:
            case OPCODE_CMPS:
            case OPCODE_CMPS + 0x01:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte & 0xFE] << " ";
                Operand[0] = this->ParseMemoryOperand(CntByte, REG_ESI_32);
                Operand[1] = this->ParseMemoryOperand(CntByte, REG_EDI_32);
                this->GetAsmStream() << (GET_D_BIT(CntByte) ? (Operand[0] + ", " + Operand[1]) : (Operand[1] + ", " + Operand[0]));
                break;
            case OPCODE_TEST_RAX_IMM + RM8_R8:
            case OPCODE_TEST_RAX_IMM + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[OPCODE_TEST_RAX_IMM] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM_IMM(CntByte, 0xC0);
                break;
            case OPCODE_STOS + RM8_R8:
            case OPCODE_STOS + RM16_R16:
            case OPCODE_SCAS + RM8_R8:
            case OPCODE_SCAS + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte & 0xFE] << " ";
                this->GetAsmStream() << this->ParseMemoryOperand(CntByte, REG_EDI_32);
                break;
            case OPCODE_LODS + RM8_R8:
            case OPCODE_LODS + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte & 0xFE] << " ";
                this->GetAsmStream() << this->ParseMemoryOperand(CntByte, REG_ESI_32);
                break;
            case OPCODE_MOV_R_IMM + REG_EAX_32:
            case OPCODE_MOV_R_IMM + REG_ECX_32:
            case OPCODE_MOV_R_IMM + REG_EDX_32:
            case OPCODE_MOV_R_IMM + REG_EBX_32:
            case OPCODE_MOV_R_IMM + REG_ESP_32:
            case OPCODE_MOV_R_IMM + REG_EBP_32:
            case OPCODE_MOV_R_IMM + REG_ESI_32:
            case OPCODE_MOV_R_IMM + REG_EDI_32:
            case OPCODE_MOV_R_IMM + REG_EAX_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_ECX_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_EDX_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_EBX_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_ESP_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_EBP_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_ESI_32 + 0x08:
            case OPCODE_MOV_R_IMM + REG_EDI_32 + 0x08:
                this->GetAsmStream() << InstructionDef::GetOpcode()[OPCODE_MOV_R_IMM] << " ";
                this->GetAsmStream() << (GET_5TH_BIT(CntByte) ? InstructionDef::GetReg(this->GetCPUMode())[GET_RM(CntByte)] + ", " + this->ParseImmediateOperand_I16_I32() : InstructionDef::GetReg(REGSIZE_8)[GET_RM(CntByte)] + ", " + this->ParseImmediateOperand_I8());
                break;
            case OPCODE_ROL_GROUP + RM8_R8:
            case OPCODE_ROL_GROUP + RM16_R16:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_RolGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM) << ", " << this->ParseImmediateOperand_I8();
                break;
            case OPCODE_ROL_GROUP_2 + RM8_R8:
            case OPCODE_ROL_GROUP_2 + RM16_R16:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_RolGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM) << ", 01h";
                break;
            case OPCODE_ROL_GROUP_3 + RM8_R8:
            case OPCODE_ROL_GROUP_3 + RM16_R16:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_RolGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM) << ", " << InstructionDef::GetReg(REGSIZE_8)[REG_AL_8];
                break;
            case OPCODE_RETN_I16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << this->ParseImmediateOperand_I16();
                break;
            case OPCODE_LEA:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                MODRM = this->ReadByte();
                this->GetAsmStream() << this->ParseRegisterOperand(CntByte, GET_REG(MODRM)) << ", " << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_NULL);
                break;
            case OPCODE_ENTER:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << this->ParseImmediateOperand_I16() << ", " << this->ParseImmediateOperand_I8();
                break;
            case OPCODE_RETF_I16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << this->ParseImmediateOperand_I16();
                break;
            case OPCODE_INT:
            case OPCODE_AAM:
            case OPCODE_AAD:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << this->ParseImmediateOperand_I8();
                break;
            case OPCODE_XLAT:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << "byte ptr [" << InstructionDef::GetReg(this->GetAddressMode())[REG_EBX_32] << " + al]";
                break;
            case OPCODE_FADD_GROUP:
            case OPCODE_FADD_GROUP | 0x04:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_FaddGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, GET_6TH_BIT(CntByte) ? OPSIZE_32 : OPSIZE_64);
                break;
            case OPCODE_FLD_GROUP_RM32:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_FldGroup()[GET_OPCODE2(MODRM)] << " ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_FLDENV:
                    case SUB_OPCODE_FSTENV:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_NULL);
                        break;
                    case SUB_OPCODE_FLD:
                    case SUB_OPCODE_FST:
                    case SUB_OPCODE_FSTP:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_32);
                        break;
                    case SUB_OPCODE_FLDCW:
                    case SUB_OPCODE_FSTCW:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_16);
                        break;
                    default:
                        break;
                }
                break;
            case OPCODE_FLD_GROUP_RM64:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_Fld64Group()[GET_OPCODE2(MODRM)] << " ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_FRSTOR:
                    case SUB_OPCODE_FSAVE:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_NULL);
                        break;
                    case SUB_OPCODE_FLD:
                    case SUB_OPCODE_FISTTP:
                    case SUB_OPCODE_FST:
                    case SUB_OPCODE_FSTP:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_64);
                        break;
                    case SUB_OPCODE_FSTSW:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_16);
                        break;
                    default:
                        break;
                }
                break;
            case OPCODE_FIADD_GROUP:
            case OPCODE_FIADD_GROUP | 0x04:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_FiaddGroup()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, GET_6TH_BIT(CntByte) ? OPSIZE_32 : OPSIZE_16);
                break;
            case OPCODE_FILD_GROUP_RM32:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_FildGroup()[GET_OPCODE2(MODRM)] << " ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_FLD_TBYTE:
                    case SUB_OPCODE_FSTP_TBYTE:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_TBYTE);
                        break;
                    default:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_32);
                        break;
                }
                break;
            case OPCODE_FILD_GROUP_RM16:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_Fild16Group()[GET_OPCODE2(MODRM)] << " ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_FBLD_TBYTE:
                    case SUB_OPCODE_FBSTP_TBYTE:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_TBYTE);
                        break;
                    case SUB_OPCODE_FILD64:
                    case SUB_OPCODE_FISTP64:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_64);
                        break;
                    default:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_16);
                        break;
                }
                break;
            case OPCODE_IN + RM8_R8:
            case OPCODE_IN + RM16_R16:
            case OPCODE_OUT + RM8_R8:
            case OPCODE_OUT + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte & 0xFE] << " ";
                Operand[0] = this->ParseRegisterOperand(CntByte, REG_EAX_32);
                Operand[1] = this->ParseImmediateOperand_I8();
                this->GetAsmStream() << (GET_D_BIT(CntByte) ? Operand[1] + ", " + Operand[0] : Operand[0] + ", " + Operand[1]);
                break;
            case OPCODE_IN_DX + RM8_R8:
            case OPCODE_IN_DX + RM16_R16:
            case OPCODE_OUT_DX + RM8_R8:
            case OPCODE_OUT_DX + RM16_R16:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte & 0xFE] << " ";
                Operand[0] = this->ParseRegisterOperand(CntByte, REG_EAX_32);
                Operand[1] = InstructionDef::GetReg(REGSIZE_16)[REG_DX_16];
                this->GetAsmStream() << (GET_D_BIT(CntByte) ? Operand[1] + ", " + Operand[0] : Operand[0] + ", " + Operand[1]);
                break;
            case OPCODE_CALL_NEAR:
            case OPCODE_JMP_NEAR:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte] << " ";
                this->GetAsmStream() << this->ParseImmediateOperand_I16_I32();
                break;
            case OPCODE_INC_GROUP_RM8:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_Inc8Group()[GET_OPCODE2(MODRM)] << " ";
                this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_8);
                break;
            case OPCODE_INC_GROUP_RM16_RM32:
                MODRM = this->ReadByte();
                this->GetAsmStream() << InstructionDef::GetSubOpcode_Inc16_32Group()[GET_OPCODE2(MODRM)] << " ";
                switch (GET_OPCODE2(MODRM)) {
                    case SUB_OPCODE_INC:
                    case SUB_OPCODE_DEC:
                    case SUB_OPCODE_CALL_NEAR:
                    case SUB_OPCODE_JMP_NEAR:
                    case SUB_OPCODE_PUSH:
                        this->GetAsmStream() << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_16_32);
                        break;
                    case SUB_OPCODE_CALL_FAR:
                    case SUB_OPCODE_JMP_FAR:
                        this->GetAsmStream() << "far " << this->ParseMODRM_RM(CntByte, MODRM, OPSIZE_32);
                        break;
                    default:
                        break;
                }
                break;
            case OPCODE_DAA:
            case OPCODE_DAS:
            case OPCODE_AAA:
            case OPCODE_AAS:
            case OPCODE_NOP:
            case OPCODE_UNDEFINED_8F:
            case OPCODE_CWDE:
            case OPCODE_CDQ:
            case OPCODE_WAIT:
            case OPCODE_PUSHFD:
            case OPCODE_POPFD:
            case OPCODE_SAHF:
            case OPCODE_LAHF:
            case OPCODE_RETN:
            case OPCODE_LEAVE:
            case OPCODE_RETF:
            case OPCODE_INT3:
            case OPCODE_INTO:
            case OPCODE_IRETD:
            case OPCODE_SALC:
            case OPCODE_INT1:
            case OPCODE_HLT:
            case OPCODE_CMC:
            case OPCODE_CLC:
            case OPCODE_STC:
            case OPCODE_CLI:
            case OPCODE_STI:
            case OPCODE_CLD:
            case OPCODE_STD:
                this->GetAsmStream() << InstructionDef::GetOpcode()[CntByte];
                break;
            default:
                this->GetAsmStream() << "???";
                break;
        }
        CntInstruction->Clear();
        cout << setiosflags(ios::uppercase) << setw(8) << setfill('0') << hex << this->GetCntAddress() << " | ";
        this->SetCntAddress(this->GetLoadAddress() + (DWORD)(this->GetExeFile().tellg()));
        while (this->GetBinStream() >> BinByte)
        {
            cout << BinByte << " ";
        }
        cout << "| ";
        while (this->GetAsmStream() >> AsmVal)
        {
            cout << AsmVal << " ";
        }
        cout << endl;
        this->StringStreamClear(this->GetAsmStream());
        this->StringStreamClear(this->GetBinStream());
        this->ResetMode();
        InstructionStartPos = this->GetExeFile().tellg();
    }
    cout << endl;
    ExeFile.close();
}

void DASM::AT_AND_T_Exec()
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

void DASM::SetLoadAddress(DWORD LoadAddress)
{
    this->LoadAddress = LoadAddress;
}

DWORD DASM::GetLoadAddress()
{
    return this->LoadAddress;
}

void DASM::SetOffsetAddress(DWORD OffsetAddress)
{
    this->OffsetAddress = OffsetAddress;
}

DWORD DASM::GetOffsetAddress()
{
    return this->OffsetAddress;
}

void DASM::AddressInc(DWORD IncVal)
{
    this->CntAddress += IncVal;
}

void DASM::SetCntAddress(DWORD CntAddress)
{
    this->CntAddress = CntAddress;
}

DWORD DASM::GetCntAddress()
{
    return this->CntAddress;
}

stringstream& DASM::GetAsmStream()
{
    return this->AsmStream;
}

stringstream& DASM::GetBinStream()
{
    return this->BinStream;
}

ifstream& DASM::GetExeFile()
{
    return this->ExeFile;
}

BYTE DASM::ReadByte()
{
    BYTE CntByte = 0;
    if (this->GetExeFile())
    {
        this->GetExeFile().read((char*)&CntByte, 1);
    }
    this->GetBinStream() << this->FormatByte(CntByte) << " ";
    return CntByte;
}

WORD DASM::ReadWord()
{
    BYTE CntByte[2];
    for (int i = 0; i < 2; i++)
    {
        CntByte[i] = this->ReadByte();
    }
    return MAKE_WORD(CntByte[0], CntByte[1]);
}

DWORD DASM::ReadDWord()
{
    WORD CntWord[2];
    for (int i = 0; i < 2; i++)
    {
        CntWord[i] = this->ReadWord();
    }
    return MAKE_DWORD_2(CntWord[0], CntWord[1]);
}

string DASM::FormatByte(BYTE CntByte, BYTE SMod)
{
    stringstream FormatStream;
    if (SMod == SIGNED && GET_1ST_BIT(CntByte))
    {
        CntByte = ~CntByte + 1;
    }
    FormatStream << setiosflags(ios::uppercase) << setfill('0') << setw(2) << hex << (int)CntByte;
    string RetVal = "";
    FormatStream >> RetVal;
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

string DASM::ParseMemoryOperand(BYTE Opcode, BYTE MODRM, BYTE OpSize)
{
    BYTE MOD = 0, RM = 0;
    BYTE Base = 0, Index = 0, Scale = 0, SIB = 0;
    string Operand;
    MOD = GET_MOD(MODRM);
    RM = GET_RM(MODRM);
    switch (OpSize) {
        case OPSIZE_8:
            Operand += InstructionDef::GetAddressHead()[ADDRESSHEAD_8] + " ";
            break;
        case OPSIZE_16:
            Operand += InstructionDef::GetAddressHead()[ADDRESSHEAD_16] + " ";
            break;
        case OPSIZE_32:
            Operand += InstructionDef::GetAddressHead()[ADDRESSHEAD_32] + " ";
            break;
        case OPSIZE_64:
            Operand += InstructionDef::GetAddressHead()[ADDRESSHEAD_64] + " ";
            break;
        case OPSIZE_F:
            Operand += InstructionDef::GetAddressHead()[ADDRESSHEAD_F] + " ";
            break;
        case OPSIZE_16_32:
            Operand += InstructionDef::GetAddressHead()[this->GetCPUMode()] + " ";
            break;
        case OPSIZE_32_64: // TODO
            //Operand += InstructionDef::GetAddressHead()[this->GetCPUMode()] + " ";
            break;
        case OPSIZE_8_16_32:
            Operand += (GET_W_BIT(Opcode) == 0x00 ? InstructionDef::GetAddressHead()[ADDRESSHEAD_8] : InstructionDef::GetAddressHead()[this->GetCPUMode()]) + " ";
            break;
        case OPSIZE_8_32_64: // TODO
            break;
        case OPSIZE_NULL:
            Operand += InstructionDef::GetAddressHead()[ADDRESSHEAD_NULL] + " ";
            break;
        default:
            Operand += (GET_W_BIT(Opcode) == 0x00 ? InstructionDef::GetAddressHead()[ADDRESSHEAD_8] : InstructionDef::GetAddressHead()[this->GetCPUMode()]) + " ";
            break;
    }
    
    switch (this->GetAddressMode()) {
        case ADDRESS_MODE_16: // 16 Bits Addressing
            Operand += "[";
            Operand += (MOD == MOD_M_NO_DISPLACEMENT && RM == RM_ONLY_DISPLACEMENT_16_FLAG) ? "small " + this->ParseDisplacement(MOD) : InstructionDef::GetReg(ADDRESSSIZE_16)[RM];
            switch (MOD) {
                case MOD_M_DISPLACEMENT_8:
                case MOD_M_DISPLACEMENT_16_32:
                    Operand += " + " + this->ParseDisplacement(MOD);
                    break;
                default:
                    break;
            }
            Operand += "]";
            break;
        case ADDRESS_MODE_32: // 32 Bits Addressing
            if (MOD == MOD_M_NO_DISPLACEMENT && RM == RM_ONLY_DISPLACEMENT_32_FLAG)
            {
                Operand += "[" + this->ParseImmediateOperand_I32() + "]";
                break;
            }
            switch (RM)
            {
                case RM_SIB_FLAG: // Use SIB Memory Addressing
                    SIB = this->ReadByte();
                    Scale = GET_SCALE(SIB);
                    Index = GET_INDEX(SIB);
                    Base = GET_BASE(SIB);
                    Operand += "[";
                    Operand += Base == RM_ONLY_DISPLACEMENT_16_FLAG ? this->ParseDisplacement(MOD) : InstructionDef::GetReg(REGSIZE_32)[Base];
                    if (Index != RM_SIB_FLAG)
                    {
                        Operand += " + " + InstructionDef::GetReg(REGSIZE_32)[Index];
                        if (Scale != 0)
                        {
                            Operand += " * " + string(1, BYTE(1 << Scale) + '0');
                        }
                    }
                    switch (MOD) {
                        case MOD_M_DISPLACEMENT_8:
                        case MOD_M_DISPLACEMENT_16_32:
                            Operand += " + " + this->ParseDisplacement(MOD);
                            break;
                        default:
                            break;
                    }
                    Operand += "]";
                    break;
                default: // Use Non-SIB Memory Addressing
                    Operand += "[" + InstructionDef::GetReg(REGSIZE_32)[RM];
                    switch (MOD) {
                        case MOD_M_DISPLACEMENT_8:
                        case MOD_M_DISPLACEMENT_16_32:
                            Operand += " + " + this->ParseDisplacement(MOD);
                            break;
                        default:
                            break;
                    }
                    Operand += "]";
                    break;
                }
            break;
        default:
            break;
    }
    return Operand;
}

string DASM::ParseRegisterOperand(BYTE Opcode, BYTE REG)
{
    return GET_W_BIT(Opcode) == 0x00 ? InstructionDef::GetReg(REGSIZE_8)[REG] : InstructionDef::GetReg(this->GetCPUMode())[REG];
}

string DASM::ParseDisplacement(BYTE MOD)
{
    return MOD == MOD_M_DISPLACEMENT_8 ? this->ParseImmediateOperand_I8() : (this->GetAddressMode() == ADDRESS_MODE_16 ? this->ParseImmediateOperand_I16() : this->ParseImmediateOperand_I32());
}

string DASM::ParseImmediateOperand(BYTE Opcode)
{
    // TODO
    //if (GET_S_BIT(Opcode) == 0x00)
    //{
    //AsmStream << Operand[1];
    //}
    //else
    //{
    //AsmStream << Operand[1];
    //}
    return GET_W_BIT(Opcode) == 0x00 ? this->ParseImmediateOperand_I8() : this->ParseImmediateOperand_I16_I32();
}

string DASM::ParseImmediateOperand_I8(BYTE SMod)
{
    BYTE I8 = this->ReadByte();
    string RetVal = "";
    switch (SMod) {
        case SIGNED:
            RetVal += (GET_1ST_BIT(I8) ? "-" : "");
            RetVal += this->FormatByte(I8, SIGNED) + "h";
            break;
        case UNSIGNED:
            RetVal += this->FormatByte(I8, UNSIGNED) + "h";
            break;
        case EXTEND_I16_I32:
            if (GET_1ST_BIT(I8))
            {
                RetVal += (this->GetCPUMode() == CPU_MODE_16 ? "FF" : "FFFFFF");
            }
            else
            {
                RetVal += (this->GetCPUMode() == CPU_MODE_16 ? "00" : "000000");
            }
            RetVal += this->FormatByte(I8, UNSIGNED) + "h";
            break;
        default:
            break;
    }
    return RetVal;
}

string DASM::ParseImmediateOperand_I16()
{
    WORD I16 = this->ReadWord();
    return this->FormatAsmWord(I16) + "h";
}

string DASM::ParseImmediateOperand_I32()
{
    DWORD I32 = this->ReadDWord();
    return this->FormatAsmDWord(I32) + "h";
}

string DASM::ParseImmediateOperand_I16_I32()
{
    return this->GetCPUMode() == CPU_MODE_16 ? this->ParseImmediateOperand_I16() : this->ParseImmediateOperand_I32();
}

string DASM::ParseMODRM_RM(BYTE Opcode, BYTE MODRM, BYTE OpSize)
{
    return GET_MOD(MODRM) == MOD_R_NO_DISPLACEMENT ? this->ParseRegisterOperand(Opcode, GET_RM(MODRM)) : this->ParseMemoryOperand(Opcode, MODRM, OpSize);
}

string DASM::ParseMODRM_RM_R(BYTE Opcode, BYTE MODRM, BYTE OpSize)
{
    string Operand[2];
    Operand[0] = this->ParseMODRM_RM(Opcode, MODRM, OpSize);
    Operand[1] = this->ParseRegisterOperand(Opcode, GET_REG(MODRM));
    return GET_D_BIT(Opcode) == 0x00 ? Operand[0] + ", " + Operand[1] : Operand[1] + ", " + Operand[0];
}

string DASM::ParseMODRM_RM_IMM(BYTE Opcode, BYTE MODRM, BYTE OpSize)
{
    string Operand[2];
    Operand[0] = this->ParseMODRM_RM(Opcode, MODRM, OpSize);
    Operand[1] = this->ParseImmediateOperand(Opcode);
    // TODO  S-BIT
    return GET_S_BIT(Opcode) == 0x00 ? Operand[0] + ", " + Operand[1] : Operand[0] + ", " + Operand[1];
}

string DASM::ParseMODRM_R_RM_IMM(BYTE Opcode, BYTE MODRM, BYTE OpSize)
{
    string Operand[3];
    Operand[0] = this->ParseRegisterOperand(Opcode, GET_REG(MODRM));
    Operand[1] = this->ParseMODRM_RM(Opcode, MODRM, OpSize);
    Operand[2] = GET_D_BIT(Opcode) == 0x00 ? this->ParseImmediateOperand_I16_I32() : this->ParseImmediateOperand_I8();
    // TODO  S-BIT
    return Operand[0] + ", " + Operand[1] + ", " + Operand[2];
}

void DASM::StringStreamClear(stringstream &SStream)
{
    SStream.clear();
    SStream.str("");
}
