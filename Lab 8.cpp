#include <iostream>
#include "String.h"
#include <deque>
#include <map>
#include <ctime>
#include <algorithm>

//Набор символов чтобы составлять строку
char a[45] =
{
'q','w','e','r','t','y','u','i','o','p','[',']','a','s','d',
'f','g','h','j','k','l','z','x','c','v','b','n','m','!','@',
'#','$','%','&','1','2','3','4','5','6','7','8','9','0','?'
};


int create_i() {
	return rand();
}

string create_s() { // создание строки длиной 5 из символов в массиве
	char* res = new char[6];
	int pos;
	for (int i = 0; i < 5; i++) {
		pos = rand() % 45;
		res[i] = a[pos]; // наугад берем символ из массива и добавляем к строке
	}
	res[5] = '\0';
	return string(res);
}

void testmultimap_s(int n) {
	std::cout << "num of elements: " << n << std::endl;
	srand(time(0));
	std::multimap<string, string> m;
	string* ar = new string[n];
	for (int i = 0; i < n; i++) {
		ar[i].assign(create_s()); // заполняем массив строк
	}
	
	clock_t t = clock(); // записываем время начала
	for (int i = 0; i < n; i++) m.emplace(ar[i], ar[i]); // добавляем в контейнер из массива строк
	t = clock() - t; // записываем время конца
	std::cout << "insert time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	t = clock();
	for (int i = 0; i < n; i++) {
		m.find(ar[rand() % n]); // берем из массива строк случайную строку и ищем ее
	}
	t = clock() - t;
	std::cout << "find time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	
	t = clock();
	for (int i = 0; i < n; i++) {
		m.erase(ar[rand() % n]);// берем из массива строк случайную строку и удаляем ее
	}
	t = clock() - t;
	std::cout << "erase time: " << ((float)t) / CLOCKS_PER_SEC << std::endl << std::endl;

}

void testmultimap_i(int n) {
	std::cout << "num of elements: " << n << std::endl;
	std::multimap<int, int> m;
	int* ar = new int[n];
	for (int i = 0; i < n; i++) {
		ar[i] = create_i();
	}

	clock_t t = clock();
	for (int i = 0; i < n; i++) m.emplace(ar[i], ar[i]);
	t = clock() - t;
	std::cout << "insert time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	t = clock();
	for (int i = 0; i < n; i++) {
		srand(time(0));
		m.find(ar[rand() % n]);
	}
	t = clock() - t;
	std::cout << "find time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	t = clock();
	for (int i = 0; i < n; i++) {
		m.erase(ar[rand() % n]);
	}
	t = clock() - t;
	std::cout << "erase time: " << ((float)t) / CLOCKS_PER_SEC << std::endl << std::endl;

}

void testdeque_s(int n) {
	std::cout << "num of elements: " << n << std::endl;
	srand(time(0));
	std::deque<string> m;
	string* ar = new string[n];
	for (int i = 0; i < n; i++) {
		ar[i].assign(create_s());
	}

	clock_t t = clock();
	for (int i = 0; i < n; i++) m.push_back(ar[i]);
	t = clock() - t;
	std::cout << "insert time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	// у deque нет метода поиска, поэтому ищем с помощью итератора 
	// (n раз берем случайную строку из массива и проходя по deque с помощью итератора сравниваем значения)
	int pos;
	t = clock();
	for (int i = 0; i < n; i++) { 
		pos = rand() % n;
		for (auto& i : m) {
			if (i == ar[pos]) break;
		}
	}
	t = clock() - t;
	std::cout << "find time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;
	
	t = clock();
	std::sort(m.begin(), m.end()); // сортировка из библиотеки algorithm
	t = clock() - t;
	std::cout << "sort time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;


	// метод удаления в deque принимает итератор места удаления, поэтому выбираем случайное место в deque и удаляем
	t = clock();
	for (int i = 0; i < n; i++) {
		m.erase(m.begin() + (rand() % m.size())); 
	}
	t = clock() - t;
	std::cout << "erase time: " << ((float)t) / CLOCKS_PER_SEC << std::endl << std::endl;

}

void testdeque_i(int n) {
	std::cout << "num of elements: " << n << std::endl;
	srand(time(0));
	std::deque<int> m;
	int* ar = new int[n];
	for (int i = 0; i < n; i++) {
		ar[i] = create_i();
	}

	clock_t t = clock();
	for (int i = 0; i < n; i++) m.push_back(ar[i]);
	t = clock() - t;
	std::cout << "insert time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	int pos;
	t = clock();
	for (int i = 0; i < n; i++) {
		pos = rand() % n;
		for (auto& i : m) {
			if (i == ar[pos]) break;
		}
	}
	t = clock() - t;
	std::cout << "find time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;
	
	t = clock();
	std::sort(m.begin(), m.end());
	t = clock() - t;
	std::cout << "sort time: " << ((float)t) / CLOCKS_PER_SEC << std::endl;

	t = clock();
	for (int i = 0; i < n; i++) {
		m.erase(m.begin() + rand() % m.size());
	}
	t = clock() - t;
	std::cout << "erase time: " << ((float)t) / CLOCKS_PER_SEC << std::endl << std::endl;
	
}

//У multimap нет сортировки, потому что контейнер упорядоченый
int main()
{
	std::cout << "multimap string" << std::endl;
	for (int i = 1000; i <= 20000; i += 1000) testmultimap_s(i);

	std::cout << "multimap int" << std::endl;
	for (int i = 1000; i <= 20000; i += 1000) testmultimap_i(i);

	std::cout << "deque string" << std::endl;
	for(int i = 1000; i <= 20000; i += 1000) testdeque_s(i);

	std::cout << "deque int" << std::endl;
	for (int i = 1000; i <= 20000; i += 1000) testdeque_i(i);
	
}