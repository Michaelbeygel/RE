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

        case 32:  out = static_cast<char>(73);  return true; 
        case 33:  out = static_cast<char>(74);  return true; 
        case 34:  out = static_cast<char>(85);  return true;
        case 35:  out = static_cast<char>(122); return true; 
        case 36:  out = static_cast<char>(98);  return true; 
        case 38:  out = static_cast<char>(111); return true; 
        case 39:  out = static_cast<char>(75);  return true; 
        case 40:  out = static_cast<char>(69);  return true; 
        case 41:  out = static_cast<char>(110); return true; 
        case 42:  out = static_cast<char>(41);  return true; 
        case 43:  out = static_cast<char>(88);  return true; 
        case 44:  out = static_cast<char>(108); return true; 
        case 45:  out = static_cast<char>(40);  return true; 
        case 46:  out = static_cast<char>(32);  return true; 
        case 47:  out = static_cast<char>(102); return true; 
        case 48:  out = static_cast<char>(96);  return true; 
        case 49:  out = static_cast<char>(61);  return true; 
        case 50:  out = static_cast<char>(64);  return true; 
        case 51:  out = static_cast<char>(66);  return true; 
        case 52:  out = static_cast<char>(92);  return true; 

        case 53:  out = static_cast<char>(33);  return true;
        case 54:  out = static_cast<char>(79);  return true; 
        case 55:  out = static_cast<char>(119); return true; 
        case 56:
        {
            if(count >1)
            {
            out = static_cast<char>(42); 
             return true;

            }
            else return false;
        }   // '8' -> '*'
        case 57:  out = static_cast<char>(107); return true; 
        case 58:  out = static_cast<char>(76);  return true; 

        case 59:  out = static_cast<char>(87);   return true; 
        case 60:  out = static_cast<char>(90);  return true;
        case 61:  out = static_cast<char>(113); return true; 
        case 62:  out = static_cast<char>(35);  return true; 
        case 63:  out = static_cast<char>(97);  return true; 

        case 64:  out = static_cast<char>(46);  return true; 
        case 65:  out = static_cast<char>(36);  return true; 
        case 66:  out = static_cast<char>(47);  return true; 
        case 67:  out = static_cast<char>(86);  return true; 

        case 68:  out = static_cast<char>(48);   return true; 
        case 69:  out = static_cast<char>(43);  return true; 
        case 70:  out = static_cast<char>(50);  return true;
        case 71:  out = static_cast<char>(39);  return true;
        case 72:  out = static_cast<char>(93);  return true; 
        case 73:  out = static_cast<char>(38);  return true; 
        case 74:  out = static_cast<char>(67);  return true; 
        case 75:  out = static_cast<char>(70);  return true; 
        case 76:  out = static_cast<char>(89);  return true; 
        case 77:  out = static_cast<char>(103); return true; 
        case 78:  out = static_cast<char>(109); return true; 
        case 79:  out = static_cast<char>(94);  return true; 
        case 80:  out = static_cast<char>(126); return true; 
        case 81:  out = static_cast<char>(125); return true; 
        case 82:  out = static_cast<char>(49);  return true; 
        case 83:  out = static_cast<char>(91);  return true; 
        case 84:  out = static_cast<char>(106); return true; 
        case 85:  out = static_cast<char>(115); return true; 
        case 86:  out = static_cast<char>(117); return true; 
        case 87:  out = static_cast<char>(81);  return true; 
        case 88:  out = static_cast<char>(72);  return true; 
        case 89:  out = static_cast<char>(56);  return true; 
        case 90:  out = static_cast<char>(55);  return true; 
        case 91:  out = static_cast<char>(95);  return true; 
        case 92:  out = static_cast<char>(63);  return true; 
        case 93:  out = static_cast<char>(54);  return true; 
        case 94:  out = static_cast<char>(118); return true;
        case 95:  out = static_cast<char>(77);  return true; 

        case 96:  out = static_cast<char>(34);  return true; 
        case 97:  out = static_cast<char>(80);  return true; 
        case 98:  out = static_cast<char>(99);  return true; 
        case 99:  out = static_cast<char>(123); return true; 
        case 100: out = static_cast<char>(37);  return true; 
        case 101: out = static_cast<char>(44);  return true; 
        case 102: out = static_cast<char>(82);  return true; 
        case 103: out = static_cast<char>(57);  return true; 
        case 104: out = static_cast<char>(100); return true; 
        case 105: out = static_cast<char>(124); return true;
        case 106: out = static_cast<char>(68);  return true; 
        case 107: out = static_cast<char>(51);  return true; 
        case 108: out = static_cast<char>(112); return true; 
        case 109: out = static_cast<char>(60);  return true; 
        case 110: out = static_cast<char>(121); return true; 
        case 111: out = static_cast<char>(105); return true; 
        case 112: out = static_cast<char>(116); return true; 
        case 113: out = static_cast<char>(62);  return true; 
        case 114: out = static_cast<char>(58);  return true; 
        case 115: out = static_cast<char>(59);  return true; 
        case 116: out = static_cast<char>(104); return true;
        case 117: out = static_cast<char>(71);  return true; 
        case 118: out = static_cast<char>(78);  return true; 

        case 119: out = static_cast<char>(53);   return true; 

        case 120: out = static_cast<char>(114); return true; 
        case 121: out = static_cast<char>(84);  return true; 
        case 122: out = static_cast<char>(52);  return true; 

        case 123: out = static_cast<char>(83);   return true; 

        case 124: out = static_cast<char>(65);  return true;
        case 125: out = static_cast<char>(45);  return true; 

        case 126: out = static_cast<char>(120);  return true; 

        default:
            return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    string input = argv[1];
    string output;

    for (unsigned char c : input) {
        if (c > 127) {
            return 1;
        }

        char decoded;
        
        if (!inverse_map(c, decoded,argc)) {

            return 1;
        }

        output.push_back(decoded);
    }

    cout << output << endl;
    return 0;
}
