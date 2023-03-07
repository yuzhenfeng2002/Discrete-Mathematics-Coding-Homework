#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

void two_prop_calculator(bool p, bool q); // Calculator of two propositions

int main() {
    cout << "***************************************\n";
    cout << "**                                   **\n";
    cout << "**     WELCOME TO THE CALCULATOR     **\n";
    cout << "**                                   **\n";
    cout << "***************************************\n";
    bool isContinue = true;
    while (isContinue)
    {
        int p, q;
        p = q = -1;
        cout << "Please input the boolean value of p: ";
        cin >> p;
        while (p != 0 && p != 1) {
            cout << "Illegal character. Please try again.\n";
            cout << "Please input the boolean value of p: ";
            cin >> p;
        }

        cout << "Please input the boolean value of q: ";
        cin >> q;
        while (q != 0 && q != 1) {
            cout << "Illegal character. Please try again.\n";
            cout << "Please input the boolean value of q: ";
            cin >> q;
        }

        two_prop_calculator(p, q);

        cout << "Do you want to try again? (y/n)";
        char opt;
        cin >> opt;
        switch (opt) {
            case 'y':
                isContinue = true;
                break;
            case 'n':
                isContinue = false;
                break;
            default:
                break;
        }
    }

    system("pause");
    
    return 0;
}

void two_prop_calculator(bool p, bool q) {
    cout << "Conjunction:\tp/\\q\t=\t" << int(p && q) << endl;
    cout << "Disjunction:\tp\\/q\t=\t" << int(p || q) << endl;
    cout << "Entailment:\tp->q\t=\t" << int(!p || q) << endl;
    cout << "Bicondition:\tp<->q\t=\t" << int((!p || q) && (!q || p)) << endl;
}