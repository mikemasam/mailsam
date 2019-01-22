#include "utils.h"

std::string Utils::removeCRLF(std::string input){
  std::string output;
  output.reserve(input.length());

  std::copy_if(input.begin(), input.end(),std::back_inserter(output),
      [] (char c) {
      return c != '\r' && c != '\n'; 
      });
  return output;
}

template<typename Out>
void Utils::_split(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> Utils::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  _split(s, delim, std::back_inserter(elems));
  return elems;
}
