#include <string.h>
#include <assert.h>
#include "ini_parser.h"

void test1()                               //����char��Ϊ�ָ����Ľ���
{
	const char* ini_text= "a=1\nb=2\n"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "1");

	const std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "");
}

void test2()				//�����ַ�����Ϊ�ָ����Ľ���
{
	const char* ini_text= "a=1||b=2||c=3"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "1");

	const std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "3");
}

void test3()				//���Զ�ָ�������ʱ�Ľ���
{
	const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "1");

	const std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "3");
}

void test4()			       //����key��valueֵʱ�Ľ���
{
	const char* ini_text= "&&&&a=test&&&b=&&"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "&", "=")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "test");

	const std::string b = parser.Get("b", NULL);
	assert(b == "");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "");
}

void test5()				//�����ļ���ȡ�Ľ���
{
	qh::INIParser parser;
	std::string file = "test.txt";
	if (!parser.Parse(file)) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "test");

	const std::string b = parser.Get("b", NULL);
	assert(b == "of");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "file");
}

void test6()
{
	const char* ini_text= "a=1\nb=123\nc=4\n\n"; 
	qh::INIParser parser;
	assert(parser.Get(ini_text, "b", NULL) == "123");
}

int main(int argc, char* argv[])
{
	//TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	return 0;
}


