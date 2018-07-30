/*
 *	author: Andrey Suvorov
 *  purpose: create a chat system
 *  version: 5/12/2017
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) 
	{
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
	}
     
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
        
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
     
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
        
	int pid = -1;      
	while(pid!=0)
	{
	    listen(sockfd,5);
	    clilen = sizeof(cli_addr);
	    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	    if (newsockfd < 0) 
	        error("ERROR on accept");
	    pid = fork();
	    
	}
	while(1)
    {
	     bzero(buffer,256);
	     n = read(newsockfd,buffer,255);
	     if (n < 0) 
		 	error("ERROR reading from socket");
	     printf("Here is the message: %s",buffer);
	     
	    printf("Please enter the message\n: ");
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
	    n = write(newsockfd,buffer,strlen(buffer));
	    if (n < 0) 
			error("ERROR writing to socket");
	}
	return 0; 
}
