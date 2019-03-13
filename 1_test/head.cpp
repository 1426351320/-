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

/*CheckedPtr�������ض���*/
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

CheckedPtr& CheckedPtr::operator++()//�����ض���
{
	if (this->curr == this->end)
		throw out_of_range("increasement pased the end of CheckedPtr");

	curr++;

	return *this;
}

CheckedPtr& CheckedPtr::operator--()//�Լ��ض���
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
	Alloc.construct(FirstFree, arg);//��ԭʼ�ڴ��й������
	++FirstFree;
}
template<class T>
void Vector<T>::Reallocate()
{
	std::ptrdiff_t Size = FirstFree - Elements;
	std::ptrdiff_t NewCapacity = 2 * max(Size, 1);//ÿ���ڴ治���ö���������Ԫ�ض����Ĵ�С
	T* NewElements = Alloc.allocate(NewCapacity);//�����µ��ڴ�

	uninitialized_copy(Elements, FirstFree, NewElements);
	for (T* p = Elements; p != FirstFree; p++)//����ԭ�ڴ��е�Ԫ��
		Alloc.destroy(p);

	if (Elements)//ȷ�ϲ���δ�����ָ��
		Alloc.deallocate(Elements, end - Elements);
	Elements = NewElements;
	FirstFree = Elements + Size;
	End = Elements + NewCapacity;
}
template<class T>
void Vector<T>::Reserve(int arg)
{
	std::ptrdiff_t Size = FirstFree - Elements;
	std::ptrdiff_t NewCapacity = arg*sizeof(T);//ÿ���ڴ治���ö���������Ԫ�ض����Ĵ�С

	if (NewCapacity < Size)
		throw runtime_error("Space allocated is too small!");
	T* NewElements = Alloc.allocate(NewCapacity);//�����µ��ڴ�

	uninitialized_copy(Elements, FirstFree, NewElements);
	for (T* p = Elements; p != FirstFree; p++)//����ԭ�ڴ��е�Ԫ��
		Alloc.destroy(p);

	if (Elements)//ȷ�ϲ���δ�����ָ��
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
			PushBack(arg2);//PushBack����Reallocate
			Size ++;
		}
	else
		while (Size != arg1)
		{
			Alloc.destroy(--FirstFree);//PushBack����Reallocate
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
			PushBack(T());//PushBack����Reallocate
			Size++;
		}
	else
		while (Size != arg1)
		{
			Alloc.destroy(--FirstFree);//PushBack����Reallocate
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









