#ifndef BTREE_H
#error "double inclusion"
#endif /* BTREE_H */

void BTree::insert()
{
	
}

template <typename Arg1, typename... Args>
void BTree::insert (Arg1 a1, Args... a)
{
	insert (this->cur, a1);
	insert(a...);
}

void BTree::insert (Node * nd, int x)
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