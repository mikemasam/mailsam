#include <iostream>
#include <boost/program_options.hpp>
#include <exception>
#include "options.h"

using namespace std;
using namespace boost::program_options;

Options::Options(void){
  this->options = new options_description("Allowed Options");
}
bool Options::init(int ac, char** av){
  // Declare the supported options.
  this->options->add_options()
    ("h", "produce help message")
    ("value,v",value<string>()->default_value(""), "functional value")
    ("index,i",value<int>()->default_value(0), "functional value");

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
