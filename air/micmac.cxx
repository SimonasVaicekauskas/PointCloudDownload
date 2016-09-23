#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

#define GLOG_NO_ABBREVIATED_SEVERITIES
#ifndef __GNUC__
#include <windows.h>
#endif
#include <glog/logging.h>


std::string exec(const char* cmd) {
	char buffer[128];
	//char* bufferis = new char[128];
	std::string result = "";
	//std::ofstream outfile("new2.txt", std::ofstream::binary);

#ifdef __GNUC__
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
#else
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
#endif
	
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			
		 	result += buffer;
	//		cout << buffer << endl;
	}
	if (fgets(buffer, 128, pipe.get()) != NULL)
	{
		printf("Yra info");
	}
	else {
		std::cout	 << result << "\n";
	}
	return result;
}
