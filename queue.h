#ifndef QUEUE_H_
#define QUEUE_H_

#include"cipher.h"

#define int long long int
#define SIZE 4

typedef struct{
    Data arr[SIZE];
    int front;
    int rear;
}queue;

void queueInit(queue* requests);

void addRequest(queue* requests,Data* request);

bool empty(queue* requests);

bool full(queue* requests);

Data* returnRequest(queue* requests);

#endif