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

char mean[100];
char word[100];
int check=0;

int comp(char word[],char mean[]){

int i=0,flag=0;
   
   while(word[i]!='\0' && mean[i]!='\0'){
    
    if(word[i]!=mean[i]) {
    flag=1;
    break;
    }
    
    ++i;
   }
   
   if(flag==0) return 1;
   else        return 0;

}

void fun(){
   FILE *fp;
   
   fp = fopen("dict.txt","r");
   
   check=0;
   //fscanf(fp,"%s",mean);
   while(1){
   
   if(feof(fp)!=0) break;
   
   fgets(mean,100,(FILE*)fp);
   if(check==1) break;
   
   check=comp(mean,word);
   
   }
   fclose(fp);

}

void add(){
  FILE *fp;
  
  fp = fopen("dict.txt","a");
  
  fprintf(fp,"%s\n",word);
  fprintf(fp,"%s\n",mean);
     
  fclose(fp);

  
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




while(1)
{
recv(csock,&word,sizeof(word),0);
fun();

send(csock,&check,sizeof(check),0);
if(check==0){
recv(csock,&mean,sizeof(mean),0);
add();
printf("word added\n");
}
if(check==1)
 send(csock,&mean,sizeof(mean),0);

printf("\nsent meaning :\n%s\n",mean);
}
close(ssock);
}
