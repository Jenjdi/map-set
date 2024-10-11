#pragma once
#include<iostream>

using namespace std;
enum Color
{
	BLACK,
	RED
};
template<typename T>
struct RBTreeNode
{
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	Color _col;
	T _val;
	RBTreeNode(const T& val)
		:_left(nullptr),
		_right(nullptr),
		_parent(nullptr),
		_col(RED),
		_val(val)
	{}
};
template<class T,class Ref,class Ptr>
struct _RBTree_Iterator
{
	typedef RBTreeNode<T> Node;
	typedef _RBTree_Iterator<T, Ref, Ptr> Self;
	Node* _node;
	_RBTree_Iterator(Node* node)
		:_node(node) 
	{}
	Ref operator* ()
	{
		return _node->_val;
	}
	Ptr operator-> ()
	{
		return &_node->_val;
	}
	bool operator != (const Self& s)
	{
		return _node != s._node;
	}
	Self& operator++()
	{
		if (_node->_right)
		{
			// 下一个，右树最左节点
			Node* leftMin = _node->_right;
			while (leftMin->_left)
			{
				leftMin = leftMin->_left;
			}

			_node = leftMin;
		}
		else
		{
			// 下一个，孩子等于父亲左的那个祖先
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return *this;
	}
};



template<class K, class key,class keyfoT>
class RBTree
{
	typedef RBTreeNode<key> node;
public:
	
	typedef _RBTree_Iterator<key,key&,key*> iterator;
	iterator begin()
	{
		node* leftMin=_root;
		if (leftMin && leftMin->_left)
		{
			leftMin = leftMin->_left;
		}
		return iterator(leftMin);
	}
	iterator end()
	{
		return iterator(nullptr);
	}
	bool insert(const key& k)
	{
		if (_root == nullptr)
		{
			_root = new node(k);
			_root->_col = BLACK;
			return true;
		}
		keyfoT _kot;
		node* parent = nullptr;
		node* cur = _root;
		while (cur)
		{
			// K
			// pair<K, V>
			// kot对象，是用来取T类型的data对象中的key
			if (_kot(cur->_val) < _kot(k))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (_kot(cur->_val) > _kot(k))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new node(k);
		cur->_col = RED; // 新增节点给红色
		if (_kot(parent->_val) < _kot(k))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_col == RED)
		{
			// 关键看叔叔
			node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				node* uncle = grandfather->_right;
				// 叔叔存在且为红，-》变色即可
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为黑
				{
					if (cur == parent->_left)
					{
						//     g  
						//   p   u
						// c 
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//      g  
						//   p     u
						//      c 
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
			else
			{
				node* uncle = grandfather->_left;
				// 叔叔存在且为红，-》变色即可
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为黑
				{
					// 情况二：叔叔不存在或者存在且为黑
					// 旋转+变色
					//      g
					//   u     p
					//            c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//		g
						//   u     p
						//      c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void RotateL(node* parent)
	{
		node* subR = parent->_right;
		node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		node* ppNode = parent->_parent;

		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_right == parent)
			{
				ppNode->_right = subR;
			}
			else
			{
				ppNode->_left = subR;
			}
			subR->_parent = ppNode;
		}
	}
	void RotateR(node* parent)
	{
		node* subL = parent->_left;
		node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;

		node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}
	}
	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}
private:
	node* _root = nullptr;
	void _inorder(node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_inorder(root->_left);
		std::cout << root->_val<<endl;
		_inorder(root->_right);
	}
};


