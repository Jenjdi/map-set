#pragma once
#include"RBtree.h"
namespace mset {
	template<class key>
	class Myset
	{
		struct keyofset
		{
			const key& operator()(const key& k)
			{
				return k;
			}
		};
	public:
		
		typedef typename RBTree<key, const key, keyofset>::iterator iterator;
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		bool insert(const key& k)
		{
			return _t.insert(k);
		}
		
	private:
		RBTree<key,const key,keyofset> _t;
	};

}