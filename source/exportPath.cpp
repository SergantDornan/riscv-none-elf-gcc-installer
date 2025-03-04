#include "exportPath.h"
std::string findConfig(){
	for(int i = 0; i < configFiles.size(); ++i){
		if(exists(configFiles[i]))
			return configFiles[i];
	}
	return "-1";
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
	std::string config = findConfig();
	if(config == "-1"){
		std::cout << "======================= ERROR =======================" << std::endl;
		std::cout << "exportPath.cpp: addPath: cannot find config file " << std::endl;
		std::cout << "probably does not work for your system" << std::endl;
		std::cout << "cannot add exportPath" << std::endl;
		return;
	}
	std::string line = getLine(config, path);
	if(line == "-1"){
		std::cout << "======================= ERROR =======================" << std::endl;
		std::cout << "exportPath.cpp: addPath: some error in: " << std::endl;
		std::cout << "exportPath.cpp: getLine" << std::endl;
		return;
	}
	std::ofstream bshrc(config, std::ios::app);
    bshrc << line << std::endl;
    bshrc.close();
}
void removePath(const std::string& path){
	std::string config = findConfig();
	if(config == "-1"){
		std::cout << "======================= ERROR =======================" << std::endl;
		std::cout << "exportPath.cpp: removePath: cannot find config file " << std::endl;
		std::cout << "probably does not work for your system" << std::endl;
		std::cout << "cannot remove exportPath" << std::endl;
		return;
	}
	std::string line = getLine(config, path);
	if(line == "-1"){
		std::cout << "======================= ERROR =======================" << std::endl;
		std::cout << "exportPath.cpp: removePath: some error in: " << std::endl;
		std::cout << "exportPath.cpp: getLine" << std::endl;
		return;
	}
    std::string l;
    std::vector<std::string> v;
    std::ifstream file(config);
    while(std::getline(file,l)){
        if(l != line)
            v.push_back(line);
    }
    file.close();
    std::ofstream newfile(config);
    for(int i = 0; i < v.size(); ++i)
        newfile << v[i] << std::endl;
    newfile.close();
}