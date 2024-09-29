#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd) {
    int clientValue;
    int seq = 1;
    for (;;) {
        cout << "ENTER ACK FOR PACKET : "<<seq<<" : ";
        seq++;
        cin >> clientValue;
        if(clientValue == 0){
        	seq--;
        }
	//cout<<"b\n";
        // Send the integer value to the server
        write(sockfd, &clientValue, sizeof(clientValue));
	//cout<<"a\n";
        // If the client wants to exit, break the loop
        if (clientValue == 9) {
            cout << "Client Exit..." << endl;
            break;
        }
	//cout<<"c\n";
        // Clear buffer to receive server's response
        //int serverResponse;
      //  read(sockfd, &serverResponse, sizeof(serverResponse));
	//cout<<"an\n";
        // Print the response from the server
       // std::cout << "From Server : " << serverResponse << std::endl;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "socket creation failed..." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Socket successfully created.." << endl;
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        cerr << "connection with the server failed..." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "connected to the server.." << endl;
    }

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);

    return 0;
}

