#include <iostream>
#include <string>
using namespace std;

bool inverse_map(unsigned char c, char& out,int count) {
    switch (c) {
        case 1:   out = static_cast<char>(20); return true;
        case 9:   out = static_cast<char>(4);  return true;
        case 12:  out = static_cast<char>(31); return true;
        case 16:  out = static_cast<char>(15); return true;
        case 18:  out = static_cast<char>(24); return true;
        case 22:  out = static_cast<char>(16); return true;

        case 32:  out = static_cast<char>(73);  return true; // ' ' -> 'I'
        case 33:  out = static_cast<char>(74);  return true; // '!' -> 'J'
        case 34:  out = static_cast<char>(85);  return true; // '"' -> 'U'
        case 35:  out = static_cast<char>(122); return true; // '#' -> 'z'
        case 36:  out = static_cast<char>(98);  return true; // '$' -> 'b'
        case 38:  out = static_cast<char>(111); return true; // '&' -> 'o'
        case 39:  out = static_cast<char>(75);  return true; // '\'' -> 'K'
        case 40:  out = static_cast<char>(69);  return true; // '(' -> 'E'
        case 41:  out = static_cast<char>(110); return true; // ')' -> 'n'
        case 42:  out = static_cast<char>(41);  return true; // '*' -> ')'
        case 43:  out = static_cast<char>(88);  return true; // '+' -> 'X'
        case 44:  out = static_cast<char>(108); return true; // ',' -> 'l'
        case 45:  out = static_cast<char>(40);  return true; // '-' -> '('
        case 46:  out = static_cast<char>(32);  return true; // '.' -> ' '
        case 47:  out = static_cast<char>(102); return true; // '/' -> 'f'
        case 48:  out = static_cast<char>(96);  return true; // '0' -> '`'
        case 49:  out = static_cast<char>(61);  return true; // '1' -> '='
        case 50:  out = static_cast<char>(64);  return true; // '2' -> '@'
        case 51:  out = static_cast<char>(66);  return true; // '3' -> 'B'
        case 52:  out = static_cast<char>(92);  return true; // '4' -> '\\'

        case 53:  out = static_cast<char>(33);  return true; // '5' collision: also 33
        case 54:  out = static_cast<char>(79);  return true; // '6' -> 'O'
        case 55:  out = static_cast<char>(119); return true; // '7' -> 'w'
        case 56:
        {
            if(count >1)
            {
            out = static_cast<char>(42); 
             return true;

            }
            else return false;
        }   // '8' -> '*'
        case 57:  out = static_cast<char>(107); return true; // '9' -> 'k'
        case 58:  out = static_cast<char>(76);  return true; // ':' -> 'L'

        case 59:  out = static_cast<char>(87);   return true; // ';' collision: also 87
        case 60:  out = static_cast<char>(90);  return true; // '<' -> 'Z'
        case 61:  out = static_cast<char>(113); return true; // '=' -> 'q'
        case 62:  out = static_cast<char>(35);  return true; // '>' -> '#'
        case 63:  out = static_cast<char>(97);  return true; // '?' -> 'a'

        case 64:  out = static_cast<char>(46);  return true; // '@' collision: also 46
        case 65:  out = static_cast<char>(36);  return true; // 'A' -> '$'
        case 66:  out = static_cast<char>(47);  return true; // 'B' -> '/'
        case 67:  out = static_cast<char>(86);  return true; // 'C' -> 'V'

        case 68:  out = static_cast<char>(48);   return true; // 'D' collision: also 48
        case 69:  out = static_cast<char>(43);  return true; // 'E' -> '+'
        case 70:  out = static_cast<char>(50);  return true; // 'F' -> '2'
        case 71:  out = static_cast<char>(39);  return true; // 'G' -> '\''
        case 72:  out = static_cast<char>(93);  return true; // 'H' -> ']'
        case 73:  out = static_cast<char>(38);  return true; // 'I' -> '&'
        case 74:  out = static_cast<char>(67);  return true; // 'J' -> 'C'
        case 75:  out = static_cast<char>(70);  return true; // 'K' -> 'F'
        case 76:  out = static_cast<char>(89);  return true; // 'L' -> 'Y'
        case 77:  out = static_cast<char>(103); return true; // 'M' -> 'g'
        case 78:  out = static_cast<char>(109); return true; // 'N' -> 'm'
        case 79:  out = static_cast<char>(94);  return true; // 'O' -> '^'
        case 80:  out = static_cast<char>(126); return true; // 'P' -> '~'
        case 81:  out = static_cast<char>(125); return true; // 'Q' -> '}'
        case 82:  out = static_cast<char>(49);  return true; // 'R' -> '1'
        case 83:  out = static_cast<char>(91);  return true; // 'S' -> '['
        case 84:  out = static_cast<char>(106); return true; // 'T' -> 'j'
        case 85:  out = static_cast<char>(115); return true; // 'U' -> 's'
        case 86:  out = static_cast<char>(117); return true; // 'V' -> 'u'
        case 87:  out = static_cast<char>(81);  return true; // 'W' -> 'Q'
        case 88:  out = static_cast<char>(72);  return true; // 'X' -> 'H'
        case 89:  out = static_cast<char>(56);  return true; // 'Y' -> '8'
        case 90:  out = static_cast<char>(55);  return true; // 'Z' -> '7'
        case 91:  out = static_cast<char>(95);  return true; // '[' -> '_'
        case 92:  out = static_cast<char>(63);  return true; // '\\' -> '?'
        case 93:  out = static_cast<char>(54);  return true; // ']' -> '6'
        case 94:  out = static_cast<char>(118); return true; // '^' -> 'v'
        case 95:  out = static_cast<char>(77);  return true; // '_' -> 'M'

        case 96:  out = static_cast<char>(34);  return true; // '`' collision: also 34
        case 97:  out = static_cast<char>(80);  return true; // 'a' -> 'P'
        case 98:  out = static_cast<char>(99);  return true; // 'b' -> 'c'
        case 99:  out = static_cast<char>(123); return true; // 'c' -> '{'
        case 100: out = static_cast<char>(37);  return true; // 'd' -> '%'
        case 101: out = static_cast<char>(44);  return true; // 'e' -> ','
        case 102: out = static_cast<char>(82);  return true; // 'f' -> 'R'
        case 103: out = static_cast<char>(57);  return true; // 'g' -> '9'
        case 104: out = static_cast<char>(100); return true; // 'h' -> 'd'
        case 105: out = static_cast<char>(124); return true; // 'i' -> '|'
        case 106: out = static_cast<char>(68);  return true; // 'j' -> 'D'
        case 107: out = static_cast<char>(51);  return true; // 'k' -> '3'
        case 108: out = static_cast<char>(112); return true; // 'l' -> 'p'
        case 109: out = static_cast<char>(60);  return true; // 'm' -> '<'
        case 110: out = static_cast<char>(121); return true; // 'n' -> 'y'
        case 111: out = static_cast<char>(105); return true; // 'o' -> 'i'
        case 112: out = static_cast<char>(116); return true; // 'p' -> 't'
        case 113: out = static_cast<char>(62);  return true; // 'q' -> '>'
        case 114: out = static_cast<char>(58);  return true; // 'r' -> ':'
        case 115: out = static_cast<char>(59);  return true; // 's' -> ';'
        case 116: out = static_cast<char>(104); return true; // 't' -> 'h'
        case 117: out = static_cast<char>(71);  return true; // 'u' -> 'G'
        case 118: out = static_cast<char>(78);  return true; // 'v' -> 'N'

        case 119: out = static_cast<char>(53);   return true; // 'w' collision: also 10, 53

        case 120: out = static_cast<char>(114); return true; // 'x' -> 'r'
        case 121: out = static_cast<char>(84);  return true; // 'y' -> 'T'
        case 122: out = static_cast<char>(52);  return true; // 'z' -> '4'

        case 123: out = static_cast<char>(83);   return true; // '{' collision: also 9, 83

        case 124: out = static_cast<char>(65);  return true; // '|' -> 'A'
        case 125: out = static_cast<char>(45);  return true; // '}' -> '-'

        case 126: out = static_cast<char>(120);  return true; // '~' collision: also 120

        default:
            return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <mapped_string>\n";
        return 1;
    }

    string input = argv[1];
    string output;

    for (unsigned char c : input) {
        if (c > 127) {
            cerr << "Non-ASCII character encountered: " << static_cast<int>(c) << "\n";
            return 1;
        }

        char decoded;
        
        if (!inverse_map(c, decoded,argc)) {
            cerr << "No inverse mapping for ASCII value "
                 << static_cast<int>(c)
                 << " ('" << c << "')\n";
            return 1;
        }

        output.push_back(decoded);
    }

    cout << output << endl;
    return 0;
}