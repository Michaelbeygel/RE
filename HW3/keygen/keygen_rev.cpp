#include <iostream>
#include <string>
#include <map>
#include <vector>

char reverse_char(char transformed_char) {
    static const std::map<char, char> reverse_map = {
        {'.', ' '},   {'>', '#'},  {'A', '$'},  {'d', '%'},  {'I', '&'},
        {'G', '\''},  {'-', '('},  {'*', ')'},  {'E', '+'},  {'e', ','},
        {'}', '-'},   {'@', '.'},  {'B', '/'},  {'D', '0'},  {'R', '1'},
        {'F', '2'},   {'k', '3'},  {'z', '4'},  {'w', '5'},  {']', '6'},
        {'Z', '7'},   {'Y', '8'},  {'g', '9'},  {'r', ':'},  {'s', ';'},
        {'m', '<'},   {'1', '='},  {'q', '>'},  {'\\','?'},  {'2', '@'},
        {'|', 'A'},   {'3', 'B'},  {'J', 'C'},  {'j', 'D'},  {'(', 'E'},
        {'K', 'F'},   {'u', 'G'},  {'X', 'H'},  {' ', 'I'},  {'!', 'J'},
        {'\'', 'K'},  {':', 'L'},  {'_', 'M'},  {'v', 'N'},  {'6', 'O'},
        {'a', 'P'},   {'W', 'Q'},  {'f', 'R'},  {'{', 'S'},  {'y', 'T'},
        {'"', 'U'},   {'C', 'V'},  {';', 'W'},  {'+', 'X'},  {'L', 'Y'},
        {'<', 'Z'},   {'S', '['},  {'4', '\\'}, {'H', ']'},  {'O', '^'},
        {'[', '_'},   {'0', '`'},  {'?', 'a'},  {'$', 'b'},  {'b', 'c'},
        {'h', 'd'},   {'/', 'f'},  {'M', 'g'},  {'t', 'h'},  {'o', 'i'},
        {'T', 'j'},   {'9', 'k'},  {',', 'l'},  {'N', 'm'},  {')', 'n'},
        {'&', 'o'},   {'l', 'p'},  {'=', 'q'},  {'x', 'r'},  {'U', 's'},
        {'p', 't'},   {'V', 'u'},  {'^', 'v'},  {'7', 'w'},  {'~', 'x'},
        {'n', 'y'},   {'#', 'z'},  {'c', '{'},  {'i', '|'},  {'Q', '}'},
        {'P', '~'},   {'8', '*'}
    };

    auto it = reverse_map.find(transformed_char);
    if (it != reverse_map.end()) {
        return it->second;
    }
    
    return '?';
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 1;
    }

    std::string transformed_password = argv[1];
    std::string original_password = "";

    for (char c : transformed_password) {
        original_password += reverse_char(c);
    }

    std::cout << original_password << std::endl;

    return 0;
}