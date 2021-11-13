#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int createTCPSocket();

int main()
{
    int sockfd, newsockfd;
    int clilen;
    char line[1000];
    int n;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = createTCPSocket();
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_port= htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("bind");
        close(sockfd);
        exit(1);
    }

    if(listen(sockfd, 5) < 0){
        perror("listen");
        close(sockfd);
        exit(1);
    }
    
    while(1)
    {
        clilen = sizeof(cliaddr);
        if((newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
            perror("accept");
            close(sockfd);
            exit(1);
        }
        
        switch(fork())
        {
        case -1:
            perror("fork");
            break;
            
        case 0:
            close(sockfd);
            while((n = read(newsockfd, line, 999)) > 0){
                /* Принятые данные отправляем обратно */
                if((n = write(newsockfd, line, strlen(line)+1)) < 0){
                    perror("write");
                    close(newsockfd);
                    exit(1);
                }
            }
            /* Если при чтении возникла ошибка – завершаем работу */
            if(n < 0){
                perror("write");
                close(newsockfd);
                exit(1);
            }

            close(newsockfd);
            exit(0);
            
        default:
            close(newsockfd);
        }
    }

    return 0;
}

int createTCPSocket(){
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(1);
    }
    return sockfd;
}