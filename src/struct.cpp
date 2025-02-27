#include "struct.h"

Mess::Mess(std::string type, std::string from, std::string to,
           std::string content) {
  this->type = type;
  this->from = from;
  this->to = to;
  this->content = content;
}

std::string Mess::to_s(Mess mess) {
  return type + ": " + from + " -> " + to + "\n" + content + "\b";
}
