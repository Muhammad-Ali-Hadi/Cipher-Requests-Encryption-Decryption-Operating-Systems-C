#include"cipher.h"

#define int long long int

char* ceaserToMessage(char* message,int size,int shifts)
{
    shifts%=26;
    char* decryptedMessage=(char*)malloc((size+1)*sizeof(char));
    for(int i=0;i<size;++i)
    {
        if(message[i]>='A' && message[i]<='Z')
        {
            decryptedMessage[i]=((message[i]-'A'-shifts+26)%26)+'A';
        }
        else if(message[i]>='a' && message[i]<='z')
        {
            decryptedMessage[i]=((message[i]-'a'-shifts+26)%26)+'a';
        }
        else
        {
            decryptedMessage[i]=message[i];
        }
    }
    decryptedMessage[size]='\0';
    return decryptedMessage;
}

char* messageToCeaser(char* message,int size,int shifts)
{
    char* encryptedMessage=(char*)malloc((size+1)*sizeof(char));
    shifts%=26;
    for(int i=0;i<size;++i)
    {
        if(message[i]>='A' && message[i]<='Z')
        {
            encryptedMessage[i]=((message[i]-'A'+shifts)%26)+'A';
        }
        else if(message[i]>='a' && message[i]<='z')
        {
            encryptedMessage[i]=((message[i]-'a'+shifts)%26)+'a';
        }
        else
        {
            encryptedMessage[i]=message[i];
        }
    }

    encryptedMessage[size]='\0';
    return encryptedMessage;
}

int modularInverse(int publicKey,int phi)
{
    for(int i=2;i<phi;++i)
    {
        if((publicKey*i)%phi==1)
        {
            return i;
        }
    }
    return -1;
}

int modularExponential(int message,int d,int n)
{
    int result=1;
    message%=n;
    while(d>0)
    {
        if(d&1)
        {
            result=(result*message)%n;
        }
        message=(message*message)%n;
        d>>=1;
    }
    return result;
}

char* messageToRSA(char* message,int size,int key)
{
    int p=53,q=61;
    // int p=2,q=7;
    int n=p*q;

    int phi=(p-1)*(q-1);

    int d=modularInverse(key,phi);
    char* encryptedMessage=(char*)malloc((size)*10*sizeof(char));
    encryptedMessage[0]='\0';

    char buffer[20];

    printf("Private Key (d,n)=>(%lld,%lld)\n",d,n);

    for(int i=0;message[i]!='\0';++i)
    {
        int encryptedChar=modularExponential((unsigned char)message[i],key,n);
        sprintf(buffer,"%lld ",encryptedChar);
        strcat(encryptedMessage,buffer);
    }
    return encryptedMessage;
}

char* RSA_ToMessage(char* message,int size,int key,int n)
{
    char* messageCopy=strdup(message);
    char* decryptedMessage=(char*)malloc((size+1)*sizeof(char));
    int num,index=0;

    char* token=strtok(messageCopy," ");
    while(token!=NULL)
    {
        num=atoi(token);
        decryptedMessage[index++]=(char)modularExponential(num,key,n);
        token=strtok(NULL," ");
    }
    decryptedMessage[index]='\0';
    return decryptedMessage;
}