// LinkedList.cpp:
//    Содержит реализации методов LinkedList и некоторых функций.
//    Наибольшая часть лабораторной работы связана с этим файлом.

#include <iostream>     // std::ostream
#include <stdexcept>    // std::out_of_range
#include <string>       // std::to_string()
#include <utility>      // std::swap()
#include <cassert>

#include "LinkedList.h"


using std::swap;  // Чтобы использовать swap() без std::


LinkedList& LinkedList::operator=(LinkedList rhs)
{

    clear();

    Node* n = rhs.first;
	for (int i=0;i<rhs.size();i++)
	{
	    push_back(n->value);
        n = n->next;
	}
	return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& rhs)
{


    Node* n = rhs.first;
	for (int i=0;i<rhs.size();i++)
	{
	    push_back(n->value);
        n = n->next;
	}
	return *this;
}

bool LinkedList::operator==(const LinkedList& other) const
{

	if (size()!=other.size())
        return false;

    Node* x = first;
	Node* y =other.first;
	for (int i=0;i<size();i++)
	{
        if (x->value != y->value)
        {
            return false;
        }
        x=x->next;
        y=y->next;

	}
	return true;


}

bool LinkedList::operator!=(const LinkedList& other) const
{

	return !(*this == other);
}

void LinkedList::erase(const Node* node)
{

}

void LinkedList::pop_back()
{

	if (size() == 0)
        return;
	Node* n=last;
	last=n->prev;
	delete n;
	if (size() > 1)
        last->next=nullptr;
	size_value--;
	if (size_value == 0) {
        assert(last == nullptr);
        first = nullptr;
	}
}

void LinkedList::pop_front()
{

	if (size() == 0)
        return;
    Node* n=first;
	first=n->next;
	delete n;
	if (size() > 1)
        first->prev=nullptr;
	size_value--;
	if (size_value == 0) {
        assert(first == nullptr);
        last = nullptr;
	}
}

LinkedList::Node* LinkedList::insert_after(LinkedList::Node* after)
{

	return nullptr;
}


LinkedList::Node* LinkedList::insert_before(LinkedList::Node* before)
{

	return nullptr;
}

void LinkedList::push_back(const Data& value)
{

	Node* node = new Node(value); // созд. в куче (heap, обл. дин. пам.)
    if (last == nullptr) {
        assert(("there is first, but there is no last", first == nullptr));
        first = node;
        last = node;
	} else {
	    assert(("there is last, but there is no first", first != nullptr));
        assert(last->next == nullptr);
        last->next = node;
        node->prev = last;
        last = node;
	}
	size_value++;
}

void LinkedList::push_front(const Data& value)
{

	Node* node = new Node(value); // созд. в куче (heap, обл. дин. пам.)
    if (first == nullptr) {
        assert(("there is last, but there is no first", last == nullptr));
        first = node;
        last = node;
	} else {
	    assert(("there is first, but there is no last", last != nullptr));
        assert(first->prev == nullptr);
        first->prev = node;
        node->next = first;
        first = node;
	}
	size_value++;



}

void LinkedList::clear()
{

    size_t s = size();
	for (int i=0;i<s;i++)
    {
        pop_front();
    }
}

void swap(LinkedList& left, LinkedList& right)
{
	// HINT: Функция std::swap() меняет значения простых типов.
}


LinkedList::LinkedList()
{
	first = nullptr;
	last = nullptr;
	size_value = 0;
}

LinkedList::LinkedList(const std::initializer_list<Data> values) :
	LinkedList()
{
	// По std::initializer_list<T> возможен диапазонный for.
	for (const Data& value : values) {
		push_back(value);
	}
}

LinkedList::LinkedList(const LinkedList& source)
{


	// HINT:
	// Здесь нельзя воспользоваться диапазонным for, потому что на данном
	// этапе задания у списка не реализованы итераторы, begin() и end().

    LinkedList* p = this;
    if (& source == p) {
        return;
    }

    first = nullptr;
	last = nullptr;
	size_value = 0;

    Node* n = source.first;
	for (int i=0;i<source.size();i++)
	{
	    push_back(n->value);
        n = n->next;
	}
}

LinkedList::LinkedList(LinkedList&& source)
	: LinkedList()
{
	swap(*this, source);
}

LinkedList::~LinkedList()
{

	clear();
}

size_t LinkedList::size() const
{
	return size_value;
}

Data& LinkedList::value_at(size_t index) const
{
    if (index>=size())
        throw std::out_of_range("index too large");
    Node* n = first;
	for (int i=0;i<index;i++)
	{
        n = n->next;
	}
	return n->value;
}

void LinkedList::remove_at(size_t index)
{

    if (index>=size())
        throw std::out_of_range("index too large");
    Node* y = first;
	for (int i=0;i<index;i++)
	{
        y = y->next;
	}
	Node* p = y->prev;
	Node* n=y->next;
	delete y;
	if (n != nullptr )
        n->prev=p;
	if (p != nullptr )
        p->next=n;
size_value--;
}



void LinkedList::insert_before(size_t index, const Data& value)
{

    if (index>=size())
        throw std::out_of_range("index too large");
    Node* n = first;
	for (int i=0;i<index;i++)
	{
        n = n->next;
	}
	Node* p = n->prev;
	Node* y=new Node(value);
	y->next=n;
	y->prev=p;
	n->prev=y;
	if (p != nullptr)
        p->next=y;
    size_value++;
}

void LinkedList::insert_after(size_t index, const Data& value)
{

    if (index>=size())
        throw std::out_of_range("index too large");
    Node* p = first;
	for (int i=0;i<index;i++)
	{
        p = p->next;
	}
	Node* n =p->next;
	Node* y=new Node(value);
	y->next=n;
	y->prev=p;
	p->next = y;
	if (n != nullptr)
        n->prev=y;
    size_value++;
}

LinkedList::Node* LinkedList::node_at(size_t index)
{

}

std::ostream& operator<<(std::ostream& output, const LinkedList& xs)
{

	output<<'[';


	for (int i=0;i<xs.size();i++)
    {
        output<<xs.value_at(i);
        if (i!=xs.size()-1)
            output<<", ";
    }

	output<<']';

	return output;
}

