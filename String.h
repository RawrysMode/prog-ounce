#pragma once

class string {

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
	static size_t get_string_count();
	bool operator<(const string&) const;
	bool operator==(const string&) const;
	string& operator=(const string& ot) { assign(ot); return *this; }

private:
	static size_t _string_count;
	const size_t initial_max_length = 16;
	char* _str;
	size_t _max_length;
	size_t _length;

	void allocate_and_cpy(size_t);
};