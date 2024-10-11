#pragma once

#include"RBtree.h"
namespace mmap {
	template<class K,class V>
	class Mymap
	{
	public:
		struct keyofmap
		{
			const K& operator()(const pair<K,V>& kv)
			{
				return kv.first;
			}
		};
		typedef typename RBTree<K, pair<K, V>, keyofmap>::iterator iterator;
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		bool insert(const pair<K,V>& kv)
		{
			return _t.insert(kv);
		}
		void inorder()
		{
			_t.inorder();
		}
	private:
		RBTree<K,pair<K,V>,keyofmap> _t;
	};


}

