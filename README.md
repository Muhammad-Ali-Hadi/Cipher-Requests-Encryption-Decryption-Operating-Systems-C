# Cipher-Requests-Encryption-Decryption-Operating-Systems-C
Cipher Encryption-Decryption System
This project implements a multi-request cipher encryption-decryption system in C, designed to efficiently handle multiple user requests using queues and multithreading.

🚀 Features:
Accepts up to 4 encryption and 4 decryption requests at a time.

Supports two encryption algorithms:
Caesar Cipher
RSA Encryption
Users can choose:
To enqueue new requests (encryption or decryption).
To execute all current requests in parallel (using threads).
To exit, in which case the system checks if any pending requests remain and executes them automatically before exiting.
Request management is handled using separate queues for encryption and decryption.

🛠 Technologies Used:
C Programming
Multithreading (POSIX Threads)
Queues (Custom implementation)
Modular Arithmetic for RSA

📋 How It Works
The user is presented with a menu to:
Add an encryption request (RSA or Caesar).
Add a decryption request (RSA or Caesar).
Execute all queued requests concurrently.
Exit the program.
If execute is chosen, all encryption and decryption requests are processed using threads.
If exit is chosen, the system:
Checks both request queues.
Executes any remaining requests.
Then terminates safely

📁 Project Structure
cipher-system/
├── main.c             # Entry point, handles user input and manages the whole program
├── queue.c/h          # Queue implementation for request handling
├── cipher.c/h         # Caesar and RSA cipher Encryption/Decryption logic
└── README.md          # You're here!

🧠 Learning Goals
Efficient request management using queues.

Implementation of basic cryptographic techniques.

Use of multithreading to improve performance and parallelism.

Practice in modular code design and inter-process coordination.

Usage:
gcc -g -pthread main.c queue.c cipher.c -o main
./main

Follow the on-screen prompts to:
Add requests
Execute them
Or quit safely
