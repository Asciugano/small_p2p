#pragma once
#include <string>
#include <vector>

struct Peer {
  std::string ip;
  int port;
};

struct Node {
  int id;
  std::vector<Peer> peers;
};

class Mess {
public:
  std::string type, from, to, content;

  Mess(std::string type, std::string from, std::string to, std::string content);

  void invia(Mess mess);
  void ricevi(Mess mess);

  std::string to_s(Mess mess);
};
