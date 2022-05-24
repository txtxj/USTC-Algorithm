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
	Integer operator+(Integer& other) const
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
	Integer operator*(Integer& other) const
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

	int Solve()
	{
		return r[0];
	}
};

int main()
{
	//#ifdef BIGINTDEBUG
	Integer x, y;
	std::cin >> x >> y;
	std::cout << x << std::endl << y;
	Integer z = x + y;
	std::cout << z << std::endl;
	Integer w = x * y;
	std::cout << w << std::endl;
	return 0;
	//#endif
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