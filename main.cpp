#include <iostream>
#include "String.h"
#include "Tests.h"


int main()
{
	// заполнение данных для тестов

	insert_data* i_data = new insert_data[4]{ 
		{3, string("abcde"), string("123456789"), string("123abcde456789")},
		{10000, string("abcde"), string("123456789"), string()},
		{3, string(""), string("123456789"), string("123456789")},
		{0, string("abcde"), string(""), string("abcde")} 
	};
	find_data* f_data = new find_data[4]{
		{string(""), string("123456789"), 0},
		{string("45678"), string("123456789"), 3},
		{string("1234567890"), string("123456789")},
		{string("abcde"), string("123456789")}
	};
	substr_data* s_data = new substr_data[5]{
		{0, 9, string("123456789"), string("123456789")},
		{1, 2, string("123456789"), string("23")},
		{1, 1000, string("123456789"), string()},
		{1, 0, string("123456789"), string("")},
		{1000, 5, string("123456789"), string()}
	};

	// прогон тестов

	int c = 0;
	for (int i = 0; i < 4; i++) {
		if (insert_test(*(i_data + i))) {
			c++;
			std::cout << "ok" << std::endl;
		}
		else std::cout << "fail" << std::endl;
	}
	std::cout << "insert test " << c << "/4 ok" << std::endl << std::endl;

	c = 0;
	for (int i = 0; i < 4; i++) {
		if (find_test(*(f_data + i))) {
			c++;
			std::cout << "ok" << std::endl;
		}
		else std::cout << "fail" << std::endl;
	}
	std::cout << "find test " << c << "/4 ok" << std::endl << std::endl;

	c = 0;
	for (int i = 0; i < 5; i++) {
		if (substr_test(*(s_data + i))) {
			c++;
			std::cout << "ok" << std::endl;
		}
		else std::cout << "fail" << std::endl;
	}
	std::cout << "substr test " << c << "/5 ok" << std::endl << std::endl;
}