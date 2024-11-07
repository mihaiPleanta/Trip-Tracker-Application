#ifndef VALIDATION_H
#define VALIDATION_H
#include<string>
#include<regex>

using namespace std;

class Validation {
public:
    bool isUppercaseLetter(char c);
    bool isValidPassword(string password);
    bool isValidEmail(const string& email);
    bool isValidDate(const string& date);
    bool isValidPrice(int price);
    bool isValidSeats(int available_seats);
};

#endif