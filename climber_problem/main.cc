#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

#define H_ARRAYSIZE(a) \
	((sizeof(a) / sizeof(*(a))) / \
	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

struct Mountain
{
	int mount_begin;
	int mount_end;
	int mount_height;
	Mountain(int b = 0, int e = 0, int h = 0) : mount_begin(b),mount_end(e),mount_height(h){}
};

static bool ComMount(Mountain m1, Mountain m2)
{
	return m1.mount_begin < m2.mount_begin;
}

void CreateMountVec(vector<Mountain>& mount, const char* pos, int num)
{
	Mountain mount_temp;
	for (int i = 0; i < num; ++i)
	{
		sscanf(++pos, "%d,%d,%d", &mount_temp.mount_begin, &mount_temp.mount_end, &mount_temp.mount_height);
		mount.push_back(mount_temp);
		while(*pos != '\n') ++pos;
	}
	sort(mount.begin(), mount.end(), ComMount);
}

int resolve(const char* input)
{
	int hori_dist = 0;
	int pre_height = 0;
	int mount_begin = -1;
	int mount_end = -1;
	int res = 0;
	const char* pos = input;
	int num;
	vector<Mountain> mount;

	sscanf(pos, "%d", &num);
	while(*pos != '\n') ++pos;

	CreateMountVec(mount, pos, num);

	for(int i = 0; i < num; ++i)
	{

		hori_dist = max(hori_dist, mount[i].mount_end);
		if(mount[i].mount_begin >= mount_begin && mount[i].mount_begin <= mount_end)
		{
			mount_end = max(mount_end, mount[i].mount_end);
			res += abs(pre_height-mount[i].mount_height);
		}
		else
		{
			mount_begin = mount[i].mount_begin;
			mount_end = mount[i].mount_end;
			res += pre_height + mount[i].mount_height;
		}
		pre_height = mount[i].mount_height;		
	}
	res += pre_height;
	return res + hori_dist;
}

int main(int argc, char* argv[]) 
{
	const char* input[] = {
		"3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
		"1\n1,2,1\n",
		"2\n1,2,1\n2,3,2",
		"3\n1,2,1\n2,3,2\n3,6,1",
		"4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
		"5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
		"1\n0,1,1",
		"2\n0,1,1\n2,4,3",
		"3\n0,1,1\n2,4,3\n3,5,1",
		"4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
		"5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		"6\n0,1,1\n1,5,2\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		"8\n0,1,1\n1,5,2\n2,4,3\n3,5,1\n5,6,1\n6,8,3\n7,8,4\n9,9,1",
		"7\n7,8,4\n6,8,3\n5,6,1\n3,5,1\n2,4,3\n1,5,2\n0,1,1"
		//TODO please add more test case here
	};
	int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 18, 23, 20};
	for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
	{
		assert(resolve(input[i]) == expectedSteps[i]);
	}
	return 0;
}
