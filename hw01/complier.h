#include <string>
#include <cstring>
#include <map>

#define IMPLIES(a,b) (1-a)|b
#define IFF(a,b) 1-(a^b)
#define MAX 0xFFF
#define CMD_MAX 15
#define REGS_MAX 8

typedef int command;


int emulator(long cond, command * cmds);
command asssemler(std::string prop);
void init_map();
void copy_n(int n);
bool is_last_command();
