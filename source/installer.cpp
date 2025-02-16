#include "installer.h"
std::string getHomedir(){
    const char* homeDir = getenv("HOME");
    if (homeDir) {
        return homeDir;
    } else {
        std::cout << "======================== ERROR ========================" << std::endl;
        std::cout << "==== some error in installer.cpp: getHomedir() ====" << std::endl;
        std::cout << std::endl;      
        return "";
    }
}
void uninstall(){
    std::string root = getHomedir() + "/" + mainDir;
    std::string cmd = "rm -rf " + root;
    system(cmd.c_str());
    std::string path = "export PATH=\"" + root + "/bin:$PATH\"";
    std::string bash = getHomedir() + "/" + ".bashrc";
    std::string line;
    std::vector<std::string> v;
    std::ifstream file(bash);
    while(std::getline(file,line)){
        if(line != path)
            v.push_back(line);
    }
    file.close();
    std::ofstream newfile(bash);
    for(int i = 0; i < v.size(); ++i)
        newfile << v[i] << std::endl;
    newfile.close();
    std::cout << "xpack-riscv-none-elf-gcc-14.2.0-3 has been removed from your computer" << std::endl;
}
bool checkProgram(const std::string& programName) {
    std::string command = "which " + programName + " > /dev/null 2>&1";
    int result = system(command.c_str());
    return result == 0;
}
bool exists(const std::string& path){
	return std::filesystem::exists(path);
}
const std::string root = getHomedir() + "/builder";
int main(int argc, char* argv[]){
	if(argc > 1 && std::string(argv[1]) == "uninstall"){
		uninstall();
		return 0;
	}
	if(argc > 1 && std::string(argv[1]) == "reinstall")
		uninstall();
    std::string currPath = "./";
    if(argc > 1 && std::string(argv[1]) != "reinstall")
        currPath = std::string(argv[1]);
	std::string root = getHomedir() + "/" + mainDir;
	if(exists(root)){
		std::cout << "===================== ERROR =====================" << std::endl;
		std::cout << root << " already exists" << std::endl;
		std::cout << "Cannot install riscv-none-elf-gcc" << std::endl;
		std::cout << "Remove " << root << " before installation" << std::endl;
		return -1;
	}
    std::string cmd = "wget --no-check-certificate -P " + currPath + " https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz";
	system(cmd.c_str());
    cmd = "tar -xvzf " + currPath + "/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz -C " + getHomedir();
	system(cmd.c_str());
	std::string bash = getHomedir() + "/" + ".bashrc";
    std::string addedPath = "export PATH=\"" + root + "/bin:$PATH\"";
    std::ofstream bshrc(bash, std::ios::app);
    bshrc << addedPath << std::endl;
    bshrc.close();
    system(addedPath.c_str());
	//export PATH="/home/sergantdornan/xpack-riscv-none-elf-gcc-14.2.0-3/bin:$PATH"
	std::cout << "===================== xpack-riscv-none-elf-gcc-14.2.0-3 has been installed =====================" << std::endl;
	return 0;
}