#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>

bool checkString(const std::string& str) {
    return (str.length() > 2 && str.length() % 32 == 0);
}

void handleClient(int client_socket) {
    char buffer[1024];

    while (true) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                std::cout << "Client disconnected" << std::endl;
            } else {
                std::cerr << "Error receiving data" << std::endl;
            }
            break;  // Выход из цикла, если клиент отключился или произошла ошибка
        }

        buffer[bytes_received] = '\0';  // Завершаем строку
        std::cout << "Received: " << buffer << std::endl;

        std::string received_data(buffer);

        // Вызов функции checkString
        if (checkString(received_data)) {
            std::cout << "String is valid!" << std::endl;
            send(client_socket, "Valid string", 12, 0);
        } else {
            std::cout << "String is invalid!" << std::endl;
            send(client_socket, "Invalid string", 14, 0);
        }
    }

    close(client_socket);  // Закрытие сокета клиента
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "Listen failed" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port 12345..." << std::endl;

    while (true) {  // Бесконечный цикл для обработки новых подключений
        sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == -1) {
            std::cerr << "Accept failed" << std::endl;
            continue;  // Пытаемся принять следующее подключение
        }

        std::cout << "Client connected" << std::endl;

        // Обработка клиента
        handleClient(client_socket);
    }

    close(server_socket);  // Закрытие серверного сокета (не достижимо, так как сервер работает в бесконечном цикле)
    return 0;
}
