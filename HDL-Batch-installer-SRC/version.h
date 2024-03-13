#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "13";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2024";
	static const char UBUNTU_VERSION_STYLE[] =  "24.03";
	
	//Software Status
	static const char STATUS[] =  "Release Candidate";
	static const char STATUS_SHORT[] =  "rc";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 5;
	static const long BUILD  = 1;
	static const long REVISION  = 6;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 10;
	#define RC_FILEVERSION 3,5,1,6
	#define RC_FILEVERSION_STRING "3, 5, 1, 6\0"
	static const char FULLVERSION_STRING [] = "3.5.1.6";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 99;
	

}
#endif //VERSION_H
