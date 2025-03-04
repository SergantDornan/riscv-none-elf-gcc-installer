#ifndef ALIAS
#define ALIAS

#include "BuilderFilework.h"
const std::vector<std::string> configFiles = {getHomedir() + "/.bashrc", 
	getHomedir() + "/.zshrc", getHomedir() + "/.config/fish/config.fish"};
std::string findConfig();
std::string getLine(const std::string&, const std::string&);
void addPath(const std::string&);
void removePath(const std::string&);


#endif