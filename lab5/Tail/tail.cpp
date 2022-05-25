#include <iostream>
#include <string>

class Integer
{
private:
	static constexpr unsigned int maxSize = 2048;
	static constexpr unsigned int bitMod = 10000;
	static constexpr unsigned int bitShift = 4;
	unsigned int n;
	unsigned int arr[maxSize]{};
public:
	explicit Integer(long long integer = 0)
	{
		n = 1;
		for (unsigned int& i : arr)
		{
			i = integer % bitMod;
			integer /= bitMod;
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
	Integer operator+(const Integer& other) const
	{
		Integer ans;
		int top = (int)std::max(other.n, n);
		ans.n = top + 1;
		ans.arr[0] = 0;
		for (int i = 0; i < top; i++)
		{
			ans.arr[i + 1] = (ans.arr[i] + arr[i] + other.arr[i]) / bitMod;
			ans.arr[i] = (ans.arr[i] + arr[i] + other.arr[i]) % bitMod;
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
				ans.arr[i + j + 1] += ans.arr[i + j] / bitMod;
				ans.arr[i + j] %= bitMod;
			}
		}
		while (ans.arr[ans.n - 1] == 0 && ans.n > 1)
		{
			ans.n -= 1;
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
	Integer operator%(const Integer& other) const
	{
		if (*this < other)
		{
			return *this;
		}
		Integer ans;

		return ans;
	}
	Integer& operator=(long long other)
	{
		n = 1;
		for (unsigned int& i : arr)
		{
			i = other % bitMod;
			other /= bitMod;
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
	Integer& operator*=(long long other)
	{
		n += 5;
		for (int i = 0; i < n; i++)
		{
			arr[i] *= other;
		}
		for (int i = 0; i < n; i++)
		{
			arr[i + 1] += arr[i] / bitMod;
			arr[i] %= bitMod;
		}
		while (arr[n - 1] == 0 && n > 1)
		{
			n -= 1;
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
			arr[i + 1] += arr[i] / bitMod;
			arr[i] %= bitMod;
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
				ans.arr[i + j + 1] += ans.arr[i + j] / bitMod;
				ans.arr[i + j] %= bitMod;
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
		unsigned int len = (int)str.length();
		x.n = len / bitShift + 1;
		for (unsigned int i = 0, h = len / 2; i < h; i++)
		{
			std::swap(str[i], str[len - i - 1]);
		}
		for (unsigned int i = 0, j = 1, k = 0; i < len; i++, j *= 10)
		{
			if (j == bitMod)
			{
				j = 1;
				k += 1;
			}
			x.arr[k] = x.arr[k] + (str[i] ^ 48) * j;
		}
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, Integer& x)
	{
		out << x.arr[x.n - 1];
		for (int i = (int)x.n - 2; i >= 0; i--)
		{
			for (int j = bitMod / 10; j >= 1; j /= 10)
			{
				out << x.arr[i] / j % 10;
			}
		}
		return out;
	}
	static Integer Pow(Integer a, unsigned int b)
	{
		Integer ans(1);
		while (b != 0)
		{
			if (b & 1)
			{
				ans *= a;
			}
			a *= a;
			b >>= 1;
		}
		return ans;
	}
};

class Solution
{
private:
	int k;
	int cnt;
	int* r;
	int* p;
	Integer* m;
public:
	explicit Solution(int kk)
	{
		k = kk;
		cnt = 0;
		r = new int[k];
		p = new int[k];
		m = new Integer[k];
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

	int Solve()
	{
		for (int i = 0; i < k; i++)
		{
			m[i] = 1;
			for (int j = 0; j < k; j++)
			{
				if (i != j)
				{
					m[i] *= p[i];
				}
			}
			#ifdef DEBUG
			std::cout << "/*****************/" << std::endl;
			std::cout << "m[" << i << "] = " << m[i] << std::endl;
			std::cout << "/*****************/" << std::endl;
			#endif
		}
		Integer ans(0);
		for (int i = 0; i < k; i++)
		{
			ans += Integer::Pow(m[i], p[i] - 2);
		}
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
	std::cout << solution.Solve();
	return 0;
}