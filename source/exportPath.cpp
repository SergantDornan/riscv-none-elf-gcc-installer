#include "exportPath.h"
std::vector<std::string> findConfig(){
	std::vector<std::string> v;
	for(int i = 0; i < configFiles.size(); ++i){
		if(exists(configFiles[i]))
			v.push_back(configFiles[i]);
	}
	return v;
}
std::string getLine(const std::string& config, const std::string& path){
	std::string name = getName(config);
	if(name == ".bashrc" || name == ".zshrc")
		return "export PATH=\"" + path + ":$PATH\"";
	else if(name == "config.fish")
		return "set -U fish_user_paths " + path + " $fish_user_paths";
	return "-1";
}
void addPath(const std::string& path){
	std::vector<std::string> config = findConfig();
	if(config.size() == 0){
		std::cout << "======================= ERROR =======================" << std::endl;
		std::cout << "exportPath.cpp: addPath: cannot find config file " << std::endl;
		std::cout << "probably does not work for your system" << std::endl;
		std::cout << "cannot add exportPath" << std::endl;
		return;
	}
	for(int i = 0; i < config.size(); ++i){
		std::string line = getLine(config[i], path);
		if(line == "-1"){
			std::cout << "======================= ERROR =======================" << std::endl;
			std::cout << "exportPath.cpp: addPath: some error in: " << std::endl;
			std::cout << "exportPath.cpp: getLine" << std::endl;
			return;
		}
		std::ofstream bshrc(config[i], std::ios::app);
    	bshrc << line << std::endl;
    	bshrc.close();
	}
}
void removePath(const std::string& path){
	std::vector<std::string> config = findConfig();
	if(config.size() == 0){
		std::cout << "======================= ERROR =======================" << std::endl;
		std::cout << "exportPath.cpp: removePath: cannot find config file " << std::endl;
		std::cout << "probably does not work for your system" << std::endl;
		std::cout << "cannot remove exportPath" << std::endl;
		return;
	}
	for(int i = 0; i < config.size(); ++i){
		std::string line = getLine(config[i], path);
		if(line == "-1"){
			std::cout << "======================= ERROR =======================" << std::endl;
			std::cout << "exportPath.cpp: removePath: some error in: " << std::endl;
			std::cout << "exportPath.cpp: getLine" << std::endl;
			return;
		}
    	std::string l;
    	std::vector<std::string> v;
    	std::ifstream file(config[i]);
    	while(std::getline(file,l)){
        	if(l != line)
            	v.push_back(line);
    	}
    	file.close();
    	std::ofstream newfile(config[i]);
    	for(int i = 0; i < v.size(); ++i)
        	newfile << v[i] << std::endl;
    	newfile.close();
	}
}