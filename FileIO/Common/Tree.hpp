#pragma once
#include "Common.h"

#ifndef TREE_HPP
#define TREE_HPP

namespace FileIO::Common {
	template <typename TValue>
	class TNode 
	{
		TNode() {}
		TNode(TValue val) : value(val){}
		~TNode() {}

		TNode<TValue>& parent;
		std::vector<TNode<TValue>*> Children;

		inline TValue GetValue() { return value; }
		inline TValue SetValue(TValue val) { return value = val; }
		inline TValue Append();

	private:
		BurpPointer<TValue> value;
	};

}
#endif // !TREE_HPP
