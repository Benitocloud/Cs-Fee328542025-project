
#include <iostream>
#include <string
#include <vector>

using namespace std;

void displayBits(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    string input;
    int d[4]; 
    int c[7]; 

    cout << "--- Hamming (7,4) C++ Engine ---" << endl;
    
    while (true) {
        cout << "Enter 4-bit data (e.g., 1101): ";
        cin >> input;
        if (input.length() == 4 && input.find_first_not_of("01") == string::npos) {
            for (int i = 0; i < 4; i++) d[i] = input[i] - '0';
            break;
        }
        cout << "Invalid input. Try again." << endl;
    }


    c[0] = d[0] ^ d[1] ^ d[3]; // P1 
    c[1] = d[0] ^ d[2] ^ d[3]; // P2 
    c[2] = d[0];               // D1
    c[3] = d[1] ^ d[2] ^ d[3]; // P3
    c[4] = d[1];               // D2
    c[5] = d[2];               // D3
    c[6] = d[3];               // D4

    cout << "\nEncoded Codeword: "; displayBits(c, 7);

    int pos;
    cout << "\nInject error at position (1-7, or 0 for none): ";
    cin >> pos;
    if (pos >= 1 && pos <= 7) {
        c[pos - 1] ^= 1;
        cout << "Bit " << pos << " flipped!" << endl;
    }

    int s1 = c[0] ^ c[2] ^ c[4] ^ c[6];
    int s2 = c[1] ^ c[2] ^ c[5] ^ c[6];
    int s3 = c[3] ^ c[4] ^ c[5] ^ c[6];
    int errorLoc = (s3 << 2) | (s2 << 1) | s1;

    cout << "\nSyndrome (S3S2S1): " << s3 << s2 << s1 << " (Dec: " << errorLoc << ")" << endl;
    if (errorLoc == 0) {
        cout << "Status: No errors detected." << endl;
    } else {
        cout << "Status: Error detected at position " << errorLoc << ". Correcting..." << endl;
        c[errorLoc - 1] ^= 1;
        cout << "Fixed Codeword: "; displayBits(c, 7);
    }

    return 0;

}
