#include <iostream>

#define MAXN 2001

class Solution
{
private:
	int n;
	int a[MAXN][MAXN]{};
	int line[MAXN][MAXN]{};
	int row[MAXN][MAXN]{};
	int ans[MAXN][MAXN]{};
private:
	static int Min3(int a, int b, int c)
	{
		a = a < b ? a : b;
		return a < c ? a : c;
	}
public:
	explicit Solution(int nn)
	{
		n = nn;
	}
	void ReadMatrix(std::istream& in)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				in >> a[i][j];
			}
		}
	}
	int Solve()
	{
		int res = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (a[i][j] == 1)
				{
					line[i][j] = line[i - 1][j] + 1;
					row[i][j] = row[i][j - 1] + 1;
					ans[i][j] = Min3(line[i][j], row[i][j], ans[i - 1][j - 1] + 1);
					if (ans[i][j] > res)
					{
						res = ans[i][j];
					}
				}
				else
				{
					line[i][j] = 0;
					row[i][j] = 0;
					ans[i][j] = 0;
				}
			}
		}
		return res;
	}
};

int main()
{
	int n;
	std::cin >> n;
	Solution solution = Solution(n);
	solution.ReadMatrix(std::cin);
	std::cout << solution.Solve();
	return 0;
}