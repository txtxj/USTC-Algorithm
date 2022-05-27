#include <iostream>
#include <string>

class Solution
{
private:
	int k;
	int cnt;
	long long* r;
	long long* p;
	long long* m;
private:
	static long long Pow(long long a, long long b, long long mod)
	{
		long long ans = 1;
		long long aa = a % mod;
		while (b != 0)
		{
			if (b & 1)
			{
				ans = aa * ans % mod;
			}
			aa = aa * aa % mod;
			b >>= 1;
		}
		return ans;
	}
	static long long Inverse(long long a, long long mod)
	{
		return Pow(a, mod - 2, mod);
	}
public:
	explicit Solution(int kk)
	{
		k = kk;
		cnt = 0;
		r = new long long[k];
		p = new long long[k];
		m = new long long[k];
	}
	~Solution()
	{
		delete[] r;
		delete[] p;
		delete[] m;
	}

	void AddPair(int rr, int pp)
	{
		r[cnt] = rr;
		p[cnt] = pp;
		cnt += 1;
	}

	void PrintAnswer(std::ostream& out) const
	{
		long long M = 1;
		for (int i = 0; i < k; i++)
		{
			M *= p[i];
		}
		#ifdef DEBUG
		std::cout << "/******************/" << std::endl;
		std::cout << "M = " << M << std::endl;
		std::cout << "/******************/" << std::endl;
		#endif
		long long ans = 0;
		for (int i = 0; i < k; i++)
		{
			m[i] = M / p[i];
			#ifdef DEBUG
			std::cout << "/******************/" << std::endl;
			std::cout << "M[" << i << "] = " << m[i] << std::endl;
			long long t = Inverse(m[i], p[i]);
			std::cout << "t[" << i << "] = " << t << std::endl;
			std::cout << "r[" << i << "] = " << r[i] << std::endl;
			std::cout << "p[" << i << "] = " << p[i] << std::endl;
			if (m[i] * t % p[i] == 1)
			{
				std::cout << "Inverse Decision Pass!" << std::endl;
			}
			std::cout << "/******************/" << std::endl;
			std::cout << ans << " + mul(above) = ";
			ans += m[i] * t * (long long)r[i];
			std::cout << ans << std::endl;
			#else
			ans += m[i] * Inverse(m[i], p[i]) * (long long)r[i];
			#endif
		}
		out << ans % M;
	}
};

int main()
{
	#ifdef BIGINTDEBUG
	Integer x, y;
	std::cin >> x >> y;
	std::cout << x % y;
	return 0;
	#endif
	#ifdef FILEREAD
	std::freopen("../test.in", "r", stdin);
	std::freopen("../ans.out", "w", stdout);
	#endif
	int k, r, p;
	std::cin >> k;
	Solution solution(k);
	for (int i = 0; i < k; i++)
	{
		std::cin >> r >> p;
		solution.AddPair(r, p);
	}
	solution.PrintAnswer(std::cout);
	return 0;
}