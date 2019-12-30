#include <iostream>
#include <string>
#include <codecvt>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#define GETSTR(x) #x
struct A {
	A(double a, int b) {
		this->a = a;
		this->b = b;
	}
	double a;
	int b;
};
int main() {
	std::vector<std::shared_ptr<A>> list;
	list.push_back(std::make_shared<A>(10.0, 5));
	list.push_back(std::make_shared<A>(9.0, 4));
	list.push_back(std::make_shared<A>(1, 8));
	list.push_back(std::make_shared<A>(7.0, 2));
	auto result = std::minmax_element(list.begin(), list.end(), [](auto it1, auto it2) {
		//double d1 = (*it1).a;
		//double d2 = (*it2).a;
		//return d1 < d2;
		return it1->a < it2->a;
	});
	std::shared_ptr<A> min;
		std::shared_ptr<A> max;
	if (result.first != list.end()) {
		min = *result.first;
	}
	if (result.second != list.end()) {
		max = *result.second;
	}
	std::string str1 = GETSTR(
#include <io.h>
		xxx;
		yyy;
		zzz;
	);
	std::cout << str1 << std::endl;
	std::string str2 = R"(
#include <io.h>
		xxx;
		yyy;
		zzz;)";
	std::cout << str2 << std::endl;
	//std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	//std::string string = converter.to_bytes(L"这是一个宽字符串");
	//std::wstring sss = converter.from_bytes(string);

	//std::wstring str = L"123,我是谁？我爱钓鱼岛！";

	//std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

	//std::string narrowStr = conv.to_bytes(str);
	//{
	//	std::ofstream ofs("c:\\test.txt");
	//	ofs << narrowStr;
	//}

	//std::wstring wideStr = conv.from_bytes(narrowStr);
	//{
	//	std::locale::global(std::locale("Chinese-simplified"));
	//	std::wofstream ofs(L"c:\\testW.txt");
	//	ofs << wideStr;
	//}

	/*std::wstring str = L"abc";
	std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
	std::string str1 = convert.to_bytes(str);
	std::wcout << str << std::endl;
	std::cout << str1 << std::endl;*/
	return 0;
}