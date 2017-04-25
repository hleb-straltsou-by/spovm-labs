#ifdef __linux
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <vector>
#include <time.h>
#include <aio.h>
#include <dlfcn.h>

#include "FileConcatanainerLinux.h"
#endif

using namespace std;

int main(int argc, char** argv)
{
	#ifdef __linux
	void *dl_handle;			// handle for library
	void (*func)(vector<string>, string);	// function header
	char *error;
	
	// Open shared dynamic library
	dl_handle = dlopen("libconct.so", RTLD_LAZY);
	if(!dl_handle){
		printf("Error! Cannot open dynamic library... %s\n", dlerror());
		return;
	}
	
	// Find address of function in library
	func = dlsym(dl_handle, "concateFiles");
	error = dlerror();
	if(error != NULL){
		printf("%s\n", error);
		return;
	}

	// Call find function
	vector<string> inputFiles;
	inputFiles.push_back("input-1.txt");
	inputFiles.push_back("input-2.txt");
	string outputFile = "output.txt";
	
	func(inputFiles, outputFile);
	#endif
	
	getchar();
  	return 0;
}




