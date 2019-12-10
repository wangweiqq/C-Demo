#include <iostream>
#include  <io.h>
#include <direct.h>
#include <string>
#include <sstream>
void CreateDir(std::string newDir) {
	char* next_token = nullptr;
	//std::string tmpdir = dir;
	char *tokenPtr = strtok_s((char*)newDir.c_str(), "/", &next_token);
	std::stringstream buff;
	while (tokenPtr != NULL) {
		buff << tokenPtr << "/";
		//std::cout << tokenPtr << '\n';
		if (_access(buff.str().c_str(), 0) == 0)
		{
			std::cout << "存在" << tokenPtr << std::endl;
		}
		else {
			std::cout << "不存在" << tokenPtr << std::endl;
			_mkdir(buff.str().c_str());
		}
		tokenPtr = strtok_s(NULL, "/", &next_token);
	}
}
int main() {

	std::string dir = "D:/Temp/11";
	//std::string dir = "D:/Project";
	int count = 0;
	CreateDir(dir);
	/*while (count < 10) {
		std::stringstream ss;
		ss<< dir << "/" << ++count << ".tiff";
		std::string str = ss.str();
		std::cout << str << std::endl;
	}*/

	if (_access(dir.c_str(), 0) == 0)
	{
		std::cout << "存在" << std::endl;
	}
	else {
		std::cout << "不存在" << std::endl;
		
		_mkdir(dir.c_str());
	}
	//_access()
	return 0;
}