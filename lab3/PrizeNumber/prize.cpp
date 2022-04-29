#include <iostream>

class Solution
{
private:
	int n;
	long long* a;
	long long* temp;
	long long* tempOrder;
	long long* tempReverse;
	long long* orderHead;
	long long* reverseDf;
private:
	#ifdef DEBUG
	static void Print(long long* array, int l, int r)
	{
		int mid = (l + r) >> 1;
		while (l <= r)
		{
			if (l == mid + 1)
			{
				std::cout << "|\t";
			}
			std::cout << array[l] << "\t";
			l += 1;
		}
		std::cout << std::endl;
	}
	#endif
	long long MergeSort(int l, int r)
	{
		if (l == r) return 0;
		int mid = (l + r) >> 1;
		long long sum = MergeSort(l, mid) + MergeSort(mid + 1, r);
		long long cnt = 0;
		int i, j, p;
		#ifdef DEBUG
		std::cout << "/******************/" << std::endl;
		Print(a, l, r);
		Print(orderHead, l, r);
		Print(reverseDf, l, r);
		#endif
		for (p = l, i = l, j = mid + 1; i <= mid && j <= r; p += 1)
		{
			if (a[i] <= a[j])
			{
				temp[p] = a[i];
				tempOrder[p] = orderHead[i] + r - j + 1;
				tempReverse[p] = reverseDf[i] + j - 1 - mid;
				cnt += orderHead[i] * (j - mid - 1);
				i += 1;
			}
			else
			{
				temp[p] = a[j];
				tempOrder[p] = orderHead[j];
				tempReverse[p] = reverseDf[j] + i - 1 - mid;
				cnt += reverseDf[j] * (i - l);
				j += 1;
			}
		}
		while (i <= mid)
		{
			temp[p] = a[i];
			tempOrder[p] = orderHead[i];
			tempReverse[p] = reverseDf[i] + r - mid;
			cnt += orderHead[i] * (r - mid);
			i += 1;
			p += 1;
		}
		while (j <= r)
		{
			temp[p] = a[j];
			tempOrder[p] = orderHead[j];
			tempReverse[p] = reverseDf[j];
			cnt += reverseDf[j] * (mid + 1 - l);
			j += 1;
			p += 1;
		}
		while (l <= r)
		{
			a[l] = temp[l];
			orderHead[l] = tempOrder[l];
			reverseDf[l] = tempReverse[l];
			l += 1;
		}
		#ifdef DEBUG
		std::cout << "sum += " << cnt << std::endl;
		std::cout << "/******************/" << std::endl;
		#endif
		return sum + cnt;
	}
public:
	explicit Solution(int nn)
	{
		n = nn;
		a = new long long[n];
		temp = new long long[n];
		tempOrder = new long long[n];
		tempReverse = new long long[n];
		orderHead = new long long[n];
		reverseDf = new long long[n];
	}
	~Solution()
	{
		delete[] temp;
		delete[] tempOrder;
		delete[] tempReverse;
		delete[] orderHead;
		delete[] reverseDf;
	}
	void ReadLine(std::istream& in)
	{
		for (int i = 0; i < n; i++)
		{
			in >> a[i];
			tempOrder[i] = tempReverse[i] = orderHead[i] = reverseDf[i] = 0;
		}
	}
	long long Solve()
	{
		return MergeSort(0, n - 1);
	}
};

int main()
{
	int n;
	std::cin >> n;
	Solution solution = Solution(n);
	solution.ReadLine(std::cin);
	std::cout << solution.Solve();
	return 0;
}