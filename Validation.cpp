#include "Validation.h"

using namespace std;

bool Validation::isUppercaseLetter(char c) {
    return isupper(c);
}

bool Validation::isValidPassword(string password) {
     return password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

bool Validation::isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.rfind('.');

    // Check if '@' and '.' are present and '.' comes after '@'
    if (atPos == string::npos || dotPos == string::npos || dotPos <= atPos + 1) {
        return false;
    }

    // Check if the email doesn't start with a number
    if (isdigit(email[0])) {
        return false;
    }

    return true;
}

bool Validation::isValidDate(const string& date) {
    // Use regular expression to check date format (dd/mm/yyyy)
    regex datePattern("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(\\d{4})$");

    return regex_match(date, datePattern);
}

bool Validation::isValidPrice(int price) {
    return price > 0;
}

bool Validation::isValidSeats(int available_seats) {
    return (available_seats >= 1) && (available_seats <= 50); 
}