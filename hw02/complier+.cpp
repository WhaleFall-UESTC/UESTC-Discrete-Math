#include "complier+.h"
#include "logger.h"

#include <iostream>
#include <bitset>

#define SEPARATOR ','

using namespace std;

enum OPCODES {RET, MOV, NOT, AND, OR, XOR, IMP, IFF};
std::map<std::string, unsigned>opcodes;

enum REGS {NONE, R1, R2, R3, R4, R5, R6, R7};
std::map<std::string, int>regs;

int n_copy = 0;
bool end_command = false;
int registers[REGS_MAX] = {};


int get_n(std::string n);
int get_reg(std::string reg);


int emulator(long cond, list<command> cmds)
{
    int op = -1, n1 = 0, n2 = 0, reg = 0;

    while (true) {
        command cmd = cmds.front();

        if ((cmd >> 14) & 1 == 0) {
            log(DEBUG, "Check 14th is 0");
            log_int(DEBUG, "The result is", registers[1]);
            return registers[1];
        }

        op = (cmd >> 29) & 7;
        n1 = (cmd >> 16) & 0x1FFF;
        n1 = ((n1 >> 12) & 1) ? registers[n1 & 0xFFF] : (cond >> n1) & 1;
        n2 = (cmd >> 3) & 0x1FFF;
        n2 = ((n2 >> 12) & 1) ? registers[n2 & 0xFFF] : (cond >> n2) & 1;
        reg = cmd & 7;

        log_bin32(DEBUG, "Run cmd", cmd);

        switch (op) {
            case RET:
                log_int(DEBUG, "The result is", registers[1]);
                return registers[1];

            case NOT:
                registers[reg] = 1 - n1;

            case MOV:
                registers[reg] = n1;
                break;

            case AND:
                registers[reg] = n1 & n2;
                break;

            case OR:
                registers[reg] = n1 | n2;
                break;

            case XOR:
                registers[reg] = n1 ^ n2;
                break;

            case IMP:
                registers[reg] = IMPLIES(n1, n2);
                break;

            case IFF:
                registers[reg] = IFF(n1, n2);
                break;

            default:
                log(WARN, "Emulator: Can't recognize opcode");
                return -1;
        }

        cmds.pop_front();
    }
}


command assembler(std::string prop)
{
    int op = -1;
    int n1 = 0, n2 = 0;
    int reg = 0;

    int idx_blank = prop.find(' ');
    if (idx_blank == prop.npos)
        idx_blank = prop.find(',');

    std::string opcode_s(prop, 0, idx_blank);
    std::string args(prop, idx_blank + 1); 

    if (opcodes.find(opcode_s) == opcodes.end()) {
        log_out(ERROR, "Complier: Opcode Invalid");
        return -1;
    }
    else
        op = opcodes[opcode_s];


    switch (op) {
        case RET: {
            return 0;
        }

        case MOV:
        case NOT: {
            int idx_dot = args.find(',');
            n1 = get_n(args.substr(0, idx_dot));

            if (n1 == -1)
                    return -1;

            if (idx_dot == std::string::npos) {
                end_command = true;
                reg = 1;
            }
            else {
                end_command = false;
                std::string reg_s(args, idx_dot + 1); 
                reg = get_reg(reg_s);
            }

            int result = (op << 29) | (n1 << 16) | reg;
            return end_command ? (result | 0x4000) : result;
        }

        case AND:
        case OR:
        case XOR:
        case IMP:
        case IFF:{
            int idx_dot1 = args.find(',');
            int idx_dot2 = args.rfind(',');

            int n1 = get_n(args.substr(0, idx_dot1));
            int n2 = get_n(args.substr(idx_dot1 + 1, idx_dot2 - idx_dot1 - 1));

            if (n1 == -1 || n2 == -1)
                return -1;

            if (idx_dot1 == idx_dot2) {
                end_command = true;
                reg = 1;
            }
            else {
                end_command = false;
                std::string reg_s(args, idx_dot2 + 1); 
                reg = get_reg(reg_s);
            }

            int result = (op << 29) | (n1 << 16) | (n2 << 3) | reg; 
            return end_command ? (result | 0x4000) : result;
        }

        default: {
            log(WARN, "Complier: Can't recognize opcode");
        }
    }
}


int complier(std::string prop, command* cmds)
{
    switch(prop[0]) {
        case 'P': {
            
        }

        case 'A': {

        }

        case 'E': {

        }

        default: {

        }
    }
}


void init_map()
{
    opcodes["ret"] = RET;
    opcodes["mov"] = MOV;
    opcodes["not"] = NOT;
    opcodes["and"] = AND;
    opcodes["or"]  = OR;
    opcodes["xor"] = XOR;
    opcodes["imp"] = IMP;
    opcodes["iff"] = IFF;

    regs["%r1"] = R1;
    regs["%r2"] = R2;
    regs["%r3"] = R3;
    regs["%r4"] = R4;
    regs["%r5"] = R5;
    regs["%r6"] = R6;
    regs["%r7"] = R7;
}


int get_n(std::string n)
{
    int res = -1;

    if (n[0] == '%') {
        res = std::stoi(n.substr(2));

        if (res >= REGS_MAX) {
            log_out(ERROR, "Complier: Register Invalid");
            return -1;
        }
        
        res = res | 0x1000;
    }
    else {
        res = std::stoi(n);

        if (res > MAX) {
            log_out(ERROR, "Complier: Num Overflow");
            return -1;
        }
        else if (res >= n_copy) {
            log_out(ERROR, "Complier: Num Too Big");
            return -1;
        }
    }

    return res;
}

int get_reg(std::string reg)
{
    if (regs.find(reg) == regs.end()) {
        log_out(ERROR, "Complier: Register Not Found");
        return -1;
    }
    return regs[reg];
}

void copy_n(int n)
{
    n_copy = n;
}

bool is_last_command() 
{
    return end_command;
}

int mod_reg(std::string reg, int value)
{
    registers[regs[reg]] = value;
}