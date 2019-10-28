/*Client code*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
int sock;
// client socket discriptor

unsigned int len;
char ch2[3]="no";
char ch1[3];
struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
// client socket is created.
{
perror("socket: ");
exit(-1);
}
client.sin_family=AF_INET;
client.sin_port=htons(10000);
// initializing socket parameters
client.sin_addr.s_addr=INADDR_ANY;
bzero(&client.sin_zero,0);
// appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1)
//connecting to client
{
perror("connect: ");
exit(-1);
}

int i;
int id;


FILE *fp;
char ch;

fp=fopen("abc.txt","r");
int flag=1;
send(sock,&flag,sizeof(flag),0);

while(1){
    ch=fgetc(fp);
    
    if(ch==EOF){ 
    flag=0;
    send(sock,&flag,sizeof(flag),0);
    break; 
    }
    
    send(sock,&flag,sizeof(flag),0);

    send(sock,&ch,sizeof(ch),0);
 }

printf("\nfile transfer successful.........\n");


}
