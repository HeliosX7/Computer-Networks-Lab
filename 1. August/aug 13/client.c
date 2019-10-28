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
char ch[3]="no";
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
char word[100];

while(1)
{
printf("enter word:\n");
scanf("%s",word);
send(sock,&word,sizeof(word),0);
// sending data back to client.

char mean[100];
int check;
recv(sock,&check,sizeof(check),0);
if(check==0){
printf("Word not found! please enter the meaning!:");
scanf("%s",mean);
send(sock,&mean,sizeof(mean),0);
printf("Word added!\n");
}
else{
recv(sock,&mean,sizeof(mean),0);
// receiving data from client
printf("Meaning :\n%s\n",mean);
}

printf("\nTo exit...press 'no'\n");
scanf("%s",ch1);

if((i=strcmp(ch,ch1))==0)
{
close(sock);
exit(0);
}
}
}
