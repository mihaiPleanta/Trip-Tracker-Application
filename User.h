#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    string email;
    string repet_password;

public:
    User();

    bool verifyUsernamePassword(string username, string password, string email);
    bool verifyNewUser(string username, string password, string email, string repet_password);
};

#endif