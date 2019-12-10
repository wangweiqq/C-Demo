// MathLibrary2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MathLibrary2.h"


// 这是导出变量的一个示例
MATHLIBRARY2_API int nMathLibrary2=0;

// 这是导出函数的一个示例。
MATHLIBRARY2_API int __stdcall fnMathLibrary2(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 MathLibrary2.h
CMathLibrary2::CMathLibrary2()
{
    return;
}
int CMathLibrary2::MyAdd(int a, int b){

	return  a + b;
}