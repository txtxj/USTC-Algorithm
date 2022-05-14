#include <vector>
#include <queue>
#include <iostream>
#include <limits>

constexpr int maxInt = std::numeric_limits<int>::max();

class Graph
{
private:
	class Edge
	{
	public:
		int to;
		int val;
	public:
		Edge(int _to, int _val) : to(_to), val(_val) {}
		~Edge() = default;
	};
	class Node
	{
	public:
		int index;
		int dis;
	public:
		Node(int _index, int _dis = maxInt) : index(_index), dis(_dis) {}
		~Node() = default;
		bool operator<(Node other) const
		{
			return dis > other.dis;
		}
	};
	int v;
	std::vector<Edge>* edge;
	std::priority_queue<Node> heap;
	bool* vis;
	int* dis;
	int** longest;
	bool** inTree;
	int* pre;
	int mst;
private:
	void AddEdge(int from, int to, int val)
	{
		edge[from].emplace_back(to, val);
		#ifdef DEBUG
		std::cout << "Add edge (" << from << ", " << to << ", " << val << ")" << std::endl;
		#endif
	}
	void Prim()
	{
		while (!heap.empty())
		{
			heap.pop();
		}
		for (int i = 0; i < v; i++)
		{
			vis[i] = false;
			dis[i] = maxInt;
		}
		int cnt = 1;
		mst = 0;
		heap.push(Node(1, 0));
		dis[1] = 0;

		while (!heap.empty() && cnt < v)
		{
			int j = heap.top().index;
			int d = heap.top().dis;
			#ifdef DEBUG
			std::cout << "/******************/" << std::endl;
			std::cout << "heap.top = (" << j << ", " << d << ")" << std::endl;
			std::cout << "/******************/" << std::endl;
			#endif
			heap.pop();
			if (!vis[j])
			{
				vis[j] = true;
				cnt += 1;
				mst += d;
				inTree[pre[j]][j] = inTree[j][pre[j]] = true;
				for (int i = 1; i < v; i++)
				{
					if (vis[i] && i != j)
					{
						longest[j][i] = longest[i][j] = std::max(longest[pre[j]][i], d);
					}
				}
				for (Edge& u : edge[j])
				{
					if (u.val < dis[u.to])
					{
						dis[u.to] = u.val;
						heap.push(Node(u.to, u.val));
						#ifdef DEBUG
						std::cout << "/******************/" << std::endl;
						std::cout << "heap.push(" << u.to << ", " << u.val << ")" << std::endl;
						std::cout << "/******************/" << std::endl;
						#endif
						pre[u.to] = j;
					}
				}
			}
		}
	}
public:
	explicit Graph(int _v)
	{
		v = _v + 1;
		edge = new std::vector<Edge>[v];
		vis = new bool[v];
		dis = new int[v];
		longest = new int*[v];
		inTree = new bool*[v];
		pre = new int[v];
		for (int i = 0; i < v; i++)
		{
			longest[i] = new int[v];
			inTree[i] = new bool[v];
		}
		mst = 0;
	}
	~Graph()
	{
		delete[] edge;
		delete[] dis;
		delete[] vis;
		for (int i = 1; i < v; i++)
		{
			delete[] longest[i];
			delete[] inTree[i];
		}
		delete[] longest;
		delete[] inTree;
		delete[] pre;
	}
	void AddEdge(std::istream& in, int edgeCount)
	{
		int a, b, c;
		for (int i = 0; i < edgeCount; i++)
		{
			in >> a >> b >> c;
			AddEdge(a, b, c);
			AddEdge(b, a, c);
		}
	}

	void Solve(std::ostream& out)
	{
		Prim();
		out << mst << std::endl;
		int df = maxInt;
		#ifdef DEBUG
		std::cout << "/******************/" << std::endl;
		for (int i = 1; i < v; i++)
		{
			for (int j = 1; j < v; j++)
			{
				out << "longest[" << i << "][" << j << "] = " << longest[i][j] << std::endl;
			}
		}
		std::cout << "/******************/" << std::endl;
		#endif
		for (int i = 1; i < v; i++)
		{
			for (Edge& p : edge[i])
			{
				if (!inTree[i][p.to])
				{
					df = std::min(df, p.val - longest[i][p.to]);
				}
			}
		}
		out << mst + df << std::endl;
	}
};

int main()
{
	int n, m;
	std::cin >> n >> m;
	Graph graph(n);
	graph.AddEdge(std::cin, m);
	graph.Solve(std::cout);
	return 0;
}