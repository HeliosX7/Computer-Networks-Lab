#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main()
{
int server_socket;
server_socket=socket(AF_INET,SOCK_STREAM,0);

//define server address

struct sockaddr_in server_address;

server_address.sin_family=AF_INET;
server_address.sin_port=htons(10000);
server_address.sin_addr.s_addr=INADDR_ANY;

// binding IP and Port

bind(server_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));

//listening for connection

listen(server_socket,10);


//accpting a connection
int client_socket;
client_socket=accept(server_socket,NULL,NULL); //connect(socket,address of the connecting socket,length of address)

//receiving data from client

char buffer[255];
int ch=0;

FILE *fp;
fp=fopen("abc.txt","w");

int w;

read(client_socket,&w,sizeof(int));

while(ch!=w)
{
read(client_socket,buffer,255);
fprintf(fp,"%s ",buffer);
ch++;
}

printf("\nfile receive successful............\n");

//closing connection
close(server_socket);
return 0;
}
