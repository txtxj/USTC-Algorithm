#include <iostream>

class BlackRedTree
{
private:
	enum Color {black, red};
	struct Node
	{
		int val;
		int siz;
		Node* left;
		Node* right;
		Node* parent;
		Color color;
	};
	Node* nil;
	Node* root;
	void LeftRotate(Node* p)
	{
		if (p == nil) return;
		Node* r = p -> right;
		p -> right = r -> left;
		if (r -> left != nil)
		{
			r -> left -> parent = p;
		}
		r -> parent = p -> parent;
		if (p -> parent == nil)
		{
			root = r;
		}
		else if (p == p -> parent -> left)
		{
			p -> parent -> left = r;
		}
		else
		{
			p -> parent -> right = r;
		}
		r -> left = p;
		r -> siz = p -> siz;
		p -> parent = r;
		p -> siz = p -> left -> siz + p -> right -> siz + 1;
	}
	void RightRotate(Node* p)
	{
		if (p == nil) return;
		Node* l = p -> left;
		p -> left = l -> right;
		if (l -> right != nil)
		{
			l -> right -> parent = p;
		}
		l -> parent = p -> parent;
		if (p -> parent == nil)
		{
			root = l;
		}
		else if (p == p -> parent -> left)
		{
			p -> parent -> left = l;
		}
		else
		{
			p -> parent -> right = l;
		}
		l -> right = p;
		l -> siz = p -> siz;
		p -> parent = l;
		p -> siz = p -> left -> siz + p -> right -> siz + 1;
	}
	void InsertFixUp(Node* z)
	{
		Node* y;
		while (z -> parent -> color == red)
		{
			if (z -> parent == z -> parent -> parent -> left)
			{
				y = z -> parent -> parent -> right;
				if (y -> color == red)
				{
					z -> parent -> color = black;
					y -> color = black;
					z -> parent -> parent -> color = red;
					z = z -> parent -> parent;
				}
				else
				{
					if (z == z -> parent -> right)
					{
						z = z -> parent;
						LeftRotate(z);
					}
					z -> parent -> color = black;
					z -> parent -> parent -> color = red;
					RightRotate(z -> parent -> parent);
				}
			}
			else
			{
				y = z -> parent -> parent -> left;
				if (y -> color == red)
				{
					z -> parent -> color = black;
					y -> color = black;
					z -> parent -> parent -> color = red;
					z = z -> parent -> parent;
				}
				else
				{
					if (z == z-> parent -> left) {
						z = z -> parent;
						RightRotate(z);
					}
					z -> parent -> color = black;
					z -> parent -> parent -> color = red;
					LeftRotate(z -> parent -> parent);
				}
			}
		}
		root -> color = black;
	}
	void InsertNode(Node* z)
	{
		Node* y = nil;
		Node* x = root;
		while (x != nil)
		{
			y = x;
			y -> siz += 1;
			if (z -> val < x -> val)
			{
				x = x -> left;
			}
			else
			{
				x = x -> right;
			}
		}
		z -> parent = y;
		if (y == nil)
		{
			root = z;
		}
		else if (z -> val < y -> val)
		{
			y -> left = z;
		}
		else
		{
			y -> right = z;
		}
		InsertFixUp(z);
	}
	Node* Minimum(Node* x)
	{
		while (x -> left != nil)
		{
			x = x -> left;
		}
		return x;
	}
	void Transplant(Node* u, Node* v)
	{
		if (u -> parent == nil)
		{
			root = v;
		}
		else if (u == u -> parent -> left)
		{
			u -> parent -> left = v;
		}
		else
		{
			u -> parent -> right = v;
		}
		v -> parent = u -> parent;
	}
	void DeleteFixUp(Node* x)
	{
		Node* w;
		while (x != root && x -> color == black)
		{
			if (x == x -> parent -> left)
			{
				w = x -> parent -> right;
				if (w -> color == red)
				{
					w -> color = black;
					x -> parent -> color = red;
					LeftRotate(x -> parent);
					w = x -> parent -> right;
				}
				if (w -> left -> color == black && w -> right -> color == black)
				{
					w -> color = red;
					x = x -> parent;
				}
				else
				{
					if (w -> right -> color == black)
					{
						w -> left -> color = black;
						w -> color = red;
						RightRotate(w);
						w = x -> parent -> right;
					}
					w -> color = x -> parent -> color;
					x -> parent -> color = black;
					w -> right -> color = black;
					LeftRotate(x -> parent);
					x = root;
				}
			}
			else
			{
				w = x -> parent -> left;
				if (w -> color == red)
				{
					w -> color = black;
					x -> parent -> color = red;
					RightRotate(x -> parent);
					w = x -> parent -> left;
				}
				if (w -> right -> color == black && w -> left -> color == black)
				{
					w -> color = red;
					x = x -> parent;
				}
				else
				{
					if (w -> left -> color == black)
					{
						w -> right -> color = black;
						w -> color = red;
						LeftRotate(w);
						w = x -> parent -> left;
					}
					w -> color = x -> parent -> color;
					x -> parent -> color = black;
					w -> left -> color = black;
					RightRotate(x -> parent);
					x = root;
				}
			}
		}
		x -> color = black;
	}
	void DeleteNode(Node* z)
	{
		Node* y = z;
		Node* x;
		Node* f;
		Color yc = y -> color;
		if (z -> left == nil)
		{
			f = x = z -> right;
			Transplant(z, x);
		}
		else if (z -> right == nil)
		{
			f = x = z -> left;
			Transplant(z, x);
		}
		else
		{
			y = Minimum(z -> right);
			yc = y -> color;
			f = y -> parent;
			x = y -> right;
			if (y -> parent == z)
			{
				x -> parent = y;
			}
			else
			{
				Transplant(y, x);
				y -> right = z -> right;
				y -> right -> parent = y;
			}
			Transplant(z, y);
			y -> left = z -> left;
			y -> left -> parent = y;
			y -> color = z -> color;
		}
		nil -> siz = 0;
		if (f == nil)
		{
			f = z -> parent;
		}
		while (f != nil)
		{
			f -> siz = f -> left -> siz + f -> right -> siz + 1;
			f = f -> parent;
		}
		if (yc == black)
		{
			DeleteFixUp(x);
		}
	}
	Node* Find(int val)
	{
		Node* x = root;
		while (x != nil && val != x -> val)
		{
			if (val < x -> val)
			{
				x = x -> left;
			}
			else if (val > x -> val)
			{
				x = x -> right;
			}
		}
		return x;
	}
	int Findkth(Node* z, int k)
	{
		if (z == nil) return -1;
		if (k <= z -> right -> siz)
		{
			return Findkth(z -> right, k);
		}
		else if (k == z -> right -> siz + 1)
		{
			return z -> val;
		}
		else
		{
			return Findkth(z -> left, k - z -> right -> siz - 1);
		}
	}
	Node* FindPre(int val)
	{
		Node* x = root;
		Node* pre = nil;
		while (x != nil)
		{
			if (x -> val <= val)
			{
				pre = x;
				x = x -> right;
			}
			else
			{
				x = x -> left;
			}
		}
		return pre;
	}
	Node* FindNext(int val)
	{
		Node* x = root;
		Node* nxt = nil;
		while (x != nil)
		{
			if (x -> val >= val)
			{
				nxt = x;
				x = x -> left;
			}
			else
			{
				x = x -> right;
			}
		}
		return nxt;
	}
	int GetRank(Node* z, int val)
	{
		if (z == nil) return 0;
		if (val == z -> val)
		{
			return z -> left -> siz + 1;
		}
		else if (val < z -> val)
		{
			return GetRank(z -> left, val);
		}
		else
		{
			return z -> left -> siz + 1 + GetRank(z -> right, val);
		}
	}
public:
	BlackRedTree()
	{
		nil = new Node{0, 0, nullptr, nullptr, nullptr, black};
		nil -> left = nil -> right = nil -> parent = nil;
		root = nil;
	}
	void Insert(int val)
	{
		Node* z = new Node{val, 1, nil, nil, nil, red};
		InsertNode(z);
		DebugPrintTree();
	}
	void Delete(int val)
	{
		Node* x = Find(val);
		DeleteNode(x);
		DebugPrintTree();
	}
	int Findkth(int k)
	{
		DebugPrintTree();
		return Findkth(root, k);
	}
	int UpperBound(int val)
	{
		DebugPrintTree();
		return FindNext(val) -> val;
	}
	int Count(int l, int r)
	{
		Node* pre = FindPre(r);
		Node* nxt = FindNext(l);
		DebugPrintTree();
		if (pre == nil || nxt == nil)
		{
			return 0;
		}
		return GetRank(root, pre -> val) - GetRank(root, nxt -> val) + 1;
	}
	#ifdef DEBUG
	static void DebugPrintMessage(Node* p)
	{
		std::cout << "val: " << p -> val << " siz: " << p -> siz << " color: " << (p -> color ? "R" : "B") << std::endl;
	}
	void DebugPrintNode(Node* p, int step, int valid, bool right)
	{
		if (p == nil) return;
		for (int i = 0; i < step; i++)
		{
			std::cout << ((valid & (1 << (i - 1))) == 0 ? "   ": "│  ");
		}
		std::cout << (right ? "└ " : "├ ");
		DebugPrintMessage(p);
		DebugPrintNode(p -> left, step + 1, valid | (1 << step), p -> right == nil);
		DebugPrintNode(p -> right, step + 1, valid & ~(1 << step), true);
	}
	#endif
	void DebugPrintTree()
	{
		#ifdef DEBUG
		std::cout << "/******************/" << std::endl << "TREE" << std::endl;
		DebugPrintNode(root, 0, 0, true);
		std::cout << "/******************/" << std::endl;
		#endif
	}
};

class Solution
{
private:
	BlackRedTree brt;
public:
	void HandleInstruction()
	{
		char op = ' ';
		int x, y;
		while (op == ' ' || op == '\n' || op == '\r')
		{
			std::cin >> op;
		}
		switch (op)
		{
			case 'I':
				std::cin >> x;
				brt.Insert(x);
				break;
			case 'D':
				std::cin >> x;
				brt.Delete(x);
				break;
			case 'S':
				std::cin >> x;
				std::cout << brt.Findkth(x) << std::endl;
				break;
			case 'L':
				std::cin >> x;
				std::cout << brt.UpperBound(x) << std::endl;
				break;
			case 'T':
				std::cin >> x >> y;
				std::cout << brt.Count(x, y) << std::endl;
				break;
			default:
				break;
		}
	}
};

Solution solution;

int main()
{
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		solution.HandleInstruction();
	}
	return 0;
}