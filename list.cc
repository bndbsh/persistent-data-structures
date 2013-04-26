
#include "list.hh"

namespace xt {
TypeInfo _List::type_info { "List" };
namespace list {

static List EMPTY = List(new _List {Object(), List(), 0});

List cons(Object o) {
	return cons(EMPTY, o);
}

List cons(List list, Object o) {
	return List(new _List {o, list, list->count+1});
}

List empty() {
	return EMPTY;
}

}

Object LSeq::first() const { return l->first; }
Seq LSeq::next() const { if (l->rest) return Seq(new LSeq(l->rest)); return Seq(); }

}
