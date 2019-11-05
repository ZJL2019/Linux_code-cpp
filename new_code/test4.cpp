#include<iostream>
using namespace std;
#include<vector>
class Solution {
public:
	bool Find(int target, vector<vector<int> > array) 
	{
		if (array.size() == 0 || array[0].size() == 0)
		{
			return false;
		}
		int rows = array.size(), cols = array[0].size();
		int r = 0, c = cols - 1;
		while (r<=rows - 1 && c>=0)
		{
			if (target == array[r][c])
			{
				return true;
			}
			else if (target < array[r][c])
			{
				c--;
			}
			else
			{
				r++;
			}
		}
		return false;
	}
};