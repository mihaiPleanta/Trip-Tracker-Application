#include "RSA.h"

long long int RSA::mod_pow(long long int base, long long int exponent, long long int modulus) {
        long long int result = 1;
        base = base % modulus;

        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = (result * base) % modulus;
            }
            exponent = exponent >> 1;
            base = (base * base) % modulus;
        }

        return result;
    }

long long int RSA::mod_inverse(long long int a, long long int m) {
        for (long long int x = 1; x < m; x++) {
            if ((a * x) % m == 1) {
                return x;
            }
        }
        return -1; // Should not happen for RSA
    }

RSA::RSA() {
        // You may replace these with secure methods of key generation
        p = 61; // Replace with a large prime number
        q = 53; // Replace with another large prime number
        n = p * q;
        long long int phi = (p - 1) * (q - 1);
        e = 17; // A common choice for e
        d = mod_inverse(e, phi);
    }

vector<long long int> RSA::encoder(const string& message) {
        vector<long long int> encrypted;

        for (char c : message) {
            long long int encrypted_char = mod_pow(c, e, n);
            encrypted.push_back(encrypted_char);
        }

        return encrypted;
    }

string RSA::decoder(const vector<long long int>& encrypted) {
        string decrypted;

        for (long long int encrypted_char : encrypted) {
            char decrypted_char = static_cast<char>(mod_pow(encrypted_char, d, n));
            decrypted.push_back(decrypted_char);
        }

        return decrypted;
    }