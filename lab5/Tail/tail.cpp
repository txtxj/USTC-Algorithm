#include <iostream>
#include <string>

class Integer
{
private:
	static constexpr unsigned int maxSize = 2048;
	unsigned int n;
	unsigned int arr[maxSize]{};
public:
	explicit Integer(long long integer = 0)
	{
		n = 1;
		for (auto& i : arr)
		{
			i = integer % 10;
			integer /= 10;
			if (integer != 0)
			{
				n += 1;
			}
		}
	}
	[[nodiscard]] unsigned int Length() const
	{
		return n;
	}
	static Integer Pow(Integer a, unsigned int b, const Integer& mod)
	{
		Integer ans(1);
		while (b != 0)
		{
			if (b & 1)
			{
				ans = ans * a % mod;
			}
			a = a * a % mod;
			b >>= 1;
		}
		return ans;
	}
	bool operator<(const Integer& other) const
	{
		if (n < other.n)
		{
			return true;
		}
		if (n > other.n)
		{
			return false;
		}
		for (int i = (int)n; i >= 0; i--)
		{
			if (arr[i] < other.arr[i])
			{
				return true;
			}
			if (arr[i] > other.arr[i])
			{
				return false;
			}
		}
		return false;
	}
	Integer operator+(const Integer& other) const
	{
		Integer ans;
		int top = (int)std::max(other.n, n);
		ans.n = top + 1;
		ans.arr[0] = 0;
		for (int i = 0; i < top; i++)
		{
			ans.arr[i + 1] = (ans.arr[i] + arr[i] + other.arr[i]) / 10;
			ans.arr[i] = (ans.arr[i] + arr[i] + other.arr[i]) % 10;
		}
		while (ans.arr[ans.n - 1] == 0 && ans.n > 1)
		{
			ans.n -= 1;
		}
		return ans;
	}
	Integer operator*(const Integer& other) const
	{
		Integer ans;
		ans.n = other.n + n;
		for (auto& i : ans.arr)
		{
			i = 0;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < other.n; j++)
			{
				ans.arr[i + j] += arr[i] * other.arr[j];
				ans.arr[i + j + 1] += ans.arr[i + j] / 10;
				ans.arr[i + j] %= 10;
			}
		}
		while (ans.arr[ans.n - 1] == 0 && ans.n > 1)
		{
			ans.n -= 1;
		}
		return ans;
	}
	Integer operator*(const unsigned int other) const
	{
		Integer ans(0);
		for (int i = 0; i < n; i++)
		{
			ans.arr[i] = arr[i] * other;
		}
		for (int i = 0; i < n; i++)
		{
			ans.arr[i + 1] += ans.arr[i] / 10;
			ans.arr[i] %= 10;
		}
		ans.n = n;
		while (ans.arr[ans.n - 1] >= 10)
		{
			ans.arr[ans.n] = ans.arr[ans.n - 1] / 10;
			ans.arr[n - 1] %= 10;
			ans.n += 1;
		}
		return ans;
	}
	Integer operator%(const Integer& other) const
	{
		// TODO: finish big int mod
		if (*this < other)
		{
			return *this;
		}
		Integer ans;

		return ans;
	}
	Integer operator/(const unsigned int other) const
	{
		Integer ans(0);
		unsigned int tmp = 0;
		for (int i = (int)n - 1; i >= 0; i--)
		{
			tmp *= 10;
			tmp += arr[i];
			ans.arr[i] = tmp / other;
			tmp %= other;
			if (ans.arr[i] != 0 && ans.n == 1)
			{
				ans.n = i + 1;
			}
		}
		return ans;
	}
	Integer& operator=(unsigned int other)
	{
		n = 1;
		for (auto& i : arr)
		{
			i = other % 10;
			other /= 10;
			if (other != 0)
			{
				n += 1;
			}
		}
		return *this;
	}
	Integer& operator=(const Integer& other)
	{
		if (this == &other)
		{
			return *this;
		}
		n = other.n;
		for (int i = 0; i < maxSize; i++)
		{
			arr[i] = other.arr[i];
		}
		return *this;
	}
	Integer& operator*=(unsigned int other)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] *= other;
		}
		for (int i = 0; i < n; i++)
		{
			arr[i + 1] += arr[i] / 10;
			arr[i] %= 10;
		}
		while (arr[n - 1] >= 10)
		{
			arr[n] = arr[n - 1] / 10;
			arr[n - 1] %= 10;
			n += 1;
		}
		return *this;
	}
	Integer& operator+=(const Integer& other)
	{
		int top = (int)std::max(other.n, n);
		n = top + 1;
		for (int i = 0; i < top; i++)
		{
			arr[i] += other.arr[i];
			arr[i + 1] += arr[i] / 10;
			arr[i] %= 10;
		}
		while (arr[n - 1] == 0 && n > 1)
		{
			n -= 1;
		}
		return *this;
	}
	Integer& operator*=(const Integer& other)
	{
		Integer ans;
		ans.n = other.n + n;
		for (auto& i : ans.arr)
		{
			i = 0;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < other.n; j++)
			{
				ans.arr[i + j] += arr[i] * other.arr[j];
				ans.arr[i + j + 1] += ans.arr[i + j] / 10;
				ans.arr[i + j] %= 10;
			}
		}
		while (ans.arr[ans.n - 1] == 0 && ans.n > 1)
		{
			ans.n -= 1;
		}
		*this = ans;
		return *this;
	}
	friend std::istream& operator>>(std::istream& in, Integer& x)
	{
		std::string str;
		in >> str;
		x.n = (int)str.length();
		for (int i = 0; i < x.n; i++)
		{
			x.arr[i] = str[x.n - i - 1] ^ 48;
		}
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const Integer& x)
	{
		for (int i = (int)x.n - 1; i >= 0; i--)
		{
			out << x.arr[i];
		}
		return out;
	}
};

class Solution
{
private:
	int k;
	int cnt;
	int* r;
	int* p;
public:
	explicit Solution(int kk)
	{
		k = kk;
		cnt = 0;
		r = new int[k];
		p = new int[k];
	}
	~Solution()
	{
		delete[] r;
		delete[] p;
	}

	void AddPair(int rr, int pp)
	{
		r[cnt] = rr;
		p[cnt] = pp;
		cnt += 1;
	}

	void PrintAnswer(std::ostream& out)
	{
		Integer M(1);
		for (int i = 0; i < k; i++)
		{
			M *= p[i];
		}
		Integer ans(0);
		for (int i = 0; i < k; i++)
		{
			ans += M / p[i] * Integer::Pow(m[i], p[i] - 2, M / p[i]) * (unsigned int)r[i];
		}
		out << ans % M;
	}
};

int main()
{
	#ifdef BIGINTDEBUG
	Integer x, y;
	std::cin >> x >> y;
	std::cout << x << std::endl << y;
	Integer z = x + y;
	std::cout << z << std::endl;
	Integer w = x * y;
	std::cout << w << std::endl;
	return 0;
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