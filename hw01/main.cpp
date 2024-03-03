#include "complier.h"
#include "logger.h"

#include <iostream>
#include <bitset>

using namespace std;


int main()
{
    init_map();
    init_log();

    int n;

    cout << "Total number of people: ";
    cin >> n;
    string Enter;
    getline(cin, Enter);

    log_int(INFO, "The number of people is", n);

    const int N = n;
    const int S = 2 << n - 1;
    copy_n(n);
    int situations[S] = {};
    int cnt_ok = 0;
    string cmd;
    command res, cmds[N][CMD_MAX] = {};

    for(int i = 0; i < n; i++) {
        log_int(INFO, "Proposition from the person with ID", i);

        cout << "The person with ID " << i << " claims:\n";
        int cnt_cmd = 0;

        do {
            getline(cin, cmd);
            log(INFO, cmd.c_str());

            res = complier(cmd);
            log_bin32(DEBUG, "Complier:", res);
            
            if (res == -1) {
                log_out(INFO, "Please input a valid command");
                continue;
            }

            cmds[i][cnt_cmd++] = res;

            if (cnt_cmd == CMD_MAX) {
                log_out(ERROR, "Commands Reach MAX");
                i--;
                break;
            }

        } while(res);
    }

    puts("");

    for(int cond = 0; cond < S; cond++) {
        log_int(INFO, "In situatoon", cond);
        bool this_cond = true;

        for(int j = 0; j < n; j++) {
            log_int(INFO, "Check proposition", j);
            
            int person_id = (cond >> j) & 1;
            int prop_right = emulator(cond, cmds[j]);
            log_int(DEBUG, "This person is", person_id);

            // if one's acts belie one's words
            if(person_id ^ prop_right) {
                this_cond = false;
                log(INFO, "Contradiction. Pass");
                break;
            }
            
            log(INFO, "Match the condition");
        }

        if(this_cond) {
            situations[cnt_ok++] = cond;
            log_out_int(INFO, "Situation", cond, "meets the question set!");
        }
    }

    if (cnt_ok == 0 || cnt_ok == 1) 
        log_out_int(INFO, "Total", cnt_ok, "situstion meets the question set.");
    else
        log_out_int(INFO, "Total", cnt_ok, "situstions meet the question set.");


    for(int i = 0; i < cnt_ok; i++) {
        puts("");
        log_out_int(INFO, "Situation", situations[i], "");

        for(int j = 0; j < n; j++) {
            int id = (situations[i] >> j) & 1;
            situations[i] >>= 1;

            string identity = id ? "Knight" : "Knave";
            cout << "[INFO]\tPerson " << j << " is a " << identity << endl;
        }
    }

    end_log();
    return 0;
}
