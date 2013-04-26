#ifndef _XT_LIST_H_
#define _XT_LIST_H_

#include "object.hh"
#include "exceptions.hh"
#include "seq.hh"


namespace xt {
struct _List;
struct _List {
	_List(Object first, std::shared_ptr<_List> rest, int count) : first(first), count(count), rest(rest) { }
	const Object first;
	const int count;
	const std::shared_ptr<_List> rest;
	static TypeInfo type_info;
};
typedef std::shared_ptr<_List> List;

class LSeq : public ISeq {
public:
	const List l;
	LSeq(const List l): l(l) {}
	virtual Object first() const;
	virtual Seq next() const;
};

namespace list {

List cons(Object o);
List cons(List list, Object o);
inline bool is_list(Object o) { return o.typeinfo == &_List::type_info; }
inline Seq to_seq(List l) { return Seq(new LSeq(l)); }
inline List to_list(Object o) { if (!is_list(o)) throw RuntimeException("Not a List"); return std::static_pointer_cast<_List>(o.ptr); }
List empty();

}
}

#endif
