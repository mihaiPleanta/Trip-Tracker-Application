#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <cmath>


using namespace std;

class RSA {
private:
    long long int p, q, n, e, d;

    long long int mod_pow(long long int base, long long int exponent, long long int modulus);

    long long int mod_inverse(long long int a, long long int m);

public:
    RSA();

    vector<long long int> encoder(const string& message);

    string decoder(const vector<long long int>& encrypted);
};


#endif