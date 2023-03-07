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

// Define a Relation Class
class Relation {
private:
    int elem_num;
    vector<string> elem_names;
    map<string, int> elem_name_map;
    vector<vector<bool>> relation_matrix;

public:
    Relation(int elem_num, vector<string> elem_names);
    void add_relation(string elem1, string elem2);
    Relation& operator= (const Relation& r);
    Relation warshall();
    friend std::ostream& operator<< (std::ostream& out, const Relation& r);
};

// Main Function
int main() {
    int elem_num;
    cout << "Please input the number of the elements in the set. Press ENTER to continue.\n";
    cin >> elem_num;

    auto elem_names = vector<string>(elem_num);
    cout << "Please input the names of the elements in the set. Press ENTER to continue.\n";
    for (size_t i = 0; i < elem_num; i++) {
        cin >> elem_names.at(i);
    }

    Relation r = Relation(elem_num, elem_names);
    int relation_num;
    cout << "Please input the number of the elements in the relation R. Press ENTER to continue.\n";
    cin >> relation_num;
    cout << "Please input the " << relation_num 
         << " element(s) of R, one element in one line. Press ENTER to continue.\n";
    for (size_t i = 0; i < relation_num; i++) {
        string elem1, elem2;
        cin >> elem1;
        cin >> elem2;
        r.add_relation(elem1, elem2);
    }
    auto tr = r.warshall();
    cout << "The transitive closure of R is:\n";
    cout << "t(R) = " << tr;
    
    system("pause");
    return 0;
}

// Initialize a Class
Relation::Relation(int elem_num, vector<string> elem_names) {
    this->elem_num = elem_num;
    for (size_t i = 0; i < elem_names.size(); i++)
    {
        this->elem_name_map.insert(std::make_pair(elem_names.at(i), i));
    }
    this->elem_names = elem_names;
    this->relation_matrix = vector<vector<bool>>(elem_num, vector<bool>(elem_num, false));
}

// Add Elements to the Relation
void Relation::add_relation(string elem1, string elem2) {
    auto idx1 = this->elem_name_map.find(elem1);
    auto idx2 = this->elem_name_map.find(elem2);
    if (idx1 != this->elem_name_map.end() && idx2 != this->elem_name_map.end()) {
        this->relation_matrix.at(idx1->second).at(idx2->second) = true;
    } else {
        cout << "WARNING: The element is not in the set.\n";
    }
}

// Print the Relation
std::ostream& operator<<(std::ostream& out, const Relation& r)
{
	bool isBegin = true;
    out << '{';
    for (size_t i = 0; i < r.elem_num; i++) {
        for (size_t j = 0; j < r.elem_num; j++)
        {
            if (r.relation_matrix.at(i).at(j))
            {
                if (!isBegin) {
                    out << ", ";
                }
                isBegin = false;
                out << '<' << r.elem_names.at(i) << ", " << r.elem_names.at(j) << '>';
            }
        }
    }
    out << "}\n";
	return out;
}

// Overload the Assignment Operator
Relation& Relation::operator= (const Relation& r)
{
    this->elem_num  = r.elem_num;
    this->elem_name_map = r.elem_name_map;
    this->relation_matrix = r.relation_matrix;
    return *this;
}

// Warshall
Relation Relation::warshall() {
    auto tr = *this;
    for (size_t k = 0; k < this->elem_num; k++) {
        for (size_t i = 0; i < this->elem_num; i++) {
            for (size_t j = 0; j < this->elem_num; j++) {
                tr.relation_matrix.at(i).at(j) = tr.relation_matrix.at(i).at(j) || (tr.relation_matrix.at(i).at(k) && tr.relation_matrix.at(k).at(j));
            }
        }
    }
    return tr;
}