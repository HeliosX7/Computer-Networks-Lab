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

int check=0;
char val[100];

int cl,el;
int id;
int conv(char a[]){
int sum=0;
int i;
for(i=0;a[i]!='\0';++i) sum=sum*10 + (a[i]-'0');

return sum;
}

char* convs(int n){
   int rev=0;
   while(n>0){
   rev=rev*10 + n%10;
   n/=10;
   }
   int k=0;
   while(rev>0){
   val[k++]= (rev%10)+'0';
   rev/=10;
   }
   val[k]='\0';
   return val;
}

void find(){
   FILE *fp;
   
   fp = fopen("dict.txt","r");
   
   check=0;
   
   char word[100];
   //fscanf(fp,"%s",mean);
   while(1){
   
   if(feof(fp)!=0) break;
   
   fscanf(fp,"%s",word);
   
   printf("\n%d",conv(word));
   
   if(check==1){ 
   cl=conv(word);
   fscanf(fp,"%s",word);
   el=conv(word);
   break;
   }
   int idc=conv(word);
   
   check= (id==idc)? 1:0;
   
   }
   fclose(fp);

}

void update(){
  FILE *fp;
  
  fp = fopen("dict.txt","r+w");
  
//  fprintf(fp,"%s\n",word);
  
   char word[100];
   int c=0;
   while(1){
   
   if(feof(fp)!=0) break;
   
   if(c==1){ 
   fprintf(fp,"%s\n",convs(cl));
   fprintf(fp,"%s\n",convs(el));
   break;
   }
   
   fscanf(fp,"%s",word);
   
   if(c==1){ 
   fprintf(fp,"%s\n",convs(cl));
   fprintf(fp,"%s\n",convs(el));
   break;
   }
   
   printf("\n%d",conv(word));
   
   
   int idc=conv(word);
   
   c = (id==idc)? 1:0;
   
   }
     
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
recv(csock,&id,sizeof(id),0);

find(id);

send(csock,&check,sizeof(check),0);



 if(check==1){
  printf("Found!");  
  send(csock,&cl,sizeof(el),0);
  send(csock,&el,sizeof(el),0);
 
  recv(csock,&cl,sizeof(cl),0);
  recv(csock,&el,sizeof(el),0);
  
  update();
  printf("\nLeave updated ! :\n");
 }

close(ssock);
}
}
