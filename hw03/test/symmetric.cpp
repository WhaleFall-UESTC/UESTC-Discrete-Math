#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef struct {int pointed; bool check = false;} info;
map<int, info> R;


bool exit(int a, int b) 
{
    auto it = R.find(a);
    if (it == R.end()) return false;
    else return it->second.pointed == b;
}


bool symmetric(void *arg)
{
    int idx1, idx2;

    for (const auto& pair : R) {
        if (pair.second.check)
            continue;

        idx1 = pair.first;
        idx2 = pair.second.pointed;

        if (!exit(idx2, idx1)) return false;

        R[idx2].check = true;
    }

    return true;
}


bool antisymmetric(void *arg)
{
    int idx1, idx2;

    for (const auto& pair : R) {
        idx1 = pair.first;
        idx2 = pair.second.pointed;

        if (idx1 != idx2 && exit(idx2, idx1)) return false;
    }

    return true;
}


bool transitive(void *arg)
{
    int idx1, idx2, idx3;

    for (const auto& pair : R) {
        idx1 = pair.first;
        idx2 = pair.second.pointed;
        idx3 = R[idx2].pointed;

        if(!exit(idx1, idx3)) return false;
    }

    return true;
}


int main(int argc, char *argv[])
{
    // if (argc != 2) {
    //     cout << "Usage: ./prog2 <file path>"<< endl;
    //     exit(-1);
    // }

    // const char *filename = argv[1];

    const char *filename = "relations";
    ifstream fin(filename);

    int n = 0, idx1, idx2;
    fin >> n;

    for (int i = 0; i < n; i++) {
        fin >> idx1 >> idx2;
        
    }

    if (symmetric(NULL)) puts("symmetric");
    else puts("not symmetric");
    if (antisymmetric(NULL)) puts("antisymmetric");
    if (transitive(NULL)) puts("transitive");
}