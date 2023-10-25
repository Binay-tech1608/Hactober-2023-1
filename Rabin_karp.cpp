#include <iostream>
#include <string>

using namespace std;

const int d = 256; // Number of possible characters in the alphabet

void rabinKarpSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    int q = 101; // A prime number used for hash calculation (can be any prime)

    int hPattern = 0; // Hash value of the pattern
    int hText = 0;    // Hash value of the current window in the text

    // Calculate the hash value of the pattern and the initial window in the text
    for (int i = 0; i < m; i++) {
        hPattern = (hPattern * d + pattern[i]) % q;
        hText = (hText * d + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        // If the hash values match, perform a character-by-character comparison
        if (hPattern == hText) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate the hash value for the next window
        if (i < n - m) {
            hText = (d * (hText - text[i] * static_cast<int>(pow(d, m - 1))) + text[i + m]) % q;
            if (hText < 0) {
                hText += q; // Ensure the hash value is non-negative
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    rabinKarpSearch(text, pattern);

    return 0;
}
