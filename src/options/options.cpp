#include <iostream>
#include <boost/program_options.hpp>
#include <exception>
#include "options.h"

using namespace std;
using namespace boost::program_options;

Options::Options(void){
  this->options = new options_description("Allowed Options");
}
bool Options::init(int ac, char** av, vector<Option> _options){
  // Declare the supported options.

  this->options->add_options()("h", "produce help message");

  for (Option o: _options) {
    std::string n = o.name + "," + o.key;
    if(o.default_value != ""){
      this->options->add_options()(n.c_str(),value<std::string>()->default_value(o.default_value),o.description.c_str());
    }else{
      this->options->add_options()(n.c_str(),o.description.c_str());
    }
  }

  //("index,i",value<int>()->default_value(0), "functional value");

  try {
    store(parse_command_line(ac, av, *this->options), vm);
    notify(this->vm);    
  } catch(exception& e){
    cerr << "Error:" << e.what() << endl;
    return false;
  }

  if (this->vm.count("h")) {
    cout << *this->options << "\n";
    return false;
  }
  return true;
}

bool Options::hasValue(string name){
  return (this->vm.count(name));
}

template<typename T>
T Options::getValue(string name,T default_value){
  if (this->hasValue(name)) {
    return this->vm[name].as<T>();
  } else {
    return default_value;
  }
}

string Options::getStringValue(string name){
  return this->getValue<string>(name,"not set");
}

int Options::getIntValue(string name){
  return this->getValue<int>(name,1);
}
