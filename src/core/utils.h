#include <iostream>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
class Utils{
  public:
    static std::string removeCRLF(std::string);
    static std::vector<std::string> split(const std::string &s, char delim);
  private:
    template<typename Out>
      static void _split(const std::string &s, char delim, Out result);
};
