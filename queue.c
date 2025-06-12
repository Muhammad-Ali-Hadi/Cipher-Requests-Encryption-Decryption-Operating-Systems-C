#include"queue.h"
#include"cipher.h"

void queueInit(queue* requests)
{
    requests->front=-1;
    requests->rear=0;
}

bool empty(queue* requests)
{
    return requests->front==-1 || requests->front==requests->rear;
}

bool full(queue* requests)
{
    return requests->rear==SIZE;
}

void addRequest(queue* requests,Data* request)
{
    if(full(requests))
    {
        printf("Requests Queue is Full\n");
        return;
    }
    if(requests->front==-1)
    requests->front++;

    requests->arr[requests->rear++]=*request;
    printf("Request Added Successfully\n");
}

Data* returnRequest(queue* requests)
{
    if(empty(requests))
    {
        printf("All Requests Executed Successfully\n");
        return NULL;
    }
    return (&requests->arr[requests->front++]);
}