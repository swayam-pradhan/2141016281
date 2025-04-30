#include <iostream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept from any IP
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    std::cout << "Waiting for connection on port " << PORT << "...\n";

    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    std::cout << "Client connected.\n";

    // Receive filename
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    std::string filename(buffer);
    std::ofstream outfile("received_" + filename, std::ios::binary);

    // Receive file content
    int bytes_received;
    while ((bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        outfile.write(buffer, bytes_received);
    }

    std::cout << "File received and saved as: received_" << filename << "\n";
    outfile.close();
    close(new_socket);
    close(server_fd);
    return 0;
}

