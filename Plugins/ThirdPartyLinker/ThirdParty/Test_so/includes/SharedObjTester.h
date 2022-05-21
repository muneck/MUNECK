#pragma once

#ifdef DLL_EXPORT
	#define API_DECLSPEC __declspec(dllexport)
#else
	#define API_DECLSPEC
#endif


#ifdef __cplusplus
	extern "C"{
 #endif

class SharedObjTester
{
private:
	int x;
public:
	SharedObjTester();
	~SharedObjTester();
	API_DECLSPEC int test1(int flag);
	API_DECLSPEC void setx(int x_in);

};

#ifdef __cplusplus
	}
#endif
