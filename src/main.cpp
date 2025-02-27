#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <ostream>
#include <thread>
#include <unistd.h>

int PORT = 5001;

void handleClient(int clientSocket) {
  char buffer[1024] = {0};
  read(clientSocket, buffer, 1024);
  std::cout << "Messaggio ricevuto: " << buffer << std::endl;
  close(clientSocket);
}

void startServer() {
  int server_fd, clientSocket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Errore nel binding della porta" << std::endl;
    return;
  }
  if (listen(server_fd, 5) < 0) {
    std::cerr << "Errore nell'ascolto sulla porta" << std::endl;
    return;
  }

  std::cout << "Server in ascolto sulla porta " << PORT << std::endl;

  while (true) {
    clientSocket =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (clientSocket < 0) {
      std::cerr << "Errore nell'accettazione della connessione" << std::endl;
      continue;
    }

    std::thread([](int socket) { handleClient(socket); },
                std::move(clientSocket))
        .detach();
  }
}

int main() {
  std::cout << "inserire la porta:" << std::endl;
  std::cin >> PORT;
  std::cout << "Nodo P2P avviato sulla porta " << PORT << std::endl;
  std::thread serverThread(startServer);
  serverThread.join();
  return 0;
}
