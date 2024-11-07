#include "Trip.h"
#include "User.h"
#include "Validation.h"
#include "RSA.h"

bool readCSVUser(const string& filename, vector<vector<string>>& fileContent) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        fileContent.push_back(row);
    }

    file.close();
    return true;
}

User::User() {
    try {
        int aux;

        cout << "Choose an action (0: Login, 1: Register): ";
        cin >> aux;

        if (cin.fail() || (aux != 0 && aux != 1)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            throw invalid_argument("Invalid input. Please enter 0 or 1.");
        }

        if (aux == 0) {
            // Login logic
            do {
                try{
                    Validation val;

                    cout << "Login" << endl;

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

                    cout << "Email: ";
                    cin >> email;

                    if (!val.isValidEmail(email)) {
                        throw invalid_argument("Invalid email format. It should be in the form: user@example.com");
                    }

                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                    // Clear input buffer in case of invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!verifyUsernamePassword(username, password, email));
        } else if (aux == 1) {
            // Registration logic
            do {
                try {
                    Validation val;

                    cout << "Register" << endl;

                    cout << "Username: ";
                    cin >> username;

                    if (!val.isUppercaseLetter(username.front())) {
                        throw invalid_argument("Username must start with an uppercase letter.");
                    }

                    cout << "Email: ";
                    cin >> email;

                    if (!val.isValidEmail(email)) {
                        throw invalid_argument("Invalid email format. It should be in the form: user@example.com");
                    }

                    cout << "Password: ";
                    cin >> password;

                    if (!val.isValidPassword(password)) {
                        throw invalid_argument("Password must contain only letters.");
                    }

                    cout << "Repet Password: ";
                    cin >> repet_password;

                    if (!val.isValidPassword(password)) {
                        throw invalid_argument("Password must contain only letters.");
                    }
                    
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                    // Clear input buffer in case of invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    exit(1);
                }
            } while (!verifyNewUser(username, password, email, repet_password));
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        exit(1);
    }
    

    cout << "-Find a trip: " << endl;
    Trip trip;
    trip.findTrip();

    char answer;

     try {
        cout << "-Book a trip? (Y/N)" << endl;
        cout << "Your answer: ";
        cin >> answer;

        // Check if the input is a single character and either 'Y' or 'N'
        if (cin.fail() || cin.peek() != '\n' || (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n')) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            throw invalid_argument("Invalid input. Please enter 'Y' or 'N'.");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Handle the error as needed, you can exit or take other actions.
        exit(1);
    }

    if (answer == 'Y' || answer == 'y') {
        trip.bookTrip();
    } else if (answer == 'N' || answer == 'n') {
        cout << "Thank you for visiting! We appreciate your time and interest. If you have any questions or feedback, feel free to reach out. Have a wonderful day!" << endl;
    }
}

bool User::verifyUsernamePassword(string username, string password, string email) {
    RSA rsa;
    vector<long long int> encrypted = rsa.encoder(password);

    // Specify the CSV file path
    const string filename = "User.csv";
    vector<vector<string>> fileContent;

    // Read the CSV file
    if (readCSVUser(filename, fileContent)) {
        // Check if the provided username, password, and email match any entry
        for (const auto& row : fileContent) {
            if (row.size() == 3) {
                const string& storedUsername = row[0];
                const string& storedEmail = row[2];

                // Assuming that the encrypted password is stored as a space-separated string
                const string& storedEncrypted = row[1];

                // Convert the storedEncrypted string to a vector<long long int>
                istringstream iss(storedEncrypted);
                vector<long long int> storedEncryptedVec;
                long long int value;
                while (iss >> value) {
                    storedEncryptedVec.push_back(value);
                }

                // Compare the stored encrypted vector with the generated encrypted vector
                if (storedUsername == username && storedEmail == email && storedEncryptedVec == encrypted) {
                    cout << "Authentication successful!" << endl;
                    return true;  // Authentication successful
                }
            }
        }
    } else {
        cerr << "Failed to read the CSV file." << endl;
    }

    cout << "Authentication failed. Incorrect username, password, or email. Try again!" << endl;
    return false;
}

bool User::verifyNewUser(string username, string password, string email, string repet_password) {
    if (password != repet_password) {
        cout << "Incorrect password confirmation" << endl;
        return false;
    }

    RSA rsa;
    vector<long long int> encrypted = rsa.encoder(password);

    // Specify the CSV file path
    string filename = "User.csv";
    vector<vector<string>> fileContent;

    // Read the existing CSV file
    if (readCSVUser(filename, fileContent)) {
        // Check if the new user already exists
        for (const auto& row : fileContent) {
            if (row.size() == 3 && row[0] == username) {
                cout << "User with the same username already exists" << endl;
                return false;
            }
            if (row.size() == 3 && row[2] == email) {
                cout << "User with the same email already exists" << endl;
                return false;
            }
        }

        // If the new user doesn't exist, append it to the existing data
        ofstream file(filename, ios::app); // Open the file in append mode

        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return false;
        }

        // Write the new user data to the CSV file
        file << username << ",";
        for (const auto& value : encrypted) {
            file << value << " ";
        }
        file << "," << email << endl;  
        file.close();

        cout << "User registered successfully!" << endl;
        return true;
    } else {
        cerr << "Failed to read the CSV file." << endl;
    }

    return false;
}



