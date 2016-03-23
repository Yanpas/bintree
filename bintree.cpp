#include "bintree.hpp"

Node::Node(int x): val(x)
{
	
}

Node::~Node()
{
	if (left != nullptr) delete left;
	if (right != nullptr) delete right;
}



BinTree::BinTree()
{
	
}

BinTree::BinTree(std::initializer_list<int> inlist)
{
	if (inlist.size()==0) return;
	root = new Node(*inlist.begin());
	for (auto& el : inlist)
		insert(el);
}

BinTree::~BinTree()
{
	delete root;
}

BinTree::BinTree(BinTree && rhl)
{
	root = rhl.root;
	rhl.root = nullptr;
}

BinTree::BinTree(const BinTree & rhl)
{
//	root = new Node(rhl.root->val);
//	copy (rhl.root->left, root->left);
//	copy (rhl.root->right, root->right);
	copy (rhl.root, root);
}

BinTree& BinTree::operator= (BinTree&& rhl)
{
	root = rhl.root;
	rhl.root = nullptr;
	return *this;
}

BinTree& BinTree::operator= (const BinTree & rhl)
{
	copy (rhl.root, root);
	return *this;
}

void BinTree::operator+=(std::initializer_list<int> list)
{
	for (auto el : list)
		this->insert(el);
}

void BinTree::print() const
{
	if (root==nullptr) {std::cout << "Empty tree\n"; return;}
	std::cout << root->val << std::endl;
	if(root->left) print(root->left,1);
	if(root->right) print(root->right,1);
}

void BinTree::print(Node * nd, int spaces) const
{
	std::cout << std::string(spaces,':');
	std::cout << nd->val << std::endl;
	if (nd->left==nullptr and nd->right==nullptr) return;
	if(nd->left) print(nd->left,spaces+1);
	else std::cout << std::string(spaces+1,':') << std::endl;
	if (nd->right) print(nd->right,spaces+1);
	else std::cout << std::string(spaces+1,':') << std::endl;	
}

void BinTree::copy(Node * const & from, Node *& to)
{
	if (from == nullptr) return;
	to = new Node(from->val);
	copy ( from->left, to->left );
	copy ( from->right, to->right );
}

void BinTree::insert (int x)
{
	if (root==nullptr) root = new Node(x);
	else insert (this->root, x);
}

void BinTree::insert (Node * nd, int x)
{
	if (x > nd->val)
	{
		if(nd->right) insert(nd->right, x);
		else nd->right = new Node(x);
	}
	if (x < nd->val)
	{
		if(nd->left) insert(nd->left, x);
		else nd->left = new Node(x);
	}
}

Node *& BinTree::search(int x)
{
	return search(x, root);
}

Node *& BinTree::search(int x, Node *& nd)
{
	Node *& fndl = nullnode;
	Node *& fndr = nullnode;
	if ( nd->val == x ) return nd;
	if ( nd->val < x && nd->right!=nullptr) fndr = search(x, nd->right) ;
	if ( nd->val > x && nd->left!=nullptr) fndl = search(x, nd->left) ;
	
	if (fndl==nullptr and fndr == nullptr) {std::cerr << "Not found\n"; return nullnode;}
	return fndr ? fndr : fndl;
}

Node * BinTree::search_min_right(Node * nd)
{
	if (nd == nullptr) return nullptr;
	if ( nd->left == nullptr ) return nd;
	return search_min_right(nd->left);
}

Node * BinTree::search_max_left(Node * nd)
{
	if (nd == nullptr) return nullptr;
	if ( nd->right == nullptr ) return nd;
	return search_max_left(nd->right);
}

std::pair<Node *, Direction> BinTree::search_parent(int x, Node * nd)
{
	if ( nd->left and nd->left->val == x ) return std::make_pair(nd, Direction::left);
	if ( nd->right and nd->right->val == x ) return std::make_pair(nd, Direction::right);
	if ( nd->val < x ) return nd->right ? search_parent(x, nd->right) : std::make_pair(nullptr, Direction::left);
	if ( nd->val > x ) return nd->left ? search_parent(x, nd->left) : std::make_pair(nullptr, Direction::left);
	
	std::cerr << "Parent not found\n";
	return std::make_pair(nullptr, Direction::left);
}

int BinTree::size() const
{
	int s = root ? 1 +size(root->left)+size(root->right) : 0;
	return s;
}

int BinTree::size(Node * nd) const
{
	return nd ? 1+size(nd->left)+size(nd->right) : 0;
}

int BinTree::maxdepth() const
{
	return maxdepth(root,0);
	 
}

int BinTree::maxdepth(Node * nd, int level) const
{
	if (nd==nullptr) return level;
	int l = maxdepth(nd->left, level+1);
	int r = maxdepth(nd->right, level+1);
	return l > r ? l : r;
	 
}

int BinTree::mindepth() const
{
	return mindepth(root, 1);
}

int BinTree::mindepth(Node * nd, int level) const
{
	if (nd->left==nullptr and nd->right==nullptr) return level;
	int l = nd->left ? mindepth(nd->left, level+1) : -1;
	int r = nd->right ? mindepth(nd->right, level+1) : -1;
	if (l==-1) return r;
	if (r==-1) return l;
	return l < r ? l : r;
}


bool BinTree::isBalanced() const
{
	return maxdepth()-mindepth() > 1 ? false : true;
}

void BinTree::delnode(int x)
{
	Node*& nd = search(x,root);
	std::pair<Node *, Direction> par = search_parent(x,root);
	auto erase_child_with_1_child = 
		[](std::pair<Node *, Direction> par, Direction nd_ch)
		{
			if(par.second==Direction::right)
			{
				if (nd_ch == Direction::left)
				{
					Node * tmp = par.first->right;
					par.first->right = par.first->right->left;
					tmp->left=nullptr;
					delete tmp;
				}
				else if (nd_ch == Direction::right)
				{
					Node * tmp = par.first->right;
					par.first->right = par.first->right->right;
					tmp->right=nullptr;
					delete tmp;
				}
			}
			else if (par.second==Direction::left)
			{
				{
				if (nd_ch == Direction::left)
				{
					Node * tmp = par.first->left;
					par.first->left = par.first->left->left;
					tmp->left=nullptr;
					delete tmp;
				}
				else if (nd_ch == Direction::right)
				{
					Node * tmp = par.first->left;
					par.first->left = par.first->left->right;
					tmp->right=nullptr;
					delete tmp;
				}
			}
			}
		};
	if (nd == nullptr) return;
	if (nd->left==nullptr and nd->right==nullptr)
	{
		if (par.first != nullptr)
		{
			if (par.second == Direction::left) par.first->left=nullptr;
			else if (par.second == Direction::right) par.first->right=nullptr;
		}
		nd = nullptr;
		delete nd;
	}
	else if (nd->left==nullptr)
	{
		if(par.first == nullptr)
		{
			Node*tmp = nd;
			nd = nd->right;
			tmp->right = nullptr;
			delete tmp;
			return;
		}
		erase_child_with_1_child(par, Direction::right);
	}
	else if (nd->right==nullptr)
	{
		if(par.first == nullptr)
		{
			Node*tmp = nd;
			nd = nd->left;
			tmp->left = nullptr;
			delete tmp;
			return;
		}
		erase_child_with_1_child(par, Direction::left);
	}
	else
	{
		Node * minr = search_min_right(nd->right);
		if (minr == nd->right)
		{
			nd->val= nd->right->val;
			erase_child_with_1_child (std::make_pair(nd, Direction::right), Direction::right);
			return;
		}
		nd->val=minr->val;
		auto minr_par = search_parent(minr->val, nd->right);
		minr_par.first->left=minr->right;
		minr->right=nullptr;
		delete minr;
	}
	
}

void BinTree::rotate(Node * nd, Direction d)
{
	
}

bool BinTree::isBST() const
{
	
}

bool BinTree::isBST(Node * nd) const
{
	
}