


#include "client.hpp"
#include <thread>
// /////////////////////////////////////////


// /////////////////////////////////////////
addrinfo* getServerAddrinfo(const char*);
socket_fd initClientSocket(addrinfo* );
int sendMessage(socket_fd, addrinfo* ,const char*);
int recvMessage(socket_fd);
void messageCycle(socket_fd, addrinfo*);


int main() {

    addrinfo* serverAddrinfo = getServerAddrinfo("127.0.0.1");
    socket_fd clientfd = initClientSocket(serverAddrinfo);
    
    thread messageCycleThread(messageCycle, clientfd, serverAddrinfo);
    // messageCycle(clientfd, serverAddrinfo);
    messageCycleThread.join();
    freeaddrinfo(serverAddrinfo);
    close(clientfd);

    return 0;

}


socket_fd initClientSocket(addrinfo* serverAddrinfo) {
    socket_fd sockfd;
    sockfd = socket(serverAddrinfo->ai_family, serverAddrinfo->ai_socktype, serverAddrinfo->ai_protocol);

    return sockfd;
}

addrinfo* getServerAddrinfo(const char* address) {
    addrinfo hints, *serverAddrinfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; 
    getaddrinfo(address, PORTSERVER, &hints, &serverAddrinfo);

    return serverAddrinfo;
}

void messageCycle(socket_fd sockfd, addrinfo* serverAddrinfo) {
    fd_set readfds;
    while(true) {
    sendMessage(sockfd, serverAddrinfo, "Hello");
    recvMessage(sockfd);    
    }
}

int sendMessage(socket_fd sockfd, addrinfo* serverAddrinfo, const char* message) {
    int sentBytes;

    sentBytes = sendto(sockfd, message, strlen(message), 0, serverAddrinfo->ai_addr, serverAddrinfo->ai_addrlen);
    return sentBytes;
}


int recvMessage(socket_fd sockfd) {
    sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    char bufferMessage[1024];
    int recvBytes;
    recvBytes = recvfrom(sockfd, bufferMessage, 1024, 0, (sockaddr*)&addr, &addrlen);
    bufferMessage[recvBytes] = '\0';
    cout << recvBytes << endl;
    cout << bufferMessage << endl;

    return recvBytes;
}


