#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <string.h>
#include <iostream>

/*
	��������� �� ���� ����� ���������� ���������� ������ � �������� ������
*/
void string::allocate_and_cpy(size_t new_max_length)
{
	if (_max_length == new_max_length) return;
	char* tmp = new char[_length + 1]; // �������� ������
	strcpy(tmp, _str);
	delete _str;
	_str = new char[new_max_length + 1]; // ��������� ������� ������
	strcpy(_str, tmp);
	delete[] tmp;
}
/*
	�����������
*/
string::string()
{
	_max_length = initial_max_length;
	_length = 0;
	_str = new char[_max_length + 1];
	*_str = '\0';
}
/*
	�����������
*/
string::string(const char* str)
{
	_max_length = initial_max_length;
	size_t len = strlen(str);
	while (len > _max_length) _max_length *= 2; // ���� ����� ����������� ������ ������ ��� ���������� ������ 
	_length = len;
	_str = new char[_max_length + 1]; 
	strcpy(_str, str);
}
/*
	�����������
*/
string::string(const string& str)
{
	_max_length = str._max_length;
	_length = str._length;
	_str = new char[_max_length];
	strcpy(_str, str._str);
}
/*
	����������
*/
string::~string()
{
	delete[] _str;
}

/*
	��������� �������� ��������� � ����� ������
*/
void string::append(const char* str)
{
	size_t len = strlen(str);
	if (len + _length > _max_length){ // ������ ���� ��������� ����� ������ ���������� ������
		while (len + _length > _max_length) _max_length *= 2; // ����������� ���������� ������
		allocate_and_cpy(_max_length);
		char* tmp = _str + _length; // ������ ��������� �� ����� ������� ������
		for (size_t i = 0; i < len; i++) { //���������� �������� ������ � ����� �������
			*(tmp + i) = *(str + i);
		}
		_length += len;
		*(_str + _length) = '\0';
	}
	else {
		char* tmp = _str + _length; // ������ ��������� �� ����� ������� ������
		for (size_t i = 0; i < len; i++) { // ���������� �������� ������ � ����� �������
			*(tmp + i) = *(str + i);
		}
		_length += len;
		*(_str + _length) = '\0';
	}
}
/*
	��������� �������� ��������� � ����� ������
*/
void string::append(const string& str)
{
	append(str._str); // �������� ���������� ����� ��������� char*
}
/*
	����� ������
*/
size_t string::length() const
{
	return _length;
}
/*
	������ ���������� ������
*/
size_t string::max_length() const
{
	return _max_length;
}
/*
	������� ������
*/
void string::clear()
{
	_length = 0;
	delete _str; // �������� ������
	_str = new char[_max_length + 1]; // ��������� ������ ��� �����
	*_str = '\0';
}
/*
	�������� �� �������
*/
bool string::empty() const
{
	return _length == 0;
}
/*
	��������� ������ ��������
*/
void string::assign(const char* str)
{
	_length = strlen(str);
	while (_length > _max_length) _max_length *= 2; // ���������� ������������ ������, ���� �����
	allocate_and_cpy(_max_length); // ��������� ���� ����� ������
	strcpy(_str, str); // ����������� �����
}
/*
	��������� ������ ��������
*/
void string::assign(const string& str)
{
	assign(str._str); // �������� ���������� �����, ��������� char*
}
/*
	������� ������ ������ �������
*/
void string::insert(size_t pos, const char* str)
{
	if (pos > _length - 1) throw "wrong position"; // �������� ������������ ���������� ������
	size_t len = strlen(str);
	while (len + _length > _max_length) _max_length *= 2; // ���������� ������������ ������ 
	allocate_and_cpy(_max_length); // ��������� ���� ����� ������

	char* second = new char[_length - pos + 1]; // ����� ��� ������ �������� ������� ������
	strcpy(second, _str + pos); // ����������� ������ �������� � �����
	strcpy(_str + pos, str); // ����������� ���������� ������ �� ����� �����
	strcpy(_str + pos + strlen(str), second); // ���������� ������ �������� ������� � ������ ����� ������ ���������
	delete[] second; // �������� ������
}
/*
	������� ������ ������ �������
*/
void string::insert(size_t pos, const string& str)
{
	insert(pos, str._str); // �������� ���������� �����, ��������� char*
}
/*
	����� ������� ������� ��������� ���������
*/
size_t string::find(const char* str) const
{
	size_t len = strlen(str);
	for (size_t i = 0, j = 0; i < _length; i++, j = 0) { // ������ �� �������� ������� ������
		while (*(_str + i + j) == *(str + j)) j++; // ���� ������� ������ � ��������� ��������� ������� �������������
		if (j == len) return i; // ���� ������� ����� ����� ���������, �� �� ����� ������ ���������
	}
	throw "no such substring"; // ���� ������ �� ����� ����������� ��������� �� ����
}
/*
	����� ������� ������� ��������� ���������
*/
size_t string::find(const string& str) const
{
	return find(str._str); // �������� ���������� �����, ��������� char*
}
/*
	��������� ��������� �� ������� ������
*/
string string::substr(size_t pos_begin, size_t length) const
{
	if (pos_begin + length > _length) throw "incorrect parameters"; // �������� ������������ ���������� ������
	char* str = new char[length + 1]; // ��������� ������ ��� ���������
	for (size_t i = 0; i < length; i++) // ��������������� �������� ������� � ���������
		*(str + i) = *(_str + pos_begin + i); 
	*(str + length) = '\0';
	string s(str);
	delete[] str;
	return s;

}
/*
	����������� ��������� �� char ��� ������� ������ 
*/
char* string::c_str() const
{
	char* str = new char[_length + 1];
	strcpy(str, _str);
	return str;
}
/*
	����� �� �����
*/
void string::print() const
{
	std::cout << _str << std::endl;
}