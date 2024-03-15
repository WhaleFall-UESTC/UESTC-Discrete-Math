#include "complier+.h"
#include "logger.h"

using namespace std;

map<string, list<command> >cmds_map;
int regs[10] = {};

int main(int argc, char **argv) 
{
    string ENTER;
    string prop;

    int n = 0;  // number of elements in domain
    int a = 2;  // number of atom prpositions. 0 denotes P(x) and 1 denotes Q(x)

    cout << "input the number of elements in domain：";
    cin >> n;
    getline(cin,ENTER);
    log_int(INFO, "n =", n);

    const long N = 1 << n * a;

    
    for (int i = 0; ; i++) {
        log_out_int(INFO, "Check proposition", i, "");

        while(true) 
        {
            getline(cin, prop);
            if (prop.empty()) {
                log_out(WARN, "Proposition Empty");
                i--;
                break;
            }

            int blank_idx1 = prop.find(' ');
            int blank_idx2 = prop.rfind(' ');

            switch(prop[0]) {
                case 'P': {
                    string prop_name(prop, blank_idx1 + 1);
                    log_out(INFO, prop_name.c_str());

                    list<command> cmds_tmp;

                    for (int j = 0; ; j++) {
                        getline(cin, prop);
                        cmds_tmp.push_back(assembler(prop));

                        if (is_last_command())
                            break;
                    }

                    cmds_map[prop_name] = cmds_tmp;
                    break;
                }

                case 'A': {
                    string cmd(prop, 0, blank_idx1);
                    string reg(prop, blank_idx2 + 1);  

                    command res = assembler(cmd);
                    list<command> cmd_tmp;

                    if (res == -1) 
                        cmd_tmp = cmds_map[cmd];
                    else 
                        cmd_tmp.push_back(res);
                    

                    for (long cond = 0; cond < N; cond++)
                    {
                        long situ = 0;
                        for (int j = a - 1; j > 0; j--) {
                            int value = (cond >> j * n) & 1;
                            situ <<= 1;
                            situ |= value;
                        }

                        if (!emulator(situ, cmd_tmp)) {
                            mod_reg(reg, 0);
                            goto END_ANY;
                        }

                        mod_reg(reg, 1);
                    }

                    END_ANY:
                    break;
                }

                case 'E': {
                    
                }

                default: {
                    
            }
        }

    }
}