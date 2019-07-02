#include "ms.hh"
#include "db.hh"
#include <sys/socket.h>
#include <netinet/in.h>

using namespace server;

namespace server{

    movieServer::movieServer(){
        database::movieDatabase * movieDatabase = new database::movieDatabase();

        //Create a socket with the socket() system call
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd == -1) { //If successful, returns socket file descriptor, otherwise, returns -1
             printf("Error creating socket");
             exit(0);
        }

        // Bind the socket to an address using the bind() system call
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY; // any address
        addr.sin_port = htons(12345);
        if (bind(fd, (struct sockaddr *)&addr, sizeof(addr))<0) { //should return 0 if successful
             printf("Error binding socket");
            exit(0);
        }
        if(listen(fd) < 0) { //Listen for a connection
            printf("Error listening for connections");
            exit(0);
        }
        int client_fd = accept(fd, (struct sockaddr *)&client_addr,
        (socklen_t*)&addrlen);
        if(client_fd < 0) {
        printf("Error accepting connection");
        exit(0);
        }

    }
    movieServer::~movieServer(){}

    int movieServer::listen (int fd){
        int backlog=1;


        return 0; // successful;
    }

}