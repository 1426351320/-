#include "head.h"

ostream& operator<<(ostream& OS, const SalesItem& arg)
{
	OS << arg.ISBN << "\t" << arg.Revenue << "\t" << arg.UnitsSold;
	return OS;
}

istream& operator>>(istream& IS,  SalesItem& arg)
{
	if (IS)
		IS >> arg.ISBN >> arg.Revenue >> arg.UnitsSold;
	else
		arg = SalesItem();

	return IS;
}

SalesItem SalesItem::operator+(const SalesItem& arg)
{
	SalesItem Ins;
	Ins = arg;
	Ins += *this;
	return Ins;
}
SalesItem& SalesItem::operator+=(const SalesItem& arg)
{
	this->ISBN = this->ISBN+ arg.ISBN;
	this->Revenue = this->Revenue + arg.Revenue;
	this->UnitsSold = this->UnitsSold + arg.UnitsSold;

	return *this;
}

/*CheckedPtr类算数重定义*/
CheckedPtr operator+(const CheckedPtr& arg1, size_t n)
{
	CheckedPtr ins(arg1);
	ins.curr = ins.curr+n;
	if (ins.curr > ins.end)
		throw out_of_range("n too large");
	
	return ins;
}

CheckedPtr operator-(const CheckedPtr& arg1, size_t n)
{
	CheckedPtr ins(arg1);
	ins.curr = ins.curr -n;
	if (ins.curr < ins.beg)
		throw out_of_range("n too large");

	return ins;
}

CheckedPtr& CheckedPtr::operator++()//自增重定义
{
	if (this->curr == this->end)
		throw out_of_range("increasement pased the end of CheckedPtr");

	curr++;

	return *this;
}

CheckedPtr& CheckedPtr::operator--()//自减重定义
{
	if (this->curr == this->beg)
		throw out_of_range("decreasement past the begin of CheckedPtr");

	curr--;

	return *this;
}

const Screen*  CheckedPtr::operator->() const
{
	return curr;
}

Screen* CheckedPtr::operator->()
{
	return curr;
}

const Screen CheckedPtr::operator*() const
{
	if (curr == end)
		throw out_of_range("invalid current pointer");

	return *curr;
}

Screen CheckedPtr::operator*()
{
	if (curr == end)
		throw out_of_range("invalid current pointer");

	return *curr;
}

template<class T>
void Vector<T>::PushBack(const T& arg)
{
	if (FirstFree == End)
		Reallocate();
	Alloc.construct(FirstFree, arg);//在原始内存中构造对象
	++FirstFree;
}
template<class T>
void Vector<T>::Reallocate()
{
	std::ptrdiff_t Size = FirstFree - Elements;
	std::ptrdiff_t NewCapacity = 2 * max(Size, 1);//每次内存不够用都分配现有元素二倍的大小
	T* NewElements = Alloc.allocate(NewCapacity);//分配新的内存

	uninitialized_copy(Elements, FirstFree, NewElements);
	for (T* p = Elements; p != FirstFree; p++)//销毁原内存中的元素
		Alloc.destroy(p);

	if (Elements)//确认不是未分配的指针
		Alloc.deallocate(Elements, end - Elements);
	Elements = NewElements;
	FirstFree = Elements + Size;
	End = Elements + NewCapacity;
}
template<class T>
void Vector<T>::Reserve(int arg)
{
	std::ptrdiff_t Size = FirstFree - Elements;
	std::ptrdiff_t NewCapacity = arg*sizeof(T);//每次内存不够用都分配现有元素二倍的大小

	if (NewCapacity < Size)
		throw runtime_error("Space allocated is too small!");
	T* NewElements = Alloc.allocate(NewCapacity);//分配新的内存

	uninitialized_copy(Elements, FirstFree, NewElements);
	for (T* p = Elements; p != FirstFree; p++)//销毁原内存中的元素
		Alloc.destroy(p);

	if (Elements)//确认不是未分配的指针
		Alloc.deallocate(Elements, end - Elements);
	Elements = NewElements;
	FirstFree = Elements + Size;
	End = Elements + NewCapacity;
}
template<class T>
void Vector<T>::Resize(size_t arg1, T arg2)
{
	std::ptrdiff_t Size = FirstFree - Elements;
	std::ptrdiff_t Capacity = End - Elements;
	//std::ptrdiff_t NewCapacity = arg1 * sizeof(T);
	if (arg1 >= Size)
		while (Size != arg1)
		{
			PushBack(arg2);//PushBack中有Reallocate
			Size ++;
		}
	else
		while (Size != arg1)
		{
			Alloc.destroy(--FirstFree);//PushBack中有Reallocate
			Size --;
		}
}
template<class T>
void Vector<T>::Resize(size_t arg)
{
	std::ptrdiff_t Size = FirstFree - Elements;
	std::ptrdiff_t Capacity = End - Elements;
	//std::ptrdiff_t NewCapacity = arg * sizeof(T);
	if (arg1 >= Size)
		while (Size != arg1)
		{
			PushBack(T());//PushBack中有Reallocate
			Size++;
		}
	else
		while (Size != arg1)
		{
			Alloc.destroy(--FirstFree);//PushBack中有Reallocate
			Size--;
		}
}
template<class T>
T& Vector<T>::operator[](const std::size_t Index)
{
	return Elements[arg];
}
template<class T>
const T& Vector<T>::operator[](const std::size_t Index)const
{
	return Elements[arg];
}









