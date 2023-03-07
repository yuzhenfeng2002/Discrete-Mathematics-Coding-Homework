#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cmath>
#include <bitset>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::stack;

const unsigned int MAX_VAR_NUM = 8;

int prec(char c); // Define the order of operators
void calculator(string eq); // The main calculator
string string_calculator(string s); // Transform the infix notation to the postfix notation
bool two_prop_calculator(bool p, bool q, char op); // Calculator of two propositions

int main() {
    cout << "***************************************\n";
    cout << "**                                   **\n";
    cout << "**     WELCOME TO THE CALCULATOR     **\n";
    cout << "**                                   **\n";
    cout << "***************************************\n";
    bool isContinue = true;
    while (isContinue)
    {
        cout << "Please input a valid equation: ";
        string eq;
        cin >> eq;

        calculator(eq);

        cout << "Do you want to try again? (y/n) ";
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

bool two_prop_calculator(bool p, bool q, char op) {
    switch (op) {
    case '&':
        return p && q;
        break;
    case '|':
        return p || q;
        break;
    case '^':
        return !p || q;
        break;
    case '~':
        return (!p || q) && (!q || p);
        break;
    default:
        return p || q;
        break;
    }
}

void calculator(string eq) {
    vector<int> sum_of_prod = vector<int>();
    vector<int> prod_of_sum = vector<int>();
    string postOrderString = string_calculator(eq);
    int alphaNum = 0;
    map<char, int> char2index = map<char, int>();
    for (size_t i = 0; i < postOrderString.size(); i++) {
        if (isalpha(postOrderString.at(i))) {
            auto search = char2index.find(postOrderString.at(i));
            if (search == char2index.end()) {
                char2index.insert({postOrderString.at(i), alphaNum});
                alphaNum ++;
            } else {
                continue;
            }
            cout << postOrderString.at(i) << ' ';
        }
    }
    cout << endl;

    int max = pow(2, alphaNum) - 1;
    for (int i = 0; i < max + 1; i++) {
        string solution = std::bitset<MAX_VAR_NUM>(i).to_string();
        solution = solution.substr(MAX_VAR_NUM - alphaNum);
        stack<bool> st = stack<bool>();
        for (size_t j = 0; j < postOrderString.size(); j++) {
            char ch = postOrderString.at(j);
            if (isalpha(ch)) {
                st.push(solution.at(char2index.find(ch)->second) - '0');
            }
            else {
                if (ch == '!') {
                    bool tmp = !st.top();
                    st.pop();
                    st.push(tmp);
                }
                else {
                    auto x = st.top(); st.pop();
                    auto y = st.top(); st.pop();
                    st.push(two_prop_calculator(y, x, ch));
                }
            }
        }
        for (size_t j = 0; j < solution.size(); j++) {
            cout << solution.at(j) << ' ';
        }
        cout << '\t' << st.top() << endl;
        if (st.top()) {
            sum_of_prod.push_back(i);
        } else {
            prod_of_sum.push_back(i);
        }
    }

    cout << "DNF: \n";
    bool flag = true;
    for (size_t i = 0; i < sum_of_prod.size(); i++) {
        if (!flag) {
            cout << " \\/ ";
        }
        
        cout << "m(" << sum_of_prod.at(i) << ')';
        flag = false;
    }
    cout << endl;

    cout << "CNF: \n";
    flag = true;
    for (size_t i = 0; i < prod_of_sum.size(); i++) {
        if (!flag) {
            cout << " /\\ ";
        }
        
        cout << "M(" << prod_of_sum.at(i) << ')';
        flag = false;
    }
    cout << endl;
    
    return;
}

string string_calculator(string s) {
    std::stack<char> st;
	st.push('N');
	int l = s.length();
	string ns;
	for (int i = 0; i < l; i++) {
		if ((s[i] >= 'a' && s[i] <= 'z') ||
			(s[i] >= 'A' && s[i] <= 'Z'))
			ns += s[i];
		else if (s[i] == '(')
			st.push('(');
		else if (s[i] == ')') {
			while (st.top() != 'N' && st.top() != '(') {
				char c = st.top();
				st.pop();
				ns += c;
			}
			if (st.top() == '(') {
				char c = st.top();
				st.pop();
			}
		}
		else {
			while (st.top() != 'N' && prec(s[i]) <= prec(st.top())) {
				char c = st.top();
				st.pop();
				ns += c;
			}
			st.push(s[i]);
		}
	}
	while (st.top() != 'N') {
		char c = st.top();
		st.pop();
		ns += c;
	}

	return ns;
}

int prec(char c) {
	switch (c) {
    case '!':
        return 5;
        break;
    case '&':
        return 4;
        break;
    case '|':
        return 3;
        break;
    case '^':
        return 2;
        break;
    case '~':
        return 1;
        break;
    default:
        return -1;
        break;
    }
}