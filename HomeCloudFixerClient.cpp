#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <algorithm>

    std::string command;
    sf::TcpSocket socket_s;

bool receive() {

    bool status;
    sf::Packet packet;
    std::string content;

    socket_s.receive(packet);
    packet >> content;
    packet.clear();

    std::cout << content << std::endl;
    return status;
} 

bool send(std::string komend) {

    bool status;
    sf::Packet packet;

    packet << komend;
    socket_s.send(packet);
    packet.clear();

    return status;
}

int main() {
    
    std::cout << "Ratunek TCP\n"
    "Program służy do ratowania serwera gdy nie można się z nim połączyć.\n"
    "Stworzone przez Mateusza Sytę.\n"
    << std::endl;

    Sleep(500);
    system("cls");

    std::cout << "Ratunek TCP\n"
    "Napisz 'START' by zacząć połączenie.\n" << std::endl;

    std::string inputstart;
    getline(std::cin, inputstart);
    transform(inputstart.begin(), inputstart.end(), inputstart.begin(), ::tolower);

    if(inputstart == "start") {

        socket_s.setBlocking(true);
        inputstart.clear();
        unsigned int port = 50153;
        std::string inputip;

        std::cout << "Wpisz adres IP serwera: \n";
        getline(std::cin, inputip);
        
        if(socket_s.connect(inputip, port) == sf::Socket::Done) {
            
            std::cout << "Połączono.\n";

            for(;;) {
                getline(std::cin, command);

                if(command == "exit") {
                    send("exit");
                    break;
                }

                send(command);
                receive();
                
            }
            socket_s.disconnect();
        }
    }
}
