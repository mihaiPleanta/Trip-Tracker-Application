# Trip-Tracker-Application

Trip-Tracker-Application is a console-based application designed for managing travel bookings. The system allows users to register, login, find available trips, and book seats. It includes a variety of validation checks to ensure that the data entered by users is in the correct format. The application also uses RSA encryption for secure password storage and authentication.

Features
User Registration: New users can create an account by providing a username, password, and email. Passwords are securely stored using RSA encryption.
User Login: Existing users can log in by entering their username, password, and email.
Trip Management: Users can search for trips based on departure city, arrival city, and date.
Booking a Trip: After finding a suitable trip, users can book available seats.
Validation: The system ensures that all inputs are validated for format correctness, including username, password, email, date, price, and available seats.
RSA Encryption: Passwords are encrypted using RSA before being stored, adding an extra layer of security.
How to Use
Registration: When you first run the application, you'll be prompted to either log in or register. To register, select option 1 and enter your username, email, and password.
Login: If you're an existing user, select option 0 and enter your username, password, and email.
Find a Trip: After logging in, you'll be able to search for available trips. You can specify the departure city, arrival city, and departure date.
Book a Trip: If you find a trip that suits your needs, you can book the required number of seats.
Validation: The application ensures all input is correctly formatted, including checking that passwords only contain letters, emails follow the correct format, and dates are in dd/mm/yyyy format.