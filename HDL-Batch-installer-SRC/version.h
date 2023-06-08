#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "08";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2023";
	static const char UBUNTU_VERSION_STYLE[] =  "23.06";
	
	//Software Status
	static const char STATUS[] =  "Release Candidate";
	static const char STATUS_SHORT[] =  "rc";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 5;
	static const long BUILD  = 0;
	static const long REVISION  = 2;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 17;
	#define RC_FILEVERSION 3,5,0,2
	#define RC_FILEVERSION_STRING "3, 5, 0, 2\0"
	static const char FULLVERSION_STRING [] = "3.5.0.2";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 99;
	

}
#endif //VERSION_H
