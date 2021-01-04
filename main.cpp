#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "catch.hpp"

#include "String.h"
#include "binary_string.h"
#include "todo_string.h"
#include "stack.h"

using namespace my;

TEST_CASE("constructor with string", "[stack, string]") { // тесты для конструктора
	stack<string> s; // конструктор по умолчанию
	REQUIRE(s.size() == 0);
	REQUIRE(s.empty());
	REQUIRE_THROWS_AS(s.top(), std::exception);
	REQUIRE_THROWS_AS(s.pop(), std::exception);
	string strings[5];
	strings[0] = "string0";
	strings[1] = "string1";
	strings[2] = "string2";
	strings[3] = "string3";
	strings[4] = "string4";
	for (int i = 0; i < 5; i++) s.push(strings[i]);
	stack<string> s1(s); // конструктор копирования
	REQUIRE(s1.size() == 5);
	REQUIRE(strcmp(s1.remove(2).c_str(), "string2") == 0);
}

TEST_CASE("constructor with int", "[stack, int]") { // тесты для конструктора
	stack<int> s; // конструктор по умолчанию
	REQUIRE(s.size() == 0);
	REQUIRE(s.empty());
	REQUIRE_THROWS_AS(s.top(), std::exception);
	REQUIRE_THROWS_AS(s.pop(), std::exception);
	int ints[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++) s.push(ints[i]);
	stack<int> s1(s); // конструктор копирования
	REQUIRE(s1.size() == 5);
	REQUIRE(s1.remove(2) == 3);
}

TEST_CASE("constructor with float", "[stack, float]") { // тесты для конструктора
	stack<float> s; // конструктор по умолчанию
	REQUIRE(s.size() == 0);
	REQUIRE(s.empty());
	REQUIRE_THROWS_AS(s.top(), std::exception);
	REQUIRE_THROWS_AS(s.pop(), std::exception);
	float floats[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	for (int i = 0; i < 5; i++) s.push(floats[i]);
	stack<float> s1(s); // конструктор копирования
	REQUIRE(s1.size() == 5);
	REQUIRE(abs(s1.remove(2) - 3.3) < 0.00001); // Погрешность при сравнении float
}


TEST_CASE("push, pop, print with string", "[stack, string]") {
	stack<string> s;
	string strings[5];
	strings[0] = "string0";
	strings[1] = "string1";
	strings[2] = "string2";
	strings[3] = "string3";
	strings[4] = "string4";
	for (int i = 0; i < 5; i++) s.push(strings[i]); // добавляем в стек данные
	FILE * o = freopen("file5lab.txt", "w", stdout); // перенаправляем поток вывода
	s.print(); // выводим стек
	
	std::ifstream ist("file5lab.txt");
	string st;
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "string4 string3 string2 string1 string0")); 
	ist.close();

	s.pop(); // удаляем данные из стека
	s.pop();

	s.print(); // выводим стек

	ist.open("file5lab.txt");
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "string2 string1 string0"));
	ist.close();

	fclose(stdout);
	o = freopen("CON", "w", stdout);
}

TEST_CASE("push, pop, print with int", "[stack, int]") {
	stack<int> s;
	int ints[5] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++) s.push(ints[i]); // добавляем в стек данные
	FILE* o = freopen("file5lab.txt", "w", stdout); // перенаправляем поток вывода
	s.print(); // выводим стек

	std::ifstream ist("file5lab.txt");
	string st;
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "5 4 3 2 1"));
	ist.close();

	s.pop(); // удаляем данные из стека
	s.pop();

	s.print(); // выводим стек

	ist.open("file5lab.txt");
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "3 2 1"));
	ist.close();

	fclose(stdout);
	o = freopen("CON", "w", stdout);
}

TEST_CASE("push, pop, print with float", "[stack, float]") {
	stack<float> s;
	float floats[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	for (int i = 0; i < 5; i++) s.push(floats[i]); // добавляем в стек данные
	FILE* o = freopen("file5lab.txt", "w", stdout); // перенаправляем поток вывода
	s.print(); // выводим стек

	std::ifstream ist("file5lab.txt");
	string st;
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "5.5 4.4 3.3 2.2 1.1"));
	ist.close();

	s.pop(); // удаляем данные из стека
	s.pop();

	s.print(); // выводим стек

	ist.open("file5lab.txt");
	ist >> st; // читаем то, что выведено
	REQUIRE(strcmp(st.c_str(), "3.3 2.2 1.1"));
	ist.close();

	fclose(stdout);
	o = freopen("CON", "w", stdout);
}

TEST_CASE("polymorphism, top", "[stack, string, binary_string, todo_string]") {
	stack<string> s;
	string str = "this is string"; // создаем 3 объекта разных классов
	binary_string bin_str = -19;
	todo_string todo_str = "do a test";
	todo_str.start();
	time_t st = todo_str.when_started();
	s.push(todo_str); // добавляем их в стек
	s.push(bin_str);
	s.push(str);
	REQUIRE(strcmp(s.top().c_str(), "this is string") == 0); // c_str() является функцией класса string и наследуется
	s.pop();
	REQUIRE(strcmp(s.top().c_str(), "-10011") == 0); // классами binary_string и
	s.pop();
	string req;
	req.append(asctime(localtime(&st)));
	req.append("do a test");
	REQUIRE(strcmp(s.top().c_str(), req.c_str()) == 0); // время начала и todo_string
}

TEST_CASE("insert, delete with string", "[stack, string]") {
	stack<string> s;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";
	s.push(str1);
	s.push(str2);
	s.insert(str3, 1);
	REQUIRE_THROWS_AS(s.insert(str1, -1), std::out_of_range);
	REQUIRE_THROWS_AS(s.insert(str1, 100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(-1), std::out_of_range);
	REQUIRE(strcmp(s.top().c_str(), str2.c_str()) == 0);
	REQUIRE(&s.top() == &str2); // совпадают адреса, так как храним ссылки
	REQUIRE(s.size() == 3);
	REQUIRE(strcmp(s.remove(1).c_str(), str3.c_str()) == 0);
}

TEST_CASE("insert, delete with int", "[stack, int]") {
	stack<int> s;
	int ints[3] = { 1, 2, 3 };
	s.push(ints[0]);
	s.push(ints[1]);
	s.insert(ints[2], 1);
	REQUIRE_THROWS_AS(s.insert(ints[0], -1), std::out_of_range);
	REQUIRE_THROWS_AS(s.insert(ints[0], 100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(-1), std::out_of_range);
	REQUIRE(s.top() == ints[1]);
	REQUIRE(&s.top() == &(ints[1])); // совпадают адреса, так как храним ссылки
	REQUIRE(s.size() == 3);
	REQUIRE(s.remove(1) == ints[2]);
}

TEST_CASE("insert, delete with float", "[stack, float]") {
	stack<float> s;
	float floats[3] = { 1.1, 2.2, 3.3 };
	s.push(floats[0]);
	s.push(floats[1]);
	s.insert(floats[2], 1);
	REQUIRE_THROWS_AS(s.insert(floats[0], -1), std::out_of_range);
	REQUIRE_THROWS_AS(s.insert(floats[0], 100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(100), std::out_of_range);
	REQUIRE_THROWS_AS(s.remove(-1), std::out_of_range);
	REQUIRE(s.top() == floats[1]);
	REQUIRE(&s.top() == &(floats[1])); // совпадают адреса, так как храним ссылки
	REQUIRE(s.size() == 3);
	REQUIRE(abs(s.remove(1) - floats[2]) < 0.00001);
}

TEST_CASE("contains with string", "[stack, string]") {
	stack<string> s;
	string s1 = "string1";
	string s2 = "string2";
	string s3 = "string1";
	s.push(s1);
	s.push(s2);
	REQUIRE(s.contains(s1));
	REQUIRE(s.contains(s3)); // Проверяем, что совпадения ищутся по значению, а не по адресу
}

TEST_CASE("contains with int", "[stack, int]") {
	stack<int> s;
	int ints[3] = { 1, 2, 1 };
	s.push(ints[0]);
	s.push(ints[1]);
	REQUIRE(s.contains(ints[0]));
	REQUIRE(s.contains(ints[2])); // Проверяем, что совпадения ищутся по значению, а не по адресу
}

TEST_CASE("contains with float", "[stack, float]") {
	stack<float> s;
	float floats[3] = { 1.1, 2.2, 1.1 };
	s.push(floats[0]);
	s.push(floats[1]);
	REQUIRE(s.contains(floats[0]));
	REQUIRE(s.contains(floats[2])); // Проверяем, что совпадения ищутся по значению, а не по адресу
}