#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);


    string prop;
    cout << "input: ";
    getline(cin, prop);
    getline(cin, prop);

    int idx = prop.find(' ');

    string op(prop, 0, idx);
    string args(prop, idx + 1);

    int idx1 = args.find(',');
    int idx2 = args.rfind(',');

    cout << idx1 << " " << idx2 << endl;

    int n1 = std::stoi(args.substr(0, idx1));
    string n2 = (args.substr(idx1 + 1, idx2 - idx1 - 1));
    string reg(args, idx2 + 1);

    cout << op << endl << args << endl << n1 << endl << n2 << endl << "%r" + reg.substr(2) << endl;
}