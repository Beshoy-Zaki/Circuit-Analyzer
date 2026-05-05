#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// To calculate equivalent series resistance
float calc_series(const vector<float>& resistors) {
    float total = 0;
    for (size_t i = 0; i < resistors.size(); ++i) {
        total += resistors[i];
    }
    return total;
}

// To calculate equivalent parallel resistance
float calc_parallel(const vector<float>& resistors) {
    float final = 0;

    // looping through each resistor one by one
    for (size_t i = 0; i < resistors.size(); ++i) {
        final += 1.0 / resistors[i];
        //this is the reciprocal of the parallel resistance
    }
    if (final > 0) {
        return 1.0 / final;
    } else {
        return 0;
    }
}

//this is to remove the additional zeros from the float
string format_result(float value) {
    string result = to_string(value);
    result.erase(result.find_last_not_of('0') + 1);
    if (result.back() == '.') result.pop_back();
    return result;
}
// This function is to extract the resistors values
vector<float> extract_resistor_values(const string& str){
    vector<float> resistors;
    //temp string to store
    string temp;
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (isdigit(c) || c == '.') {
            temp += c;
        } else if (!temp.empty()) {
            resistors.push_back(stof(temp));
            temp.clear();
        }
    }
    if (!temp.empty()) resistors.push_back(stof(temp));
    return resistors;
}
int main() {
    string input_str;
    getline(cin, input_str);
    //Error handling of invalid characters
    if (input_str.find_first_not_of("0123456789.psPSe ") != string::npos) {
        cout << "Wrong Description";
        return 0;
    }
    while(true) {
        bool found = false; // this flag is to return to the loop again
        for (int i = input_str.length() - 1; i >= 0; --i) {
            // tolower allows to search for P or p and S or s
            if (tolower(input_str[i]) == 'p' || tolower(input_str[i]) == 's') {
                char type = input_str[i];
                size_t j = input_str.find('e', i);
                if (j != string::npos) {
                    //taking substring of the last part of the circuit to calculate individually
                    string str = input_str.substr(i+1, j-i-1);
                    input_str.erase(i, j - i + 1);
                    vector<float> resistors = extract_resistor_values(str);
                    //condition to handle the resistors numbers
                    if ((type == 'p' || type == 'P') && resistors.size() < 2) {
                        cout << "Incorrect Input" << endl;
                        return 0;
                    } else if ((type == 's' || type == 'S') && resistors.empty()) {
                        cout << "Incorrect Input" << endl;
                        return 0;
                    }
                    //result calculation
                    float result = (type == 'p' || type == 'P') ? calc_parallel(resistors) : calc_series(resistors);
                    input_str.insert(i,format_result(result));
                    found = true;
                    break;
                }
            }
        }

        // If no calculations were found, we can output the result
        if (!found) {
            cout << "The total resistance = " << format_result(stof(input_str)) << endl;
            break; // to exit the while loop
        }
    }

    return 0;
}
