#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef unsigned long condition;

int main(int argc, char **argv)
{
    /* Input parameters */

    int n = -1;             // number of digits in the domai:/
    char *domain;           // domain, {1, 2, ...}
    int len = 0;            // length of the string of domain
    int atoms = 2;          // number of atom propositions
    int flags = -1;         // wether parameter is -n or -u

    enum {Domain, N, Atoms};

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'n': flags = N; break;
                case 'u': flags = Domain; break;
                case 'a': flags = Atoms; break;
            }
        }
        else if (flags != -1) {
            switch(flags) {
                case N: 
                    n = atoi(argv[i]);
                    break;
                case Domain:
                    len = strlen(argv[i]);
                    domain = (char *)malloc(len * sizeof(char));
                    strcpy(domain, argv[i]);
                case Atoms:
                    atoms = atoi(argv[i]);
            }
        }
    }

    if (n == -1) {
        n += 2;
        for (int i = 0; i < len; i++) 
            if (domain[i] == ',')
                n++;      
    }

    if (n == -1)
        exit(-1);

    const condition COND = pow(n, atoms);


    
    /* Check Proposition 1 */

    return 0;
}