#include <iostream>
#include <fstream>
#include <map>
#include <pthread.h>

using namespace std;

map<int, int> elements;

void* check_idx1(void *arg) 
{
    int idx1 = *(int*)arg;

    auto it = elements.find(idx1);
    if (it != elements.end()) {
        cout << idx1 << " has pointed " << it->second << endl;
        exit(0);
    }

    pthread_exit(NULL);
}

void* check_idx2(void *arg) 
{
    int idx2 = *(int*)arg;

    for (const auto& pair : elements) 
        if (pair.second == idx2) {
            cout << idx2 << " has been pointed by " << pair.first << endl;
            exit(0);
        }

    pthread_exit(NULL);
}


int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        cout << "Usage: ./injection <file path>"<< endl;
        exit(-1);
    }

    const char *filename = argv[1];

    ifstream file(filename, ios::in);
    
    int n = 0;
    file >> n;
    
    int idx1, idx2;
    pthread_t thread_idx1, thread_idx2;

    
    for (int i = 0; i < n; i++) 
    {
        file >> idx1 >> idx2;

        pthread_create(&thread_idx1, NULL, check_idx1, &idx1);
        pthread_create(&thread_idx2, NULL, check_idx2, &idx2);

        pthread_join(thread_idx1, NULL);
        pthread_join(thread_idx2, NULL);

        elements[idx1] = idx2;
    }

    cout << "Injection!" << endl;
    file.close();
    return 0;
}