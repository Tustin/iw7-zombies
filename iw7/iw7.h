// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IW7_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IW7_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include "Commands.hpp"

#ifdef IW7_EXPORTS
#define IW7_API __declspec(dllexport)
#else
#define IW7_API __declspec(dllimport)
#endif

// This class is exported from the iw7.dll
class IW7_API Ciw7 {
public:
	Ciw7(void);
	// TODO: add your methods here.
};

extern IW7_API int niw7;

IW7_API int fniw7(void);


