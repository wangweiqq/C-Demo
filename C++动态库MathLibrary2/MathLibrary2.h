// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MATHLIBRARY2_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MATHLIBRARY2_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef MATHLIBRARY2_EXPORTS
#define MATHLIBRARY2_API __declspec(dllexport)
#else
#define MATHLIBRARY2_API __declspec(dllimport)
#endif

// 此类是从 MathLibrary2.dll 导出的
class MATHLIBRARY2_API CMathLibrary2 {
public:
	CMathLibrary2(void);
	// TODO:  在此添加您的方法。
	int MyAdd(int a, int b);
};

extern MATHLIBRARY2_API int nMathLibrary2;

extern MATHLIBRARY2_API int __stdcall fnMathLibrary2(void);
