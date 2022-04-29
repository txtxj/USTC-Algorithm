#include <iostream>
#include <cstring>

#define MOD 1000000007
#define MAXV 50000

class Solution
{
private:
	int ans[MAXV]{};
public:
	int n, v;
	int* coins;
public:
	Solution(int nn, int vv)
	{
		n = nn;
		v = vv;
		coins = new int[nn];
		std::memset(ans, 0, sizeof ans);
	}
	~Solution()
	{
		delete[] coins;
	}
	void ReadCoins()
	{
		for (int i = 0; i < n ; i++)
		{
			std::cin >> coins[i];
		}
	}
	int Solve()
	{
		ans[0] = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 1; j <= v; j++)
			{
				if (j >= coins[i])
				{
					ans[j] = (ans[j] + ans[j - coins[i]]) % MOD;
				}
			}
		}
		return ans[v];
	}
};

int main()
{
	int n, v;
	std::cin >> n >> v;
	Solution solution = Solution(n, v);
	solution.ReadCoins();
	std::cout << solution.Solve() << std::endl;
	return 0;
}