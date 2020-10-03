#pragma once

class string {

private:
	const size_t initial_max_length = 16;
	char* _str;
	size_t _max_length;
	size_t _length;

	void allocate_and_cpy(size_t);

public:
	string();
	string(const char*);
	string(const string&);
	~string();
	void append(const char*);
	void append(const string&);
	size_t length() const;
	size_t max_length() const;
	void clear();
	bool empty() const;
	void assign(const char*);
	void assign(const string&);
	void insert(size_t, const char*);
	void insert(size_t, const string&);
	size_t find(const char*) const;
	size_t find(const string&) const;
	string substr(size_t, size_t) const;
	char* c_str() const;
	void print() const;
};