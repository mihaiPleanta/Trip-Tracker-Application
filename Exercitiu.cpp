#include "Admin.h"
#include "User.h"
#include "Trip.h"

#include <stdexcept>

using namespace std;

int main() {
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"
         << "\n";
    
    try {
        int id;

        cout << "Enter ID (0 for Admin, 1 for User): ";
        cin >> id;

        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            throw invalid_argument("Invalid input. Please enter a number.");
        }

        if (id == 0) {
            // Handle Admin login
            Admin admin;
        } else if (id == 1) {
            // Handle User login
            User user;
        } else {
            throw invalid_argument("Invalid authentication ID");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";

    return 0;
}