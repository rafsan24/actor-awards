#ifndef __DYNAMICARRAY_H
#define __DYNAMICARRAY_H

#include <iostream>

using namespace std;

template <typename ItemType>
class DynamicArray
{
	public:
		DynamicArray();
		DynamicArray(int capacity);
		DynamicArray& operator=(const DynamicArray &other);
		~DynamicArray();
		DynamicArray(const DynamicArray &other);
		ItemType& operator[](int index);
		const ItemType& operator[](int index) const;
		void remove(ItemType obj);
		unsigned int getSize() const;
		void push_back(ItemType add);
		void pop_back();
		int getCapacity() const;
	private:
		ItemType* data = nullptr; 
		int capacity = 0;
		int size = 0;
};
#include "DynamicArray.cpp"
#endif 
