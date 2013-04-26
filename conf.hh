#ifndef _XT_CONF_H_
#define _XT_CONF_H_

#include <unistd.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>

typedef char byte;
typedef unsigned char ubyte;
typedef unsigned char xt_byte;

enum class Type : unsigned char {
	Nil,
	Boolean,
	Number,
	Pointer,
	Char,
	Other
};

struct TypeInfo {
	std::string name;
};

template<typename T>
int index_of(const std::vector<T>& v, const T& val) {
	int idx = 0;
	for (typename std::vector<T>::const_iterator it = v.cbegin(); it != v.cend(); ++it) {
		if (*it == val) return idx;
		idx++;
	}
	return -1;
}

template<typename K, typename V>
bool has_key(const std::unordered_map<K, V> m, const K& k) {
	for (auto it = m.begin(); it != m.end(); ++it) {
		if (k == it->first) return true;
	}
	return false;
}

#endif
