#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/stat.h>




const char *  writing_to_file (double a, std::string &b , std::string &c){
    const char * filename = "transaction_test.txt";
    std::ofstream out (filename);
    if( out.is_open()){
        out << a << " " << b << " " << c << " " ;
    }
    else {
        std::cerr << "File cannot open"<< std::endl;
    }
    out.close();
    return filename;
}


int main() {

    int port = 50632;
    std::string ipAddress = "127.0.0.1";

    double amount;
    std::string sender;
    std::string recipient;

    amount = 4;
    sender = "sasha";
    recipient = "masha";

    const char * filename_trans = writing_to_file( amount, sender, recipient);




    int sock = socket(AF_INET, SOCK_STREAM, 0); // создание сокета
    if (sock == -1) {
        std::cerr<< "creation socket failed" <<std::endl;
        return 0;
    }

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &sin.sin_addr);

    //коннектимся с айпишником
    int connectRes = connect(sock, (sockaddr*)&sin, sizeof(sin));
    if (connectRes == -1)
    {
        std::cerr<< "connection failed" <<std::endl;
        return 0;
    }
    else {
        std::cout << "connection to port : "<< port << std::endl;
    }

    if(!fork()) {
        char sdbuf[512];
        std::cout<<"sending to the server"<<std::endl;
        FILE *fs = fopen(filename_trans, "r");
        bzero(sdbuf, 512);
        int fs_block_sz;
        while ((fs_block_sz = fread(sdbuf, sizeof(char), 512, fs)) > 0) {
            if ( send(sock, sdbuf, fs_block_sz, 0) < 0) {
                std::cout<< "failed to dens file" << std::endl;
                break;
            }
            bzero(sdbuf, 512);
        }
        fclose ( fs);
        std::cout<< "was sent " << std::endl;
    }
    close(sock);

}
