#include <iostream>
#include <string>

#define LEFT false
#define RIGHT true
#define ANY false
#define EXIST true
#define IMP(a, b) (!a)||b
#define IFF(a, b) !(a^b)

using namespace std;


void report_side(int prop_id, bool side, bool value) {
    const char* side_s = side ? "right" : "left";
    const char* value_s = value ? "TRUE" : "FALSE";
    cout << "The " << side_s << " side of the Proposition " << prop_id << " is " << value_s << endl;
}

void report_prop(int prop_id, bool value) {
    const char* value_s = value ? "TRUE" : "FALSE";
    cout << "Proposition " << prop_id << " is " << value_s << "\n\n";
}

bool any(int sit, int n) {
    return sit == (1 << n) - 1;
}

bool exist(int sit) {
    return sit != 0;
}


int main(int argc, char **argv) 
{
    //int n = atoi(argv[1]);  // The number of elements in domain
    int n;
    cin >> n;
    int a = 2;              // The number of atom props
    const long N = 1 << a * n;
    const int mask = (1 << n) - 1;

    bool r, l, p;



    /*--------------------------
        Check Proposition 1
    ---------------------------*/
    p = true;

    for (long sit = 0; sit < N; sit++) 
    {
        int pi = (sit >> n) & mask;
        int qi = sit & mask;

        l = true;
        r = any(pi, n) || any(qi, n);
        //report_side(1, RIGHT, r);

        for (int i = 0; i < n; i++) {
            if (((pi >> i) & 1) | ((qi >> i) & 1) == 0) {
                l = false;
                break;
            }
        }
        //report_side(1, LEFT, l);

        if (l ^ r) {
            p = false;
            break;
        }
    }

    report_prop(1, p);



    /*--------------------------
        Check Proposition 2
    ---------------------------*/
    p = true;

    for (long sit = 0; sit < N; sit++) 
    {
        int pi = (sit >> n) & mask;
        int qi = sit & mask;

        l = false;
        r = exist(pi) && exist(qi);
        //report_side(1, RIGHT, r);

        for (int i = 0; i < n; i++) {
            if (((pi >> i) & 1) & ((qi >> i) & 1) == 1) {
                l = true;
                break;
            }
        }
        //report_side(1, LEFT, l);

        if (l ^ r) {
            p = false;
            break;
        }
    }

    report_prop(2, p);



    /*--------------------------
        Check Proposition 3
    ---------------------------*/
    p = true;

    for (long sit = 0; sit < N; sit++) 
    {
        int pi = (sit >> n) & mask;
        int qi = sit & mask;

        l = true;
        r = IMP(any(pi, n), any(qi, n));
        //report_side(1, RIGHT, r);

        for (int i = 0; i < n; i++) {
            if (!IMP(((pi >> i) & 1), ((qi >> i) & 1))) {
                l = false;
                break;
            }
        }
        //report_side(1, LEFT, l);

        if (l ^ r) {
            p = false;
            break;
        }
    }

    report_prop(3, p);



    /*--------------------------
        Check Proposition 4
    ---------------------------*/
    p = true;

    for (long sit = 0; sit < N; sit++) 
    {
        int pi = (sit >> n) & mask;
        int qi = sit & mask;

        l = false;
        r = IMP(exist(pi), exist(qi));
        //report_side(1, RIGHT, r);

        for (int i = 0; i < n; i++) {
            if (IMP(((pi >> i) & 1), ((qi >> i) & 1))) {
                l = true;
                break;
            }
        }
        //report_side(1, LEFT, l);

        if (l ^ r) {
            p = false;
            break;
        }
    }

    report_prop(4, p);



    /* My Proposition */

    p = true;

    for (long sit = 0; sit < N; sit++) 
    {
        int pi = (sit >> n) & mask;
        int qi = sit & mask;


        l = true;
        r = any(pi, n) && any(qi, n);
        report_side(1, RIGHT, r);

        for (int i = 0; i < n; i++) {
            if (!(((pi >> i) & 1) & ((qi >> i) & 1))) {
                l = false;
                break;
            }
        }
        report_side(1, LEFT, l);

        if (l ^ r) {
            p = false;
            break;
        }
    }

    report_prop(0, p);

    return 0;
}