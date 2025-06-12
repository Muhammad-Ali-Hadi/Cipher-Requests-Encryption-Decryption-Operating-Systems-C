# Cipher-Requests-Encryption-Decryption-Operating-Systems-C
_This project implements a multi-request cipher encryption-decryption system in C, designed to efficiently handle multiple user requests using queues and multithreading._  

**🚀 Features:**  
_Accepts up to 4 encryption and 4 decryption requests at a time._  

**Flow of Execution:**  
https://www.canva.com/design/DAGlLK8CKMU/A0sX1gWhyKQ8kM99RvW1ZA/view?utm_content=DAGlLK8CKMU&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=hbbdc1aeddc  
  
**Supports two encryption algorithms:**  
_Caesar Cipher  
RSA Encryption_  

**Users can choose:**  
_To enqueue new requests (encryption or decryption).  
To execute all current requests in parallel (using threads).  
To exit, in which case the system checks if any pending requests remain and executes them automatically before exiting.  
Request management is handled using separate queues for encryption and decryption._  
  
**🛠 Technologies Used:**  
_C Programming  
Multithreading (POSIX Threads)  
Queues (Custom implementation)  
Modular Arithmetic for RSA_  
  
**📋 How It Works:**  
_The user is presented with a menu to:  
Add an encryption request (RSA or Caesar).  
Add a decryption request (RSA or Caesar).  
Execute all queued requests concurrently.  
Exit the program.  
If execute is chosen, all encryption and decryption requests are processed using threads.  
If exit is chosen, the system:  
Checks both request queues.  
Executes any remaining requests.  
Then terminates safely_  
  
**📁 Project Structure**  
cipher-system/  
├── main.c             _# Entry point, handles user input and manages the whole program_  
├── queue.c/h          _# Queue implementation for request handling_  
├── cipher.c/h         _# Caesar and RSA cipher Encryption/Decryption logic_  
└── README.md          _# You're here!_  
  
**🧠 Learning Goals**  
_Efficient request management using queues.  
Implementation of basic cryptographic techniques.  
Use of multithreading to improve performance and parallelism.  
Practice in modular code design and inter-process coordination._  
  
**Usage:**  
_gcc -g -pthread main.c queue.c cipher.c -o main  
./main_  
  
**Follow the on-screen prompts to:**  
_Add requests  
Execute them  
Or quit safely_  
