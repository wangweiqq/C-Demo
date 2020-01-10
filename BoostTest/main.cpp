#include <iostream>
#include <boost\operators.hpp>
#include <boost\uuid\uuid.hpp>
#include <boost\uuid\uuid_generators.hpp>
#include <boost\uuid\uuid_io.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\format.hpp>
#include <boost\xpressive\xpressive.hpp>
#include <boost\xpressive\xpressive_dynamic.hpp>
#include <boost\dynamic_bitset.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <vector>
#include <list>
#include <codecvt>
/**
1、boost::less_than_comparable 要求实现<号，自动实现>,<=,>=
2、boost::equality_comparable 要求实现=号，自动实现!=
3\ dereferenceable解引用，要求实现*号，自动实现->
复合：
1、totally_ordered:全序包含less_than_comparable，equality_comparable
2、additive：可加减，组合了addable，subtractable
3、multiplicative：可乘除，组合了multipliable和dividable
4、arithmetic：算数运算，组合了additive和multiplicative
5、unit_stoppable：可步进，组合了incrementable和decrementable
*/
template<typename T>
struct outable {
	friend std::ostream& operator<<(std::ostream& os, const T& x) {
		os << typeid(x).name();
		return os;
	}
	friend std::istream& operator >> (std::istream& is, T& x) {
		int date;
		is >> date;
		x.SetValue (date);
		return is;
	}
};
class demo_class: boost::totally_ordered<demo_class,
					boost::additive<demo_class>>,
					outable<demo_class>
{
public:
	demo_class() = default;
	//demo_class(const demo_class&) = default;
	demo_class(int n):x(n) {}
	~demo_class() {}
	void SetValue(int n) {
		x = n;
	}
	void print() {
		std::cout << x << std::endl;
	}
	demo_class& operator+=(const demo_class& l) {
		this->x += l.x;
		return *this;
	}
	demo_class& operator-=(const demo_class& l) {
		this->x -= l.x;
		return *this;
	}
private:
	friend bool operator<(const demo_class& l,const demo_class& d) {
		return l.x < d.x;
	}
	friend bool operator==(const demo_class& l, const demo_class& d) {
		return l.x == d.x;
	}
	
private:
	int x;
};
int main() {
	std::locale global(std::locale(""));
	boost::property_tree::ptree pt;
	boost::property_tree::read_xml("conf.xml",pt);

	std::string gui1 = pt.get<std::string>("conf.gui.<xmlattr>.id");
	auto ppp  = pt.get_child("conf.gui.<xmlattr>");
	//std::string gui2 = ppp.get_optional<std::string>("<xmlattr>.id").get();
	////if (gui2) {
	//	std::cout << gui2 << std::endl;
	////}
	//auto gui3 = ppp.get_value_optional<std::string>("<xmlattr>");
	for (auto it = ppp.begin(); it != ppp.end(); ++it) {
		std::cout << "Key:"<<it->first.data()<<",Value = "<<it->second.data() << std::endl;
	}

	std::string xmlstr1 = pt.get<std::string>("conf.theme");
	std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
	std::wstring ssss = convert.from_bytes(xmlstr1);
	//std::wstring ssss = convert.to_bytes(xmlstr1);
	std::wcout.imbue(std::locale("chs"));
	std::wcout << ssss << std::endl;

	auto& child = pt.get_child("conf.urls");
	for (auto it = child.begin(); it != child.end(); ++it) {
		std::cout << "Key:"<<it->first.data()<<",Value:"<<it->second.data() << std::endl;
		//it->second.p
	}

	auto& urlnew = child.add("url", "http://www.url4.com");
	urlnew.add("<xmlattr>.id", 666);
	std::wstring ttt = L"中文";
	std::string txt = convert.to_bytes(ttt);
	urlnew.add("<xmlattr>.type", txt);
	boost::property_tree::write_xml("conf2.xml", pt);



	return 0;
	boost::dynamic_bitset<> db2(0x16, BOOST_BINARY(10101));
	std::cout << db2 << std::endl;
	std::cout << std::hex << db2.to_ulong() << std::endl;
	boost::dynamic_bitset<> db(std::string("0100"));
	std::cout << db << std::endl;
	std::cout << db[0] << db[1] << db[2] << db[3] << std::endl;
	std::cout << std::hex << db.to_ulong() << std::endl;	
	db.resize(3);
	std::cout << db << std::endl;
	std::cout << std::hex << db.to_ulong() << std::endl;
	return 0;
	std::string str5 = "650103198011242315";
	//R"(\d{6}[1|2]\d{3}[0|1]\d[0-3]\d\d{3}[X|\d])"
	boost::xpressive::cregex reg = boost::xpressive::cregex::compile(R"(\d{6}([1|2]\d{3})([0|1]\d)([0-3]\d)\d{3}[X|\d])");
	boost::xpressive::cmatch what;
	bool bl5 = boost::xpressive::regex_match(str5.c_str(), what,reg);
	for (auto it = what.begin(); it != what.end(); ++it) {
		std::cout << *it << std::endl;
	}
	int year = boost::lexical_cast<int>(what[1]);
	int month = boost::lexical_cast<int>(what[2]);
	int date = boost::lexical_cast<int>(what[3]);
	return 0;
	boost::format fmt("|%s|.pos = %d\n");
	std::string str2 = "Long long ago,there was a king.";
	boost::iterator_range<std::string::iterator> rge;
	rge = boost::algorithm::find_first(str2, "long");
	std::cout << fmt%rge%(rge.begin() - str2.begin());

	rge = boost::algorithm::ifind_first(str2, "long");
	std::cout << fmt%rge % (rge.begin() - str2.begin());
	
	rge = boost::algorithm::find_nth(str2, "ng", 0);
	std::cout << fmt%rge % (rge.begin() - str2.begin());

	rge = boost::algorithm::find_head(str2, 5);
	std::cout << fmt%rge % (rge.begin() - str2.begin());

	rge = boost::algorithm::find_tail(str2, 5);
	std::cout << fmt%rge % (rge.begin() - str2.begin());

	rge = boost::algorithm::find_first(str2, "samus");
	bool bl = rge;
	bool bl2 = rge.empty();

	std::vector<std::string> list;
	boost::split(list, str2, boost::is_any_of(", "));

	std::string str4 = boost::join_if(list, ",", [](auto x) {
		return boost::contains(x, "ng");
	});

	std::string wstr = "hello世界你好.txt";
	if (boost::algorithm::iends_with(wstr,".TXT")) {
		std::cout << boost::algorithm::to_upper_copy(wstr) << std::endl;
	}
	if (boost::algorithm::starts_with(wstr, "hello")) {
		std::cout << boost::algorithm::replace_first_copy(wstr, "世界", "world") << std::endl;
	}
	std::cout << boost::algorithm::erase_first_copy(wstr, "你好") << std::endl;
	return 0;
	std::string str222 = boost::lexical_cast<std::string>(demo_class(1));
	demo_class objdemo = boost::lexical_cast<demo_class>(255);
	float fffff = boost::lexical_cast<float>("0.618");
	double fffff2 = boost::lexical_cast<double>("0.618");
	std::string sssss = boost::lexical_cast<std::string>(0.618);
	return 0;
	boost::uuids::uuid u;
	u = boost::uuids::nil_uuid();
	std::cout << u << std::endl;
	boost::uuids::string_generator sgen;
	u = sgen("0123456789abcdef0123456789abcde1");
	std::cout << u << std::endl;
	boost::uuids::name_generator ngen(u);
	boost::uuids::uuid u2 = ngen("Hello");
	std::cout << u2 << std::endl;
	std::cout << "random" << std::endl;
	boost::uuids::random_generator rgen;
	for (int i = 0; i < 10; i++) {
		std::cout << rgen() << std::endl;
	}
	//std::copy()
	demo_class a(10), b(20),c(10);
	std::cout << (a < b) << std::endl;
	std::cout << (a >= b) << std::endl;
	std::cout << (a <= c) << std::endl;
	std::cout << (a > c) << std::endl;
	std::cout << (a == c) << std::endl;
	std::cout << (a != b) << std::endl;
	(a + b).print();
	a.print();
	b.print();
	(a - b).print();
	return 0;
}