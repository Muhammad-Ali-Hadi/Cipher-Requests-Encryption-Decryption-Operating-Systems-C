#ifndef CIPHER_H_
#define CIPHER_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define int long long int

typedef struct{
    char* message;
    int size;
    bool cipherType; // False for Ceaser/True for RSA
    int shifts;
    int publicKey; // For RSA (e)
    int privateKey; // For RSA (d)
    int n; // For RSA (n)
}Data;

char* ceaserToMessage(char* message,int size,int shifts);

char* messageToCeaser(char* message,int size,int shifts);

int modularInverse(int publicKey,int phi);

int modularExponential(int message,int d,int n);

char* messageToRSA(char* message,int size,int key);

char* RSA_ToMessage(char* message,int size,int key,int n);

#endif