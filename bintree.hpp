#ifndef BinTree_H
#define BinTree_H

#include <initializer_list>
#include <iostream>
#include <string>

enum class Direction
{
	left,
	right
};

struct Node
{
	int val;
	Node * left = nullptr;
	Node * right = nullptr;
	Node(int x=0);
	virtual ~Node();
};

class BinTree
{
  public:
	BinTree();
	BinTree(Node *nd) = delete;
	BinTree(std::initializer_list<int> list);
	virtual ~BinTree();
	BinTree(BinTree &&);
	BinTree(const BinTree &);
	
	BinTree& operator= (BinTree&&);
	BinTree& operator= (const BinTree&);
	void operator+=(std::initializer_list<int> list);
		
	void insert (int x);
	void print() const;
	Node * search(int x);
	Node * search(int x, Node * nd);
	int size() const;
	int maxdepth() const;
	int mindepth() const;
	bool isBalanced() const;
	void delnode(int x);
	void rotate(Node * nd, Direction d);
	bool isBST() const;
	friend Node * getroot(BinTree& name)
	{
		return name.root;
	}
	
  private:
	Node * root=nullptr;
	void insert (Node * nd, int x);
	void print(Node * nd, int spaces) const;
	void copy(Node * const & from, Node * & to);
	int size(Node * nd) const;
	int maxdepth(Node * nd, int level) const;
	int mindepth(Node * nd, int level) const;
	Node * search_min_right(Node * nd);
	Node * search_max_left(Node * nd);
	std::pair<Node *, Direction> search_parent(int x, Node * nd);
	bool isBST(Node * nd) const;
};



//#include "BinTree.tcc"

#endif /* BinTree_H */ 
