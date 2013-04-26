#ifndef _XT_VECTOR_HH_
#define _XT_VECTOR_HH_

#include "conf.hh"
#include "object.hh"
#include "list.hh"
#include "seq.hh"

#include <memory>
#include <vector>

namespace xt {

struct _Node {
	_Node() { array = new_object_array(32); }
	_Node(ObjectArray array) : array(array) {}
	ObjectArray array;
	static TypeInfo type_info;
};

typedef std::shared_ptr<_Node> Node;

inline Node to_node(Object o) { return std::static_pointer_cast<_Node>(o.ptr); }

struct _Vector {
	_Vector(unsigned int cnt, unsigned int shift, Node root, ObjectArray tail) : cnt(cnt), shift(shift), root(root), tail(tail) {}
	const unsigned int cnt;
	const unsigned int shift;
	const Node root;
	const ObjectArray tail;
	static TypeInfo type_info;
};

typedef std::shared_ptr<_Vector> Vector;

class VSeq : public ISeq {
public:
	const Vector v;
	const unsigned int index;
	VSeq(Vector v) : v(v), index(0) {}
	VSeq(Vector v, unsigned int index) : v(v), index(index) {}
	virtual Object first() const;
	virtual Seq next() const;
};

namespace vector {

///returns the empty vector []
Vector empty();

///retruns new vector with val appended
Vector conj(Vector v, Object val);

///returns new vector containing val (appends to empty vector)
Vector conj(Object val);

///returns new vector containing values in list
template<class T>
Vector vec(std::initializer_list<T> list) {
	auto v = empty();
	for (auto i: list) v = conj(v, Object(i));
	return v;
}

///returns vector from list
Vector vec(List list);

inline bool is_vector(Object o) { return o.typeinfo == &_Vector::type_info; }
inline Vector to_vec(Object o) { if (!is_vector(o)) throw RuntimeException("Not a Vector"); return std::static_pointer_cast<_Vector>(o.ptr); }
inline Seq to_seq(Vector v) { return Seq(new VSeq(v)); }

///gets the length of a vector
inline int len(Vector v) { return v->cnt; }

///returns the nth element of a vector
Object nth(Vector v, unsigned int i);

///returns the nth element of a vector, or notFound if index is out of bounds
Object nth(Vector v, unsigned int i, Object notFound);

///returns a new vector with v[i] == val
Object assocN(Vector v, unsigned int i, Object val);

}
}

#endif
