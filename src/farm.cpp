#include <string>

#include "ansi_clear.hpp"

std::string hello() {
   return "Hello World!";
}

void spaces_and_dot(int number_of_spaces, std::string symbol) {
  ansi_clear();
  std::string input;
  for(int i = 0; i < number_of_spaces; i++) {
    std::cout << " ";
  }
  std::cout << symbol << std::endl;
  std::cout << "Press Enter" << std::endl;
  std::getline(std::cin, input);
}

void zoom(std::string symbol) {
  for(int i = 40; i > 0; i--) {
    spaces_and_dot(i, symbol);
  }
}
