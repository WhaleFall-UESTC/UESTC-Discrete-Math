#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<int, int> elements;

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        cout << "Usage: ./prog1 <file path>"<< endl;
        exit(-1);
    }

    const char *filename = argv[1];

    ifstream file(filename, ios::in);
    
    int n = 0;
    file >> n;
    
    int idx1, idx2;
    
    for (int i = 0; i < n; i++) 
    {
        file >> idx1 >> idx2;

        for (const auto& pair : elements) 
            if (pair.second == idx2) {
                cout << idx2 << " has been pointed by " << pair.first << endl;
                exit(0);
            }

        auto it = elements.find(idx1);
        if (it == elements.end())
            elements[idx1] = idx2;
        else {
            cout << idx1 << " has pointed " << it->second << endl;
            exit(0);
        }
    }

    cout << "Injection!" << endl;
    file.close();
    return 0;
}