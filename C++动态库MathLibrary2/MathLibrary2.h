// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATHLIBRARY2_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATHLIBRARY2_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MATHLIBRARY2_EXPORTS
#define MATHLIBRARY2_API __declspec(dllexport)
#else
#define MATHLIBRARY2_API __declspec(dllimport)
#endif

// �����Ǵ� MathLibrary2.dll ������
class MATHLIBRARY2_API CMathLibrary2 {
public:
	CMathLibrary2(void);
	// TODO:  �ڴ�������ķ�����
	int MyAdd(int a, int b);
};

extern MATHLIBRARY2_API int nMathLibrary2;

extern MATHLIBRARY2_API int __stdcall fnMathLibrary2(void);
