#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <assert.h>
#include "qh_vector.h"

void test1()                                    //���Թ��캯��
{
	std::string str = "Test of function vector(size_t, const T&)";
	qh::vector<std::string> myVec(10, str);
	qh::vector<std::string> myVec1(myVec);
	assert(myVec.size() == 10);
	for (size_t i = 0; i < myVec.size(); ++i)
	{
		assert(myVec[i] == str);
	}	
	assert(myVec1.size() == 10);
	for (size_t i = 0; i < myVec1.size(); ++i)
	{
		assert(myVec1[i] == str);
	}	
}

void test2()                                  //���Ը�ֵ����
{
	std::string str = "Test of operator = ";
	qh::vector<std::string> myVec(10, str);
	qh::vector<std::string> myVec1;
	qh::vector<std::string> myVec2;
	myVec2 = myVec1 = myVec;
	assert(myVec1.size() == 10);
	assert(myVec2.size() == 10);
	for (size_t i = 0; i < myVec.size(); ++i)
	{
		assert(myVec1[i] == str);
		assert(myVec2[i] == str);
	}	
}

void test3()                                 //����push_back����
{
	int num[] = {1,2,3,4,5,6,7,8};
	qh::vector<int> num_vec;
	for(size_t i = 0; i < 8; ++i)
		num_vec.push_back(num[i]);
	assert(num_vec.size() == 8);
	for(int i = 0; i < 8; ++i)
		assert(num_vec[i] == num[i]);
}

void test4()                                 //��������vector<vector<int>>���ɶ�ά����
{
	int num[] = {1,2,3,4,5,6,7,8};
	qh::vector<int> num_vec;
	qh::vector<qh::vector<int> > numVec_vec;
	for(int i = 0; i < 8; ++i)
		num_vec.push_back(num[i]);
	for (int i = 0; i < 3; ++i)
		numVec_vec.push_back(num_vec);
	assert(numVec_vec.size() == 3);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 8; ++j)
			assert(numVec_vec[i][j] == num[j]);	
}

void test5()                                  //����pop_back����
{
	int num[] = {1,2,3,4,5,6,7,8};
	qh::vector<int> num_vec;
	for(int i = 0; i < 8; ++i)
		num_vec.push_back(num[i]);
	for(int i = 0; i < 8; ++i)
	{
		num_vec.pop_back();
		assert(num_vec.size() == 8 - i - 1);
		for (size_t j = 0; j < num_vec.size(); ++j)
			assert(num_vec[j] == num[j]);	
	}
}

void test6()                                   //����resize����
{
	int num[] = {1,2,3,4,5,6,7,8};
	int numResize[] = {1,2,3,4,5,6,7,8,0,0,0,0};
	qh::vector<int> num_vec;
	for(int i = 0; i < 8; ++i)
		num_vec.push_back(num[i]);
	for (int i = 12; i >= 0; --i)
	{
		num_vec.resize(i);
		for (size_t j = 0; j < num_vec.size(); ++j)
			assert(num_vec[j] == numResize[j]);	
	}
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
	test6();
#ifdef WIN32
	system("pause");
#endif

	return 0;
}

