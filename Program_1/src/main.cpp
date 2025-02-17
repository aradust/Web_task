#include "worker.hpp"
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

std::mutex mtx;
std::condition_variable cv;
std::queue<std::string> buffer;
bool data_ready = false;

void inputThread() {
    while (true) {
        std::cout << "Введите строку: ";
        std::string input;
        std::cin >> input;
        handleInput(input);
        {
            std::lock_guard<std::mutex> lock(mtx);
            buffer.push(input);
            data_ready = true;
        }
        cv.notify_one();
    }
}

void outputThread() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return data_ready; });
        std::string data = buffer.front();
        buffer.pop();
        data_ready = false;
        lock.unlock();
        std::cout << "Processed: " << data << std::endl;

        // Отправляем данные серверу и выводим ответ от сервера
        std::string server_response = sendDataToServer(data);
        std::cout << "Server response: " << server_response << std::endl;
    }
}

std::string sendDataToServer(const std::string& data) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return "";
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  // Порт сервера
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP-адрес сервера (локальный)

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(sock);
        return "";
    }

    if (send(sock, data.c_str(), data.size(), 0) == -1) {
        std::cerr << "Error sending data" << std::endl;
        close(sock);
        return "";
    }

    char buffer[1024];
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';  // Завершаем строку
        std::string response(buffer);
        close(sock);
        return response;
    } else {
        std::cerr << "Error receiving data from server" << std::endl;
        close(sock);
        return "";
    }
}

int main() {
    std::thread t1(inputThread);
    std::thread t2(outputThread);
    t1.join();
    t2.join();
    return 0;
}
