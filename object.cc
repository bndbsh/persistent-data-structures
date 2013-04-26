#include "object.hh"

namespace xt {

// // static TypeInfo number_type  = TypeInfo { "Number" };
// TypeInfo bool_type;
// TypeInfo char_type;
// TypeInfo nil_type;

ObjectArray new_object_array(unsigned int size) {
	auto o = ObjectArray(new std::vector<Object>);
	if (size != 0) o->reserve(size);
	return o;
}

Object::Object(const Object& o) {
	type = o.type;
	if (type == Type::Boolean) b = o.b;
	if (type == Type::Number) number = o.number;
	if (type == Type::Char) ch = o.ch;
	if (type == Type::Pointer) new (&ptr) std::shared_ptr<void>(o.ptr);
	typeinfo = o.typeinfo;
}

Object& Object::operator=(const Object& o) {
	type = o.type;
	if (type == Type::Boolean) b = o.b;
	if (type == Type::Number) number = o.number;
	if (type == Type::Char) ch = o.ch;
	if (type == Type::Pointer) new (&ptr) std::shared_ptr<void>(o.ptr);
	typeinfo = o.typeinfo;
	return *this;
}

Object::operator bool() const {
	if (type == Type::Nil) return false;
	if (type == Type::Boolean) return b;
	if (type == Type::Number) return true;
	if (type == Type::Char) return true;
	if (type == Type::Pointer) return !!ptr;
	return false;
}


}
