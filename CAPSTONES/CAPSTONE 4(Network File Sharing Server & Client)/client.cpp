#include <iostream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    std::string filename;
    std::cout << "Enter filename to send: ";
    std::cin >> filename;

    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        std::cerr << "File not found!\n";
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // Change to server IP if needed

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, filename.c_str(), filename.length(), 0);
    usleep(500000);  // Short delay to ensure filename is processed

    // Send file content
    while (!infile.eof()) {
        infile.read(buffer, BUFFER_SIZE);
        send(sock, buffer, infile.gcount(), 0);
    }

    std::cout << "File sent.\n";
    infile.close();
    close(sock);
    return 0;
}

