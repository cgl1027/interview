#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
#include <assert.h>
#include <string.h>

#define H_ARRAYSIZE(a) \
	((sizeof(a) / sizeof(*(a))) / \
	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

#define H_ARRAY_SIZE H_ARRAYSIZE

void test1()                                  //���Թ��캯��
{
	const char* str = "Test of ctor";
	qh::string myStr(str);
	assert(!strcmp(myStr.data(), str));
}

void test2()				     //���Ը��ƹ��캯��
{
	const char* str = "Test of assign ctor";
	qh::string myStr(str);
	qh::string myStr1(myStr);
	assert(!strcmp(myStr1.data(), str));
}

void test3()									
{
	char* str = "Test of qh::string(const char*, size_t)";
	qh::string myStr(str + 12, 27);
	assert(!strcmp(myStr.data(), &str[12]));
}

void test4()				     //����operator[]
{
	char* str = "Test of operator []";
	qh::string myStr(str);
	for (size_t i = 0; i < myStr.size(); ++i)
	{
		assert(myStr[i] == str[i]);
	}	
}

void test5()				     //���Ը�ֵ������
{
	const char* str = "Test of operator =";
	qh::string myStr(str);
	qh::string myStr1(&str[5]);
	myStr1 = myStr;
	assert(!strcmp(myStr1.data(), str));
}


int main(int argc, char* argv[])
{
	//TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
	//TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
	test1();
	test2();
	test3();
	test4();
	test5();

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
