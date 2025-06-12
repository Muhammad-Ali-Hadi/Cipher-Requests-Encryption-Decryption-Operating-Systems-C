#include<unistd.h>
#include<math.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<fcntl.h>
#include"cipher.h"
#include"queue.h"

#define endl printf("\n")
#define int long long int
#define forn(x,n) for(int i=x;i<n;++i)

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

queue encryptionQueue;
queue decryptionQueue;

void *encryptMessage(void *arg)
{
    Data *data = (Data *)arg;
    char *encryptedMessage = NULL;

    encryptedMessage =(!data->cipherType) ? messageToCeaser(data->message, data->size, data->shifts) : messageToRSA(data->message, data->size, data->publicKey);
   
    pthread_mutex_lock(&lock);
    (!data->cipherType) ? printf("Ceaser Encrypted Message: %s of (%s)\n", encryptedMessage, data->message) : printf("RSA Encrypted Message: %s of (%s)\n", encryptedMessage, data->message);
    pthread_mutex_unlock(&lock);

    free(encryptedMessage);
    free(data->message);
    free(data);
    return NULL;
}

void *decryptMessage(void *arg)
{
    Data *data = (Data *)arg;
    char *decryptedMessage = NULL;

    decryptedMessage =(!data->cipherType) ? ceaserToMessage(data->message, data->size, data->shifts) : RSA_ToMessage(data->message, data->size, data->privateKey, data->n);

    pthread_mutex_lock(&lock);
    (!data->cipherType) ? printf("Ceaser Decrypted Message: %s of (%s)\n", decryptedMessage, data->message) : printf("RSA Decrypted Message: %s of (%s)\n", decryptedMessage, data->message);
    pthread_mutex_unlock(&lock);

    free(decryptedMessage);
    free(data->message);
    free(data);
    return NULL;
}

signed main()
{
    pthread_mutex_init(&lock,NULL);
    queueInit(&encryptionQueue);
    queueInit(&decryptionQueue);

    while (true)
    {
        printf("\n---Welcome To Cipher Conversion System---\n");
        printf("Enter (1) to Encrypt Message\n");
        printf("Enter (2) to Decrypt Cipher\n");
        printf("Enter (3) to Execute Added Requests\n");
        printf("Enter (0) to Exit\n");
        printf("------------------------------------------\n");

        char choice;
        scanf(" %c", &choice);
        getchar();

        if (choice == '0')
        {
            break;
        }
        
        if (choice == '1')
        { // Encryption
            char temp[1024];
            printf("Enter Text: ");
            fgets(temp, sizeof(temp), stdin);
            int len = strlen(temp);
            if (len > 0 && temp[len - 1] == '\n')
                temp[len - 1] = '\0';

            char *msg = strdup(temp);
            int size = strlen(msg);

            Data *data = (Data *)malloc(sizeof(Data));
            data->message = msg;
            data->size = size;
            printf("------------------------------------------\n");
            printf("Enter (1) for Ceaser Cipher Encryption\n");
            printf("Enter (2) for RSA Encryption\n");
            printf("------------------------------------------\n");
            char opt;
            scanf(" %c", &opt);
            getchar();

            if (opt == '1')
            {
                data->cipherType = false;
                printf("Enter Number of Shifts: ");
                scanf("%lld", &data->shifts);
                getchar();
                data->publicKey = data->privateKey = data->n = 0;
            }
            else if (opt == '2')
            {
                data->cipherType = true;
                data->publicKey = 17;
                data->privateKey = data->shifts = data->n = 0;
            }
            else
            {
                free(msg);
                free(data);
                printf("Invalid Cipher Type!\n");
                continue;
            }
            addRequest(&encryptionQueue,data);
        }
        else if (choice == '2')
        { // Decryption
            char temp[1024];
            printf("Enter Text: ");
            fgets(temp, sizeof(temp), stdin);
            int len = strlen(temp);
            if (len > 0 && temp[len - 1] == '\n')
                temp[len - 1] = '\0';

            char *msg = strdup(temp);
            int size = strlen(msg);
            Data *data = (Data *)malloc(sizeof(Data));
            data->message = msg;
            data->size = size;
            printf("------------------------------------------\n");
            printf("Enter (1) for Ceaser Cipher Decryption\n");
            printf("Enter (2) for RSA Decryption\n");
            printf("------------------------------------------\n");
            char opt;
            scanf(" %c", &opt);
            getchar();

            if (opt == '1')
            {
                data->cipherType = false;
                printf("Enter Number of Shifts: ");
                scanf("%lld", &data->shifts);
                getchar();
                data->publicKey = data->privateKey = 17;
                data->n = 999999;
            }
            else if (opt == '2')
            {
                data->cipherType = true;
                printf("Enter Private Key (d n): ");
                scanf("%lld %lld", &data->privateKey, &data->n);
                getchar();
                data->shifts = data->publicKey = 0;
            }
            else
            {
                free(msg);
                free(data);
                printf("Invalid Cipher Type!\n");
                continue;
            }
            addRequest(&decryptionQueue,data);
        }
        else if(choice=='3') // Parallel Execution of Each Request
        {
            if(empty(&encryptionQueue))
            {
                printf("No Requests for Encryption to Execute\n");
            }
            else
            {
                int executions=encryptionQueue.rear;
                pthread_t encrypt[executions];
                forn(0,executions)
                {
                    pthread_create(&encrypt[i],NULL,encryptMessage,returnRequest(&encryptionQueue));
                }
                printf("---Encryption Requests---\n");
                forn(0,executions)
                {
                    pthread_join(encrypt[i],NULL);
                }
                printf("--------------------------\n");
                queueInit(&encryptionQueue);
            }
            if(empty(&decryptionQueue))
            {
                printf("No Requests for Decryption to Execute\n");
            }
            else
            {
                int executions=decryptionQueue.rear;
                pthread_t decrypt[executions];
                forn(0,executions)
                {
                    pthread_create(&decrypt[i],NULL,decryptMessage,returnRequest(&decryptionQueue));
                }
                printf("---Decryption Requests---\n");
                forn(0,executions)
                {
                    pthread_join(decrypt[i],NULL);
                }
                printf("--------------------------\n");
                queueInit(&decryptionQueue);
            }
        }
        else
        {
            printf("Invalid Choice! Try Again\n");
        }
    }
    
    if(!empty(&encryptionQueue))
    {
        int executions=encryptionQueue.rear;
        pthread_t encrypt[executions];
        forn(0,executions)
        {
            pthread_create(&encrypt[i],NULL,encryptMessage,returnRequest(&encryptionQueue));
        }
        printf("---Encryption Requests---\n");
        forn(0,executions)
        {
            pthread_join(encrypt[i],NULL);
        }
        printf("--------------------------\n");
        queueInit(&encryptionQueue);
    }
    if(!empty(&decryptionQueue))
    {
        int executions=decryptionQueue.rear;
        pthread_t decrypt[executions];
        forn(0,executions)
        {
            pthread_create(&decrypt[i],NULL,decryptMessage,returnRequest(&decryptionQueue));
        }
        printf("---Decryption Requests---\n");
        forn(0,executions)
        {
            pthread_join(decrypt[i],NULL);
        }
        printf("--------------------------\n");
        queueInit(&decryptionQueue);
    }
    return 0;
}