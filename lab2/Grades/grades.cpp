#include <iostream>
#include <algorithm>
#include <cstring>

#define TABLE_MAX 15000000
#define HEAP_MAX 700050
#define NAME_MAX 1000

class Solution
{
private:
	int siz = 0, cnt = 0;
	int table[TABLE_MAX] = {};
	std::string bullet[NAME_MAX] = {};
	struct Student
	{
		std::string name;
		int score{};
	};
	Student heap[HEAP_MAX];
	friend bool operator<(const Student& a, const Student& b)
	{
		return a.score < b.score;
	}
private:

	static int HashName(const std::string& name)
	{
		int ans = 0;
		for (auto p : name)
		{
			ans = ans * 28 - 64 + p;
		}
		return ans;
	}

	int& GetIndex(const std::string& name)
	{
		return table[HashName(name)];
	}

	void MaxHeapify(int index)
	{
		int l = index << 1;
		int r = l + 1;
		int largest = index;
		if (l <= siz && !(heap[l] < heap[index]))
		{
			largest = l;
		}
		if (r <= siz && !(heap[r] < heap[largest]))
		{
			largest = r;
		}
		if (largest != index)
		{
			std::swap(heap[index], heap[largest]);
			GetIndex(heap[index].name) = index;
			GetIndex(heap[largest].name) = largest;
			MaxHeapify(largest);
		}
	}

	void DeleteStudent(const std::string& name)
	{
		if (GetIndex(name) > siz || GetIndex(name) == 0) return;
		heap[GetIndex(name)].score = __INT_MAX__;
		for (int i = GetIndex(name); i > 1; i = i >> 1)
		{
			std::swap(heap[i], heap[i >> 1]);
			GetIndex(heap[i].name) = i;
			GetIndex(heap[i >> 1].name) = i >> 1;
		}
		std::swap(heap[1], heap[siz]);
		GetIndex(heap[1].name) = 1;
		GetIndex(heap[siz].name) = 0;
		siz -= 1;
		MaxHeapify(1);
	}

	void InsertStudent(const std::string& name, int score)
	{
		siz += 1;
		heap[siz] = Student{name, score};
		GetIndex(name) = siz;
		for (int i = siz; i > 1 && heap[i >> 1] < heap[i]; i = i >> 1)
		{
			std::swap(heap[i], heap[i >> 1]);
			GetIndex(heap[i].name) = i;
			GetIndex(heap[i >> 1].name) = i >> 1;
		}
	}

	void PrintScore(const std::string& name)
	{
		std::cout << heap[GetIndex(name)].score << std::endl;
	}

	void PrintBest(int index)
	{
		if (index > siz) return;
		if (heap[index].score == heap[1].score)
		{
			bullet[cnt++] = heap[index].name;
			PrintBest(index << 1);
			PrintBest((index << 1) + 1);
		}
	}


public:
	void HandleInstruction()
	{
		char op = ' ';
		std::string name;
		int score;
		while (op == ' ' || op == '\n' || op == '\r') std::cin >> op;
		switch (op)
		{
			case 'I':
				std::cin >> name >> score;
				InsertStudent(name, score);
				break;
			case 'D':
				std::cin >> name;
				DeleteStudent(name);
				break;
			case 'S':
				std::cin >> name;
				PrintScore(name);
				break;
			case 'F':
				cnt = 0;
				PrintBest(1);
				std::sort(bullet, bullet + cnt);
				for (int i = 0; i < cnt; i++)
				{
					std::cout << bullet[i] << std::endl;
				}
				break;
			default:
				break;
		}
	}

	void Initiate()
	{
		std::memset(table, 0, sizeof table);
	}
};

Solution solution;

int main()
{
	int n;
	std::cin >> n;
	solution.Initiate();
	for (int i = 0; i < n; i++)
	{
		solution.HandleInstruction();
	}
	return 0;
}