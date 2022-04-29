#include <iostream>

#define MAX_N 1200000

class Solution
{
private:
	int n = 0;
	int a[MAX_N] = {};
	int dp[MAX_N] = {};

private:
	void Initiate()
	{
		for (auto& p : dp) p = __INT_MAX__;
	}

	static int LowerBound(const int* st, int num, int k)
	{
		int l = 0, r = num, mid;
		while (l < r)
		{
			mid = (l + r) >> 1;
			if (st[mid] < k) l = mid + 1;
			else r = mid;
		}
		return l;
	}

public:
	int LongestIncreaseSubsequence()
	{
		Initiate();
		for (int i = 0; i < n; i++)
		{
			auto lb = LowerBound(dp, n, a[i]);
			dp[lb] = a[i];
		}
		return LowerBound(dp, n, __INT_MAX__);
	}

	void Input()
	{
		std::cin >> n;
		for (int i = 0; i < n; i++)
		{
			std::cin >> a[i];
		}
	}
};

int main()
{
	Solution solution;

	solution.Input();
	std::cout << solution.LongestIncreaseSubsequence();

	return 0;
}