#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>

template<typename ItemType>
void DynamicArray<ItemType>::pop_back()
{
	if(size > 0)
	{
		size--;
		data[size] = ItemType();
	}
}
template<typename ItemType>
unsigned int DynamicArray<ItemType>::getSize() const
{
	return size;
}
template<typename ItemType>
int DynamicArray<ItemType>::getCapacity() const
{
	return capacity;
} 
template <typename ItemType>
DynamicArray<ItemType>::DynamicArray()
{
	size = 0;
	capacity = 0;
	data = nullptr;
}
template <typename ItemType>
DynamicArray<ItemType>::DynamicArray(int capacity)
{
	size = 0;
	this->capacity = capacity;
	data = new ItemType[capacity];
}	
template<typename ItemType>
DynamicArray<ItemType>::~DynamicArray()
{
	delete[] data;
}
template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const DynamicArray &other)
{	
	size = other.size;
	capacity = other.capacity;
	data = new ItemType[capacity];
	for(int i = 0; i < other.size; i++)
	{
		data[i] = other.data[i];
	}
}
template <typename ItemType>
void DynamicArray<ItemType>::push_back(ItemType add)
{
	if(this->capacity == 0)
	{
		capacity = 1;
		data = new ItemType[capacity];
	}

 	if (size == capacity) {
       		int newCapacity = 2 * capacity;
		ItemType* arr = new ItemType[newCapacity];
		for(int i = 0; i < size; i++)
		{
			arr[i] = data[i];
		}
		delete[] data;
		data = arr;
		capacity = newCapacity;
    	}
  	int pos = 0;
  	while (pos < size && data[pos] < add)
    	{
        	pos++;
    	}
    	for (int i = size; i > pos; i--) {
        	data[i] = data[i - 1];
    	}
    	data[pos] = add;
    	size++;
}	
template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray &other)
{
	if(this == &other)
	{
		return *this;
	}
	delete[] data;
	size = other.size;
	capacity = other.capacity;
	data = new ItemType[capacity];
	for(int i = 0; i < other.size; i++)
	{
		data[i] = other.data[i];
	}
	return *this;
}
template <typename ItemType>
ItemType& DynamicArray<ItemType>::operator[](int index)
{
	if((index >= 0) && (index < size))
	{
		return data[index];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}
template<typename ItemType>
const ItemType& DynamicArray<ItemType>::operator[](int index) const 
{
		if((index >= 0) && (index < size))
		{
			return data[index];	
		}
		else
		{
			throw std::out_of_range("Index out of range");
		}
}
template <typename ItemType>
void DynamicArray<ItemType>::remove(ItemType obj)
{
	for(int i = 0; i < size; i++)
	{
		if(data[i] == obj)
		{
			for(int j = i; j < size - 1; j++)
			{
				data [j] = data[j+1];
			}
			size -= 1;
			if(size < capacity)
			{
				data[size] = ItemType();
			}
			break;
		}
	}
}
