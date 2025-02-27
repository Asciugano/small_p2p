#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <ostream>
#include <thread>
#include <unistd.h>

int PORT = 5001;

void handleClient(int clientSocket) {
  char buffer[1024] = {0};
  int bytesRead = read(clientSocket, buffer, sizeof(buffer));
  if (bytesRead > 0) {
    std::cout << "Messaggio ricevuto: " << buffer << std::endl;

    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: "
                           "text/plain\r\n\r\nMessaggio ricevuto\n";
    send(clientSocket, response.c_str(), response.size(), 0);
  } else {
    std::cerr << "Errore nella lettura del messaggio dal client." << std::endl;
  }
  close(clientSocket);
}

void startServer() {
  int server_fd, clientSocket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cerr << "Errore nella creazione del socket" << std::endl;
    return;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Errore nel binding della porta " << PORT << std::endl;
    close(server_fd);
    return;
  }

  if (listen(server_fd, 5) < 0) {
    std::cerr << "Errore nell'ascolto sulla porta " << PORT << std::endl;
    close(server_fd);
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

  close(server_fd); // Chiusura del socket del server
}

int main() {
  std::cout << "Inserire la porta: ";
  std::cin >> PORT;

  if (PORT < 1024 || PORT > 65535) {
    std::cerr
        << "Numero di porta non valido. Utilizzare un numero tra 1024 e 65535."
        << std::endl;
    return 1;
  }

  std::cout << "Nodo P2P avviato sulla porta " << PORT << std::endl;
  std::thread serverThread(startServer);
  serverThread.join();
  return 0;
}
