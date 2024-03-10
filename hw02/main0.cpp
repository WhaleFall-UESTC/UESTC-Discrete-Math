#include <iostream>
#include <cmath>

#define PICK(x,i) ((x>>i)&1)
#define PICK0(x, i) (!PICK(x, i))

#define IFF(a, b) (1-(a^b))
#define IMP(a, b) ((1-a)|b)

#define OP_DETECT_WRONG break

using namespace std;

int n;
int p1 = 1, p2 = 1; 
int equals = 1;
int pi = 0, qi = 0;


void report(int);

int main(int argc, char **argv)
{
    n = atoi(argv[1]);
    int cond = 1 << 2 * n;

    bool p1_end = false, p2_end = false;


    /* Proposition 1 */

    puts("Check proposition 1");

    for (int k = 0; k < cond; k++) {
        pi = k >> n;
        qi = k;
        p1 = p2 = 1;

        for (int i = 0; i < n; i++) {
            if (!(PICK(pi, i) || PICK(qi, i))) {
                p1 = 0;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            int pi_i = PICK(pi, i);
            for (int j = 0; j < n; j++) {
                if (!(pi_i || PICK(qi, j))) {
                    p2 = 0;
                    break;
                }
            }
        }

        if (p1 ^ p2) {
            report(k);
            OP_DETECT_WRONG;
        }
    }

    if (equals)
        cout << "The two propositions are equivalent" << endl;

    puts("");

    

    /* Proposition 2 */

    puts("Check proposition 2");

    equals = 1;
    pi = qi = 0;

    for (int k = 0; k < cond; k++) {
        pi = k >> n;
        qi = k;
        p1 = p2 = 0;

        for (int i = 0; i < n; i++) {
            if (PICK(pi, i) && PICK(qi, i)) {
                p1 = 1;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            int pi_i = PICK(pi, i);
            for (int j = 0; j < n; j++) {
                if (pi_i && PICK(qi, j)) {
                    p2 = 1;
                    break;
                }
            }
        }

        if (p1 ^ p2){
            report(k);
            OP_DETECT_WRONG;
        }
    }

    if (equals)
        cout << "The two propositions are equivalent" << endl;

    puts("");



    /* Proposition 3 */

    puts("Check proposition 3");
    
    equals = 1;
    pi = qi = 0;

    for (int k = 0; k < cond; k++) {
        pi = k >> n;
        qi = k;
        p1 = p2 = 1;

        for (int i = 0; i < n; i++) {
            if (!IMP(PICK(pi, i), PICK(qi, i))) {
                p1 = 0;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            int pi_i = PICK(pi, i);
            for (int j = 0; j < n; j++) {
                if (!IMP(pi_i, PICK(qi, j))) {
                    p2 = 0;
                    break;
                }
            }
        }

        if (p1 ^ p2) {
            report(k);
            OP_DETECT_WRONG;
        }
    }

    if (equals)
        cout << "The two propositions are equivalent" << endl;

    puts("");

    

    /* Proposition 4 */

    puts("Check proposition 4");

    equals = 1;
    pi = qi = 0;

    for (int k = 0; k < cond; k++) {
        pi = k >> n;
        qi = k;
        p1 = p2 = 0;

        for (int i = 0; i < n; i++) {
            if (IMP(PICK(pi, i), PICK(qi, i))) {
                p1 = 1;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            int pi_i = PICK(pi, i);
            for (int j = 0; j < n; j++) {
                if (IMP(pi_i, PICK(qi, j))) {
                    p2 = 1;
                    break;
                }
            }
        }

        if (p1 ^ p2) {
            report(k);
            OP_DETECT_WRONG;
        }
    }

    if (equals)
        cout << "The two propositions are equivalent" << endl;

    puts("");
}


void report(int k)
{
    cout << "In cond " << k << " p1 not equals to p2 when" << endl;
    equals = 0;

    for (int i = 0; i < n; i++) {
        cout << "P(" << i << ") is " << char(70 + 14 * PICK(pi, i)) << "\t";
        cout << "Q(" << i << ") is " << char(70 + 14 * PICK(qi, i)) << "\n";
    }
}