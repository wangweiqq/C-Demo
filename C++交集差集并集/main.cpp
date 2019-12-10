#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
int main() {
	std::set<int> v1{ 1,10,5,7,4,3,9,8 };
	std::set<int> v2{ 11,1,5,8,20,30 };
	/*for (auto i = v1.begin(); i != v1.end(); ++i) {
		std::cout << *i << " ,";
	}*/
	std::set<int> res1;
	//交集
	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::inserter(res1,res1.begin()));
	std::cout << "交集" << std::endl;
	for (auto i = res1.begin(); i != res1.end(); ++i) {
		std::cout << *i << " ,";
	}
	std::cout << "\n差集1"<<std::endl;
	//差集1
	std::set<int> res2;
	std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::inserter(res2, res2.begin()));
	for (auto i = res2.begin(); i != res2.end(); ++i) {
		std::cout << *i << " ,";
	}
	std::cout << "\n差集2" << std::endl;
	std::set<int> res3;
	std::set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), std::inserter(res3, res3.begin()));
	for (auto i = res3.begin(); i != res3.end(); ++i) {
		std::cout << *i << " ,";
	}
	std::cout << "\n并集" << std::endl;
	std::set<int> res4;
	std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::inserter(res4, res4.begin()));
	for (auto i = res4.begin(); i != res4.end(); ++i) {
		std::cout << *i << " ,";
	}
	std::cout << "交集2" << std::endl;
	std::map<int, std::string> v3{ {10,"a"},{9,"b"},{2,"c"},{5,"d"} };
	std::map<int, std::string> v4{ { 5,"a" },{ 19,"b" },{ 2,"c" },{ 45,"d" } };
	/*for (auto i = v3.begin(); i != v3.end(); ++i) {
		std::cout << "(" << (*i).first << "," << (*i).second.c_str() << ") ,";
	}*/
	std::map<int, std::string> res5;
	std::set_intersection(v3.begin(), v3.end(), v4.begin(), v4.end(), std::inserter(res5, res5.begin()));
	//std::set_intersection(v3.begin(), v3.end(), v4.begin(), v4.end(), std::back_inserter(res5));
	std::cout << "交集" << std::endl;
	for (auto i = res5.begin(); i != res5.end(); ++i) {
		std::cout << "(" << (*i).first << "," << (*i).second.c_str() << ") ,";
	}
	return 0;
}