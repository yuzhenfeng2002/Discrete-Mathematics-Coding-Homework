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
    vector<vector<bool>> relation_matrix;

public:
    Relation(int elem_num, vector<vector<bool>> relation_matrix);
    Relation& operator= (const Relation& r);
    friend std::ostream& operator<< (std::ostream& out, const Relation& r);
    Relation reflexive_closure();
    Relation symmetric_closure();
    Relation transitive_closure();
};

// Main Function
int main() {
    int elem_num;
    cout << "Please input the number of the elements in the set: ";
    cin >> elem_num;

    auto relation_matrix = vector<vector<bool>>(elem_num, vector<bool>(elem_num, false));
    cout << "Please input the relation matrix: \n";
    for (size_t i = 0; i < elem_num; i++) {
        cout << "Line " << i << ": ";
        for (size_t j = 0; j < elem_num; j++) {
            bool is_related;
            cin >> is_related;
            relation_matrix.at(i).at(j) = is_related;
        }
    }
    Relation r = Relation(elem_num, relation_matrix);

    int opt = 0;
    while (opt != 4) {
        cout << "----------\n";
        cout << "1. Reflexive Closure\n";
        cout << "2. Symmetric Closure\n";
        cout << "3. Transitive Closure\n";
        cout << "4. Exit\n";
        cout << "Select: ";
        cin >> opt;
        if (opt == 1) {
            cout << r.reflexive_closure();
        }
        if (opt == 2) {
            cout << r.symmetric_closure();
        }
        if (opt == 3) {
            cout << r.transitive_closure();
        }
    }
    
    system("pause");
    return 0;
}

// Initialize a Class
Relation::Relation(int elem_num, vector<vector<bool>> relation_matrix) {
    this->elem_num = elem_num;
    this->relation_matrix = relation_matrix;
}

// Print the Relation
std::ostream& operator<<(std::ostream& out, const Relation& r)
{
	for (size_t i = 0; i < r.elem_num; i++) {
        for (size_t j = 0; j < r.elem_num; j++) {
            cout << r.relation_matrix.at(i).at(j) << ' ';
        }
        cout << endl;
    }
    return out;
}

// Overload the Assignment Operator
Relation& Relation::operator= (const Relation& r)
{
    this->elem_num  = r.elem_num;
    this->relation_matrix = r.relation_matrix;
    return *this;
}

Relation Relation::reflexive_closure() {
    Relation rr = *this;
    for (size_t i = 0; i < rr.elem_num; i++) {
        rr.relation_matrix.at(i).at(i) = true;
    }
    return rr;
}

Relation Relation::symmetric_closure() {
    Relation sr = *this;
    for (size_t i = 0; i < sr.elem_num; i++) {
        for (size_t j = 0; j < sr.elem_num; j++) {
            sr.relation_matrix.at(i).at(j) = sr.relation_matrix.at(i).at(j) || sr.relation_matrix.at(j).at(i);
        }
    }
    return sr;
}

Relation Relation::transitive_closure() {
    Relation tr = *this;
    Relation multi = *this;
    for (size_t i = 1; i < tr.elem_num; i++) {
        for (size_t j = 0; j < tr.elem_num; j++) {
            for (size_t k = 0; k < tr.elem_num; k++) {
                for (size_t l = 0; l < tr.elem_num; l++) {
                    multi.relation_matrix.at(j).at(k) = 
                        multi.relation_matrix.at(j).at(k) || (multi.relation_matrix.at(j).at(l) && this->relation_matrix.at(l).at(k));
                }
            }
        }
        
        for (size_t j = 0; j < tr.elem_num; j++) {
            for (size_t k = 0; k < tr.elem_num; k++) {
                tr.relation_matrix.at(j).at(k) = tr.relation_matrix.at(j).at(k) || multi.relation_matrix.at(j).at(k);
            }
        }
    }
    
    return tr;
}