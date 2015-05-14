#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

#define max(a,b) (a >= b ? a : b)

int resolve(const char* input)
{
	int stepBegin = 0;
	int stepEnd = 0;
	int height = 0;
	int horiDistance = 0;
	int preHeight = 0;
	int mountBegin = -1;
	int mountEnd = -1;
	int res = 0;
	const char* pos = input;
	int num;

	sscanf(pos, "%d", &num);
	while(*pos != '\n') ++pos;
	
	for(int i = 0; i < num; ++i)
	{
		sscanf(++pos, "%d,%d,%d", &stepBegin, &stepEnd, &height);
		horiDistance = max(horiDistance, stepEnd);
		
		if(stepBegin >= mountBegin && stepBegin <= mountEnd)
		{
			mountEnd = max(mountEnd, stepEnd);
			res += abs(preHeight - height);
		}
		else
		{
			mountBegin = stepBegin;
			mountEnd = stepEnd;
			res += preHeight + height;
		}
		
		preHeight = height;
		while(*pos != '\n') ++pos;
	}
	
	res += preHeight;
	return res + horiDistance;
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
	"7\n0,1,1\n1,5,2\n2,4,3\n3,5,1\n5,6,1\n6,8,3\n7,8,4",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 18, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
