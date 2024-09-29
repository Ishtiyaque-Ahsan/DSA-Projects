#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib> // For atoi
#include <sys/select.h> // For select() system call
using namespace std;

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd, int W) 
{
    int clientValue;
    int p = 1;
    
    // Infinite loop for chat
    for (;;) {
        // Prepare for select timeout
        struct timeval tv;
        fd_set readfds;

        // Timeout setup (5 seconds)
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        for (int i = 0; i < W; i++) {
            cout << "SND PKT " << p + i << endl;
        }

        p += W;
        for (int i = 0; i < W; i++) {
            FD_ZERO(&readfds);           // clear the set
            FD_SET(connfd, &readfds);    // add descriptor to set

            // Wait for an acknowledgement or timeout
            int activity = select(connfd + 1, &readfds, NULL, NULL, &tv);

            if (activity == 0) {
                // Timeout occurred, no data received
                cout<<"TIMER ENDED"<<endl;
                cout << "NO ACK RECIEVED, RESENDING " << p - W + i << endl;
                p = p - (W - i);
                break;
            } else if (activity > 0) {
                if (FD_ISSET(connfd, &readfds)) {
                    // Data is ready to be read
                    read(connfd, &clientValue, sizeof(clientValue));
                    int temp = p - W;
                    cout << "For packet... " << temp + i << ", ACK RECEIVED" << clientValue << endl;
                    
                    if (clientValue == 0) {
                        cout << "ACK IS CORRUPTED FOR PACKET " << p - W + i << endl;
                        p = p - (W - i);
                        break;
                    }
                    if (clientValue == 1) {
                        continue;
                    }
                }
            } else {
                // Select error
                cerr << "Select sys call error." << endl;
                break;
            }

            // If client message was "9" then server exits and chat ends
            if (clientValue == 9) {
                cout << "Server closes..." << endl;
                break;
            }
        }
    }
}

// Driver function
int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // Socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout << "Socket creation failed..." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Socket successfully created.." << endl;
    }
    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        cout << "Socket bind failed..." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Socket successfully binded.." << endl;
    }

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        cout << "Listen failed..." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Server listening.." << endl;
    }

    socklen_t len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        cout << "Server accept failed..." << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Server accept the client..." << endl;
    }
    int win;
    cout << "Enter the window size: " << endl;
    cin >> win;
    
    // Function for chatting between client and server
    func(connfd, win);

    // After chatting close the socket
    close(sockfd);
    return 0;
}


