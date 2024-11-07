#ifndef ADMIN_H
#define ADMIN_H
#include<string>

using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    Admin();

    bool verifyUsernamePassword(string username, string password);
};

#endif