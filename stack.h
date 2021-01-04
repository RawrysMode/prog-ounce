#pragma once

#include "String.h"
#include <iostream>

namespace my {
template<class T>
class stack {
public:
	stack();
	stack(const stack& other);
	~stack();
	void push(T& data);
	void pop();
	const T& top() const;
	bool empty() const;
	size_t size() const;
	void clear();
	void insert(T& data, size_t index);
	const T& remove(size_t index);
	void print() const;
	bool contains(const T& data) const;

private:
	class node {
	public:
		node(T& data);
	private:
		T& _data;
		node* _next;
		friend class stack;
	};

	node* _head;
	size_t _length;
};
}
using namespace my;

template<class T>
stack<T>::stack()
{
	_head = nullptr;
	_length = 0;
}

/*
	����������� �����������
*/
template<class T>
stack<T>::stack(const stack<T>& other)
{
	clear(); // ������� ����
	if (other._length == 0) return;
	_head = new node(other._head->_data); // ������� ������
	node* n = _head;
	node* tmp = other._head->_next;
	while (tmp != nullptr) {
		n->_next = new node(tmp->_data); // ��������� �������� ����� other
		n = n->_next;
		tmp = tmp->_next;
	}
	_length = other._length;
}


template<class T>
stack<T>::~stack()
{
	node* tmp;
	while (_head) { // ��������������� ������� �������
		tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
}

template<class T>
void stack<T>::push(T& data)
{
	node* tmp = new node(data); // ������� ����� ������� �� ����� ������
	tmp->_next = _head;
	_head = tmp;
	_length++;
}

template<class T>
void stack<T>::pop()
{
	if (_length == 0) throw std::exception("no elements");
	node* tmp = _head; // ������� ������� � ������
	_head = _head->_next;
	delete tmp;
	_length--;
}

template<class T>
const T& stack<T>::top() const
{
	if (_length == 0) throw std::exception("no elements");
	return _head->_data;
}

template<class T>
bool stack<T>::empty() const
{
	return _length == 0;
}

template<class T>
size_t stack<T>::size() const
{
	return _length;
}

template<class T>
void stack<T>::clear()
{
	node* tmp;
	while (_head) { // �� ��, ��� � � ����������� 
		tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
	_head = nullptr; // �������� ����������
	_length = 0;
}

template<class T>
void stack<T>::insert(T& data, size_t index)
{
	if (index < 0 || index >= _length) throw std::out_of_range("index out of range");
	if (index == 0) { // ���� ������ == 0, �� �� ����� ��� � push
		push(data);
		return;
	}
	node* tmp = _head;
	for (int i = 1; i < index; i++) { // ������� �� ������� �����
		tmp = tmp->_next;
	}
	node* new_node = new node(data); // ��������� ���� �������
	new_node->_next = tmp->_next;
	tmp->_next = new_node;
	_length++;
}

template<class T>
const T& stack<T>::remove(size_t index)
{

	if (index < 0 || index >= _length) throw std::out_of_range("index out of range");
	if (index == 0) { // ���� ������ == 0, �� �� ����� ��� � pop
		T s = top();
		pop();
		return s;
	}
	node* tmp = _head;
	for (int i = 1; i < index; i++) { // ������� �� ������� ����� 
		tmp = tmp->_next;
	}
	node* del = tmp->_next; // ������� �������, �������� � ��������� �� ��������
	tmp->_next = del->_next;
	del->_next = nullptr;
	T& s = del->_data;
	delete del;
	_length--;
	return s;
}

template<class T>
void stack<T>::print() const
{
	node* tmp = _head;
	for (size_t i = 0; i < _length; i++, tmp = tmp->_next) std::cout << tmp->_data << " "; // ������� ������
	std::cout << std::endl;
}
/*
	��������������� ��������� �� ������� ��������, ��������� �� ������, � �� �� �������
*/
template<class T>
bool stack<T>::contains(const T& data) const
{
	node* tmp = _head;
	for (size_t i = 0; i < _length; i++, tmp = tmp->_next) if (tmp->_data == data) return 1;
	return 0;
}
// ������������� ��� ������ ������ �.�. � ������ string ��� ���������� ==
template<>
bool stack<string>::contains(const string& data) const
{
	node* tmp = _head;
	for (size_t i = 0; i < _length; i++, tmp = tmp->_next) if (strcmp(tmp->_data.c_str(), data.c_str()) == 0) return 1;
	return 0;
}

template<class T>
stack<T>::node::node(T& data) :
	_data(data),
	_next(nullptr)
{}
