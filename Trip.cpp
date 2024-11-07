#include "Trip.h"
#include "Validation.h"


using namespace std;

void Trip::addTrip() {
    try{
        Validation val;

        cout << "Departure City: ";
        cin >> from;

        if (!val.isUppercaseLetter(from.front())) {
            throw invalid_argument("Departure city must start with an uppercase letter.");
        }

        cout << "Arrival city: ";
        cin >> to;

        if (!val.isUppercaseLetter(to.front())) {
            throw invalid_argument("Arrival city must start with an uppercase letter.");
        }

        cout << "Departure date: ";
        cin >> date;

        if(!val.isValidDate(date)) {
            throw invalid_argument("Invalid date. Date must be dd/mm/yyyy format.");
        }

        cout << "Price: ";
        cin >> price;

        if(!val.isValidPrice(price)) {
            throw invalid_argument("Invalid price. Please enter a positive integer.");
        }

        cout << "Available seats: ";
        cin >> available_seats;

        if(!val.isValidSeats(available_seats)) {
            throw invalid_argument("Invalid number of seats. Please enter an integer between 10 and 50.");
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Clear input buffer in case of invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        exit(1);
    }
    

    ofstream file("Trip.csv", ios::app);

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    // Write the trip data to the file
    file << from << "," << to << "," << date << "," << price << "," << available_seats << endl;

    // Close the file
    file.close();

    cout << "Trip added successfully!" << endl;
}

void Trip::removeTrip() {
    Validation val;

    string criteria_from, criteria_to, criteria_data;

    try {
        
        cout << "Enter Departure City for deletion: ";
        cin >> criteria_from;

        if (!val.isUppercaseLetter(criteria_from.front())) {
            throw invalid_argument("Departure city must start with an uppercase letter.");
        }

        cout << "Enter Arrival City for deletion: ";
        cin >> criteria_to;

        if (!val.isUppercaseLetter(criteria_to.front())) {
            throw invalid_argument("Arrival city must start with an uppercase letter.");
        }

        cout << "Enter date for deletion: ";
        cin >> criteria_data;

        if(!val.isValidDate(criteria_data)) {
            throw invalid_argument("Invalid date. Date must be dd/mm/yyyy format.");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Clear input buffer in case of invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        exit(1);
    }


    // Read the CSV file into a vector
    vector<string> lines;
    ifstream file("Trip.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    // Open the file in write mode (clearing the contents)
    ofstream outFile("Trip.csv");

    // Check if the file is open
    if (!outFile.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    // Rewrite the lines to the file excluding the matching row
    for (const auto& l : lines) {
        istringstream iss(l);
        string token_from, token_to, token_data;

        // Split the line into tokens
        getline(iss, token_from, ','); // from
        getline(iss, token_to, ',');   // to
        getline(iss, token_data, ','); // date

        // Check if the current line matches the deletion criteria
        if (token_from == criteria_from && token_to == criteria_to && token_data == criteria_data) {
            continue;  // Skip writing this line if it matches
        }

        // Write the line to the file if it doesn't match the deletion criteria
        outFile << l << endl;
    }

    // Close the file
    outFile.close();

    cout << "Trip remove successfully!" << endl;
}

void Trip::findTrip() {
    Validation val;

    try {
        cout << "Departure City: ";
        cin >> from;

        if (!val.isUppercaseLetter(from.front())) {
            throw invalid_argument("Departure city must start with an uppercase letter.");
        }

        cout << "Arrival city: ";
        cin >> to;

        if (!val.isUppercaseLetter(to.front())) {
            throw invalid_argument("Arrival city must start with an uppercase letter.");
        }

        cout << "Departure date: ";
        cin >> date;

        if(!val.isValidDate(date)) {
            throw invalid_argument("Invalid date. Date must be dd/mm/yyyy format.");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Clear input buffer in case of invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        exit(1);
    }

    ifstream file("Trip.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        istringstream iss(line);
        string col1, col2, col3, col4, col5;

        if (getline(iss, col1, ',') && getline(iss, col2, ',') && getline(iss, col3, ',') &&
            getline(iss, col4, ',') && getline(iss, col5, ',')) {
            
            if (col1 == from  && col2 == to && col3 == date) {
                found = true;
                cout << "Trip found! " << endl;
                cout << "Departure City: " << col1 << " ";
                cout << "Arrival City: " << col2 << " ";
                cout << "Departure Date: " << col3 << " ";
                cout << "Price: " << col4 << " ";
                cout << "Available Seats: " << col5 << endl;
                break;
            }
        }
    }

    file.close();

    if (!found) {
        cout << "Trip not found." << endl;
        exit(1);
    }
}

void Trip::bookTrip() {
    Validation val;

    int seats;
    try {
        cout << "Number of seats: ";
        cin >> seats;

        if(!val.isValidSeats(seats)) {
            throw invalid_argument("Invalid number of seats. Please enter an integer between 10 and 50.");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Clear input buffer in case of invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        exit(1);
    }
    
    ifstream file("Trip.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool tripFound = false;
    bool tripSeats = false;

    while (getline(file, line)) {
        istringstream iss(line);
        string col1, col2, col3, col4, col5;

        if (getline(iss, col1, ',') && getline(iss, col2, ',') && getline(iss, col3, ',') &&
            getline(iss, col4, ',') && getline(iss, col5, ',')) {
            
            if (col1 == from && col2 == to && col3 == date) {
                tripFound = true;

                int availableSeats = stoi(col5);

                if (availableSeats >= seats) {
                    availableSeats -= seats;
                    tripSeats = true;
                }

                lines.push_back(col1 + "," + col2 + "," + col3 + "," + col4 + "," + to_string(availableSeats));
            } else {
                // If the criteria do not match, keep the line unchanged
                lines.push_back(line);
            }
        }
    }

    file.close();

    if (!tripFound) {
        cout << "Trip not found." << endl;
    } else if (!tripSeats) {
        cout << "Insufficient seats available." << endl;
    } else {
        // Write the updated data back to the CSV file
        ofstream outFile("Trip.csv");

        if (outFile.is_open()) {
            for (const auto& updatedLine : lines) {
                outFile << updatedLine << endl;
            }

            cout << "Trip booked successfully!" << endl;
        } else {
            cerr << "Error opening file for writing" << endl;
        }
    }
}

