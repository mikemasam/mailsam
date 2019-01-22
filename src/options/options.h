#pragma once
#include <string>
#include <boost/program_options.hpp>
using namespace std;
using namespace boost::program_options;
class Options {
  public:
    struct Option {
      std::string name;
      std::string key;
      std::string default_value;
      std::string description;
    };

    Options();
    bool init(int ac, char** av,vector<Option>);
    bool hasValue(string name);
    string getStringValue(string name);
    int getIntValue(string name);

  private:
    options_description *options;
    variables_map vm;
    template<typename T>
      T getValue(string name,T default_value);
};
