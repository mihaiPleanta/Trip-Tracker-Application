#include "Trip.h" 
#include "Admin.h"
#include "Validation.h"
#include "RSA.h"

using namespace std;

bool readCSV(const string& filename, vector<pair<string, vector<long long int>>>& data) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string col1, col2;

        if (getline(iss, col1, ',') && getline(iss, col2, ',')) {
            istringstream encryptedStream(col2);
            vector<long long int> encrypted;
            long long int value;

            while (encryptedStream >> value) {
                encrypted.push_back(value);
            }

            data.emplace_back(col1, encrypted);
        } else {
            cerr << "Error: Unable to parse line in the file " << filename << endl;
            return false;
        }
    }

    file.close();
    return true;
}

Admin::Admin() {
    cout << "Login" << endl;

    do {
        try {
            Validation val;
            
            cout << "Username: ";
            cin >> username;

            if (!val.isUppercaseLetter(username.front())) {
                throw invalid_argument("Username must start with an uppercase letter.");
            }
            

            cout << "Password: ";
            cin >> password;

            if (!val.isValidPassword(password)) {
                throw invalid_argument("Password must contain only letters.");
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (!verifyUsernamePassword(username, password));

    try {
        int aux;

        cout << "Choose an action (0: Add Trip, 1: Remove Trip): ";
        cin >> aux;

        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            throw invalid_argument("Invalid input. Please enter a number.");
        }

        if (aux == 0) {
            // Handle adding a trip
            Trip trip;
            trip.addTrip();
        } else if (aux == 1) {
            // Handle removing a trip
            Trip trip;
            trip.removeTrip();
        } else {
            throw invalid_argument("Invalid choice. Please enter 0 or 1.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

bool Admin::verifyUsernamePassword(string username, string password) {
    RSA rsa;
    vector<long long int> encrypted = rsa.encoder(password);

    string filename = "Admin.csv";
    vector<pair<string, vector<long long int>>> csvData;

    if (readCSV(filename, csvData)) {
        for (const auto& entry : csvData) {
            if (entry.first == username && entry.second == encrypted) {
                cout << "Authentication successful!" << endl;
                return true;
            }
        }
    } else {
        cerr << "Failed to read the CSV file." << endl;
    }

    cout << "Authentication failed. Incorrect username or password. Try again!" << endl;
    return false;
}