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
int id;

while(1)
{
printf("\nEnter employee ID : ");
scanf("%d",&id);
send(sock,&id,sizeof(id),0);
// sending data back to client.

int cl,el;

int check;
recv(sock,&check,sizeof(check),0);

if(check==0){
printf("ID not found! please enter the correct ID!:");
}
else{

recv(sock,&cl,sizeof(cl),0);
recv(sock,&el,sizeof(el),0);
printf("Current Balance(Days left) : \n1.CL = %d\n2.EL =%d\n",cl,el);

printf("Press 1 for CL and 2 for EL : ");
int opt;
scanf("%d",&opt);

switch(opt){
          case 1: {
                   printf("Enter the no. days you want leave for : ");
                   int days;
                   scanf("%d",&days);
                   if(cl-days<0) {
                   printf("Requested leave cannot be granted !");
                  
                   }
                   else{
                   cl-=days;
                   printf("Requested leave granted!");
                   }
                   break;
          }
          case 2: {
          printf("Enter the no. days you want leave for : ");
          int days;
	   	  scanf("%d",&days);
                   if(el-days<0) {
                   printf("Requested leave cannot be granted !");
                   }
                   else{
                   el-=days;
                   printf("Requested leave granted!");
                   }
                   break;
          }
          default : printf("Enter valid option !");
}

send(sock,&cl,sizeof(cl),0);
send(sock,&el,sizeof(el),0);
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
