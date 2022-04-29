#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
private:
	int n;
	int k;
	long long* a;
	std::vector<std::pair<long long, int> > vec;
private:
	static int Min2(int a, int b)
	{
		return a < b ? a : b;
	}
public:
	Solution(int nn, int kk)
	{
		n = nn;
		k = kk;
		a = new long long[n];
		vec.resize(n);
		vec.clear();
	}
	~Solution()
	{
		delete[] a;
	}
	void ReadLine(std::istream& in)
	{
		in >> a[0];
		for (int i = 1; i < n; i++)
		{
			in >> a[i];
			a[i] += a[i - 1];
		}
	}
	int Solve()
	{
		int ans = __INT_MAX__;
		for (int i = 0; i < n; i++)
		{
			if (a[i] <= vec.back().first)
			{
				auto it = std::lower_bound(vec.begin(), vec.end(), std::make_pair(a[i], 0));
				vec.erase(it, vec.end());
			}
			vec.emplace_back(a[i], i);
			auto it = std::upper_bound(vec.begin(), vec.end(), std::make_pair(a[i] - k, 0)) - 1;
			if (it >= vec.begin())
			{
				ans = Min2(ans, i - it -> second);
			}
			#ifdef DEBUG
			std::cout << "/******************/" << std::endl;
			for (auto p : vec)
			{
				std::cout << p.first << " ";
			}
			std::cout << std::endl;
			std::cout << "it = " << it - vec.begin() << std::endl;
			std::cout << "ans = " << ans << std::endl;
			std::cout << "/******************/" << std::endl;
			#endif
		}
		return ans;
	}
};

int main()
{
	int n, k;
	std::cin >> n >> k;
	Solution solution(n, k);
	solution.ReadLine(std::cin);
	std::cout << solution.Solve();
	return 0;
}