#include "installer.h"
#include "exportPath.h"
const std::string tarName = "xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz";
const std::string bin = getHomedir() + "/" + mainDir + "/bin";
void uninstall(){
    std::string root = getHomedir() + "/" + mainDir;
    std::string cmd = "rm -rf " + root;
    system(cmd.c_str());
    removePath(bin);
    std::cout << "xpack-riscv-none-elf-gcc-14.2.0-3 has been removed from your computer" << std::endl;
}
bool checkProgram(const std::string& programName) {
    std::string command = "which " + programName + " > /dev/null 2>&1";
    int result = system(command.c_str());
    return result == 0;
}
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
	std::string cmd = "";
	if(!exists(getHomedir() + "/" + tarName)){
    	cmd = "wget --no-check-certificate -P " + cd + " https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz";
		system(cmd.c_str());
		cmd = "tar -xvzf " + cd + "/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz -C " + getHomedir();
		system(cmd.c_str());
	}
	else{
		cmd = "tar -xvzf " + getHomedir() + "/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz -C " + getHomedir();
		system(cmd.c_str());
	}
    addPath(bin);
	//export PATH="/home/sergantdornan/xpack-riscv-none-elf-gcc-14.2.0-3/bin:$PATH"
    //set -U fish_user_paths "/opt/mycompiler/bin" $fish_user_paths
	std::cout << "===================== xpack-riscv-none-elf-gcc-14.2.0-3 has been installed =====================" << std::endl;
	return 0;
}