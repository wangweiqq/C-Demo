// MathLibrary2.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "MathLibrary2.h"


// ���ǵ���������һ��ʾ��
MATHLIBRARY2_API int nMathLibrary2=0;

// ���ǵ���������һ��ʾ����
MATHLIBRARY2_API int __stdcall fnMathLibrary2(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� MathLibrary2.h
CMathLibrary2::CMathLibrary2()
{
    return;
}
int CMathLibrary2::MyAdd(int a, int b){

	return  a + b;
}