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
int i;
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

char pass[10];
int resp=0;
while(1)
{
if(resp==0){
printf("Enter password:\n");
scanf("%s",pass);
send(sock,&pass,sizeof(pass),0);
// sending data back to client.

recv(sock,&resp,sizeof(resp),0);
// receiving data from client
if(resp==1) printf("\nCorrect!");
else        printf("\nIncorrect!");
}

if(resp==1){
char word[30];
int num;
printf("\nEnter word:");
scanf("%s",word);
printf("\nEnter number:");
scanf("%d",&num);

send(sock,&word,sizeof(word),0);
send(sock,&num,sizeof(num),0);

char ans;

recv(sock,&ans,sizeof(ans),0);

printf("\nrequired char =%c",ans);

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
