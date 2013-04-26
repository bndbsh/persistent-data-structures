#ifndef _XT_OBJECT_HH_
#define _XT_OBJECT_HH_

#include "conf.hh"

#include <memory>
#include <vector>

namespace xt {

static TypeInfo bool_type { "Boolean" };
static TypeInfo char_type { "Char" };
static TypeInfo number_type { "Number"};
static TypeInfo nil_type { "Nil" };

struct Object {
	Object() : type(Type::Nil), typeinfo(&nil_type) {}
	Object(const Object& o);
	explicit Object(bool b) : type(Type::Boolean), typeinfo(&bool_type), b(b) {}
	explicit Object(int n) : type(Type::Number), typeinfo(&number_type), number(n) {}
	explicit Object(double n) : type(Type::Number), typeinfo(&number_type), number(n) {}
	explicit Object(char ch) : type(Type::Char), typeinfo(&char_type), ch(ch) {}
	Object(void* t, TypeInfo* ti) : type(Type::Pointer), typeinfo(ti), raw(t) {}
	template<class T>
	Object(std::shared_ptr<T> t, TypeInfo* ti) : type(Type::Pointer), typeinfo(ti), ptr(t) {}
	template<class T>
	Object(std::shared_ptr<T> t) : type(Type::Pointer), typeinfo(&T::type_info), ptr(t) {}
	Object& operator=(const Object& o);
	
	bool operator==(const Object& o2) const { return type == o2.type && typeinfo == o2.typeinfo && number == o2.number; }

	~Object() {}
	operator bool() const;
	Type type;
	TypeInfo* typeinfo;
	union {
		double number;
		bool b;
		char ch;
		void* raw;
		std::shared_ptr<void> ptr;
	};
};

typedef std::vector<Object> _ObjectArray;
typedef std::shared_ptr<_ObjectArray> ObjectArray;

ObjectArray new_object_array(unsigned int size = 0);

}

namespace std { 
template<>
struct hash<typename xt::Object> {
	std::size_t operator()(xt::Object const &key) {
		return hash<void*>()(key.ptr.get());
	}
};
}

#endif
