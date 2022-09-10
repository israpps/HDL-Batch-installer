#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion
{

//Date Version Types
static const char DATE[] = "10";
static const char MONTH[] = "09";
static const char YEAR[] = "2022";
static const char UBUNTU_VERSION_STYLE[] =  "22.09";

//Software Status
static const char STATUS[] =  "Release Candidate";
static const char STATUS_SHORT[] =  "rc";

//Standard Version Type
static const long MAJOR  = 3;
static const long MINOR  = 4;
static const long BUILD  = 0;
static const long REVISION  = 0;

//Miscellaneous Version Types
static const long BUILDS_COUNT  = 41;
#define RC_FILEVERSION 3,4,0,0
#define RC_FILEVERSION_STRING "3, 4, 0, 0\0"
static const char FULLVERSION_STRING [] = "3.4.0.0";

//These values are to keep track of your versioning state, don't modify them.
static const long BUILD_HISTORY  = 99;


}
#endif //VERSION_H
