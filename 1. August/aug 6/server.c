/*Server code*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

char fun(char word[],int num){
int arr[26]={0};
 int i;
 for(i=0;word[i]!='\0';++i){
 char let=word[i];
 arr[let-'a']++;
 }
 int max=0,ind=0;
 for(i=0;i<26;++i){
 if(arr[i]>max) { max=arr[i]; ind=i; }
 
 if(max==num) return 'a'+ind;
 }
 return 'a'+ind;
}

int main()
{
int ssock,csock;
// creating server and client socket discriptor

unsigned int len;
struct sockaddr_in server,client;
// creating server & client socket object
if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
// creating socket
{
perror("socket: ");
exit(-1);
}
server.sin_family=AF_INET;
server.sin_port=htons(10000);
// initializing server socket parameters.
server.sin_addr.s_addr=INADDR_ANY;
bzero(&server.sin_zero,0);
// appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
len=sizeof(struct sockaddr_in);
if((bind(ssock,(struct sockaddr *)&server,len))==-1)
// binding port & IP
{
perror("bind error: ");
exit(-1);
}
if((listen(ssock,5))==-1)
// listening for client
{
perror("listen error: ");
exit(-1);
}
if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
// accepting connection
{
perror("accept error: ");
exit(-1);
}

char pass_correct[10]="qwerty";
char pass[10];
int resp=0;

while(1)
{
if(resp==0){
recv(csock,&pass,sizeof(pass),0);

if(strcmp(pass_correct,pass)==0) resp=1;

send(csock,&resp,sizeof(resp),0);
}

if(resp==1){
char word[30];
int num;
recv(csock,&word,sizeof(word),0);
recv(csock,&num,sizeof(num),0);

char ans=fun(word,num);
send(csock,&ans,sizeof(ans),0);
printf("\nsent ans=: %c\n",ans);
}

}
close(ssock);
}
