#pragma once
#ifndef _HEAD_H_
#define _HEAD_H_

#include <set>
#include <iostream>
#include <string>
using namespace std;

class SalesItem
{
private:
	std::string ISBN;
	unsigned UnitsSold;
	double Revenue;
public:
	SalesItem(){}
	SalesItem operator+(const SalesItem&);
	SalesItem& operator+=(const SalesItem&);
	friend std::ostream& operator<<(std::ostream&, const SalesItem&);
	friend std::istream& operator>>(std::istream&,  SalesItem&);
};

class Employee
{
public:
	Employee() :Name(""), ID(0) {}
	Employee(const Employee &arg) :Name(arg.Name), ID(arg.ID) {}
	~Employee()
	{
	}
	Employee operator=(const Employee &arg)
	{
		Name = arg.Name;
		ID = arg.ID;
	}
private:
	std::string Name;
	int ID;
};

class HasPtr
{
public:
	HasPtr(int *p,int i):ptr(p),val(i){}
	int *GetPtr() const
	{
		return ptr;
	}
	int GetInt()
	{
		return val;
	}
	void SetPtr(int *p)
	{
		ptr = p;
	}
	void SetInt(int i)
	{
		val = i;
	}

	HasPtr() :ptr(new int(0)), val(0) {}//默认构造函数
	~HasPtr()//析构函数
	{
		delete ptr;
	}
private:
	int *ptr, val;
};

class Screen
{
public :
	Screen(){}
};

class CheckedPtr
{
public:
	CheckedPtr(Screen *b, Screen *e) :beg(b), end(e), curr(b) {}
	CheckedPtr(const CheckedPtr& arg)  :beg(arg.beg), end(arg.end), curr(arg.curr) {}
	friend CheckedPtr operator+(const CheckedPtr& arg1, size_t n);
	friend CheckedPtr operator-(const CheckedPtr& arg1, size_t n);
	CheckedPtr& operator++();
	CheckedPtr& operator--();
	const Screen* operator->() const;
	Screen* operator->() ;
	const Screen operator*() const;
	Screen operator*();
private:
	Screen *beg, *end, *curr;
};

struct  FunObj
{
	int operator()(bool Judge, int arg1, int arg2)
	{
		if (Judge)
			return arg1;
		else
			return arg2;
	}
};

class Predicate
{
public:
	Predicate(int arg):Judge(arg){}
	bool operator()(const int &arg)
	{
		return arg == Judge;
	}
private:
	int Judge;
};

//泛型句柄类
template<typename T>
class Handle
{
private:
	T* Pointer;
	size_t* Use;
	void Decrease(void)
	{
		if (--*Use == 0)
		{
			delete Pointer;
			delete Use;
		}
	}
public:
	Handle(T* arg = nullptr) :Pointer(arg), Use(new size_t(1)){}
	T& operator*();
	T* operator->();
	const T& operator*()const;
	const T* operator->()const;
	//复制控制
	Handle(const Handle& arg) :Pointer(arg.Pointer), Use(arg.Use) { ++*Use; }
	Handle& operator=(const Handle&);
	~Handle() { Decrease(); }
};

//Handle类模板成员实现
template<typename T>
inline T& Handle<T>::operator*()
{
	if (Pointer == nullptr)
		return *this;
	throw std::runtime_error("Deference unbund handle");
}

template<typename T>
inline T* Handle<T>::operator->()
{
	if (Pointer == nullptr)
		return Pointer;
	throw std::runtime_error("Access through unbund handle");
}

template<typename T>
inline const T& Handle<T>::operator*()const
{
	if (Pointer == nullptr)
		return *this;
	throw std::runtime_error("Deference unbund handle");
}

template<typename T>
inline const T* Handle<T>::operator->()const
{
	if (Pointer == nullptr)
		return Pointer;
	throw std::runtime_error("Access through unbund handle");
}

template<typename T>
inline Handle<T>& Handle<T>::operator=(const Handle& arg)
{
	Decrease();
	++*arg.Use;
	Use= arg.Use;
	Pointer = arg.Pointer;
	return *this;
}

template<class T>
class Vector
{
public:
	Vector() :Elements(0), FirstFree(0), End(0)
	{
	}
	void PushBack(const T&);
	void Reserve(int);
	void Resize(size_t, T);
	void Resize(size_t);
	T& operator[](const std::size_t);
	const T& operator[](const std::size_t) const;
	typedef T* Iterator;
	Iterator Begin(void)
	{
		return Elements;
	}
	Iterator Final(void)
	{
		return FirstFree;
	}
private:
	static std::allocator<T> Alloc;
	void Reallocate();
	T *Elements, *FirstFree, *End;
};
#include "head.cpp"
#endif