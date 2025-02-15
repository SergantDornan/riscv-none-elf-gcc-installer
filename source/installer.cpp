#include "installer.h"
//sudo apt update
//sudo apt install -y --no-install-recommends ca-certificates git make python3 openocd picocom
//tar -xvzf xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz


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
	std::string root = getHomedir() + "/" + mainDir;
	if(exists(root)){
		std::cout << "===================== ERROR =====================" << std::endl;
		std::cout << root << " already exists" << std::endl;
		std::cout << "Cannot install riscv-none-elf-gcc" << std::endl;
		std::cout << "Remove " << root << " before installation" << std::endl;
		return -1;
	}
	std::string cmd = "tar -xvzf xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz -C " + getHomedir();
	system(cmd.c_str());
	std::cout << "===================== xpack-riscv-none-elf-gcc-14.2.0-3 has been installed =====================" << std::endl;
	return 0;
}