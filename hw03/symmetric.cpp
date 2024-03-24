#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <map>

using namespace std;

typedef struct{int n; bool check;} pointed; // check means re format exist in R
typedef vector<pointed> point;
map<int, point> R;


bool exist(int a, int b)
{
    auto it_a= R.find(a);
    if (it_a == R.end()) return false;

    point a_v = it_a->second;
    for (auto& num : a_v) 
        if (num.n == b) {
            num.check = true;
            R[b][a].check = true;
            return true;
        }

    return false;
}


void* symmetric(void* arg)
{
    for (const auto& pair : R) {
        int a = pair.first;
        point b = pair.second;

        for (const auto& num : b) {
            if (num.check) continue;
            if (!exist(num.n, a)) {
                puts("not symmetric");
                pthread_exit(NULL);
            }
        }
    }

    puts("symmetric");
    pthread_exit(NULL);
}


void* antisymmetric(void *arg)
{
    for (const auto& pair : R) {
        int a = pair.first;
        point b = pair.second;

        for (const auto& num : b) {
            bool not_equal = a == num.n;
            if ((num.check || exist(num.n, a)) && a != num.n) {
                puts("not antisymmetric");
                pthread_exit(NULL);
            }
        }
    }

    puts("antisymmetric");
    pthread_exit(NULL);
}


void* transitive(void *arg)
{
    for (const auto& pair : R) {
        int a = pair.first;
        for (const auto& b_p : pair.second) {
            int b = b_p.n;
            for (const auto& c_p : R[b]) {
                int c = c_p.n;
                if (!exist(c, a)) {
                    puts("not transitive");
                    pthread_exit(NULL);
                }
            }
        }
    }

    puts("transitive");
    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Usage: ./symmetric <file path>"<< endl;
        exit(-1);
    }

    const char *filename = argv[1];

    ifstream fin(filename);

    int n = 0, idx1, idx2;
    fin >> n;

    for (int i = 0; i < n; i++) {
        fin >> idx1 >> idx2;
        R[idx1].push_back({idx2, false});
    }


    pthread_t symmetric_thread, antisymmetric_thread, transitive_thread;
    
    pthread_create(&symmetric_thread, NULL, symmetric, NULL);
    pthread_create(&antisymmetric_thread, NULL, antisymmetric, NULL);
    pthread_create(&transitive_thread, NULL, transitive, NULL);

    pthread_join(symmetric_thread, NULL);
    pthread_join(antisymmetric_thread, NULL);
    pthread_join(transitive_thread, NULL);

    return 0;
}