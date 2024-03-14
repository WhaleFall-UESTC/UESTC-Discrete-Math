#include "complier+.h"
#include "logger.h"

using namespace std;

int main(int argc, char **argv) 
{
    string ENTER;
    string prop;

    int n = 0;  // number of elements in domain
    int u = 2;  // number of atom prpositions. 0 denotes P(x) and 1 denotes Q(x)

    cout << "input the number of elements in domain：";
    cin >> n;
    getline(cin,ENTER);
    log_int(INFO, "n =", n);

    
    for (int i = 0; ; i++) {
        log_out_int(INFO, "Check proposition", i, "");

        getline(cin, prop);

        if (prop.empty()) {
            break;
            log_out(ERROR, "Proposition Empty");
            exit(-1);
        }

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