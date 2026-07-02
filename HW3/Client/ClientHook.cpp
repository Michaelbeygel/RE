#include <iostream>
#include <string>

std::string decode_string(std::string encoded) {
    std::string decoded = "";
    int i = 0;
    int len = encoded.length();
    
    bool is_high_nibble = true;
    unsigned char high_nibble = 0;

    while (i < len) {
        unsigned char current_nibble = 0;
        char c = encoded[i];

        if (c == 'A') {
            current_nibble = 1;
            i += 1;
        } else if (c == 'J') {
            current_nibble = 10;
            i += 1;
        } else if (c == 'Q') {
            current_nibble = 11;
            i += 1;
        } else if (c == 'K') {
            current_nibble = 12;
            i += 1;
        } else if (c >= '0' && c <= '9') {
            if (i + 2 < len && (encoded[i+1] == '+' || encoded[i+1] == '-')) {
                int val1 = c - '0';
                char op = encoded[i+1];
                int val2 = encoded[i+2] - '0';

                if (op == '+') {
                    current_nibble = val1 + val2;
                } else if (op == '-') {
                    current_nibble = val1 - val2;
                }
                i += 3;
            } else {
                current_nibble = c - '0';
                i += 1;
            }
        } else {
            i += 1;
            continue;
        }

        if (is_high_nibble) {
            high_nibble = current_nibble;
            is_high_nibble = false;
        } else {
            char decoded_char = (high_nibble << 4) | current_nibble;
            decoded += decoded_char;
            is_high_nibble = true;
        }
    }

    return decoded;
}
