
#include "vector.hh"
#include "exceptions.hh"

namespace xt {
TypeInfo _Vector::type_info { "Vector" };
TypeInfo _Node::type_info { "VectorNode" };
namespace vector {

static Node EMPTY_NODE;
static Vector EMPTY;

Vector vec(List list) {
	if (list->count == 0) return empty();
	Vector ret = vector::conj(list->first);
	List n = list->rest;
	while (n && n->count) {
		ret = conj(ret, n->first);
		n = n->rest;
	}
	return ret;
	
}

unsigned int tailoff(Vector v) {
	if (v->cnt < 32) return 0;
	return ((v->cnt-1) >> 5) << 5;
}

Node empty_node() {
	if (!EMPTY_NODE) {
		EMPTY_NODE = Node(new _Node {new_object_array(32)});
	}
	return EMPTY_NODE;
}

Vector empty() {
	if (!EMPTY) {
		EMPTY = Vector(new _Vector {0, 5, empty_node(), new_object_array()});
	}
	return EMPTY;
}

ObjectArray arrayFor(Vector v, unsigned int i) {
	if (i < v->cnt) {
		if (i >= tailoff(v)) return v->tail;
		Node node = v->root;
		for (int level = v->shift; level > 0; level -= 5)
			node = to_node((*node->array)[(i >> level) & 0x01f]);
		return node->array;
	}
	throw RuntimeException("Index out of bounds");
}

Object nth(Vector v, unsigned int i) {
	return (*arrayFor(v, i))[i & 0x01f];
}

Object nth(Vector v, unsigned int i, Object notFound) {
	if (i < v->cnt) return nth(v, i);
	return notFound;
}

Node doAssoc(unsigned int level, Node node, unsigned int i, Object val) {
	Node ret = Node(new _Node {new_object_array(32)});
	std::copy(node->array->begin(), node->array->end(), ret->array->begin());
	if (level == 0)
		(*ret->array)[i & 0x01f] = val;
	else {
		unsigned int subidx = (i >> level) & 0x01f;
		(*ret->array)[subidx] = doAssoc(level - 5, to_node((*node->array)[subidx]), i, val);
	}
	return ret;
}

Object assocN(Vector v, unsigned int i, Object val) {
	if (i < v->cnt) {
		if (i >= tailoff(v)) {
			ObjectArray newTail = new_object_array(v->tail->size());
			*newTail = *v->tail;
			(*newTail)[i & 0x01f] = val;
			return Vector(new _Vector {v->cnt, v->shift, v->root, newTail});
		}
		return Vector(new _Vector {v->cnt, v->shift, doAssoc(v->shift, v->root, i, val), v->tail});
	}
	if (i == v->cnt) return conj(v, val);
	throw RuntimeException("Index out of bounds");
}

Node newPath(unsigned int level, Node node) {
	if (level == 0) return node;
	Node ret = Node(new _Node);
	(*ret->array)[0] = newPath(level - 5, node);
	return ret;
}

Node pushTail(Vector v, unsigned int level, Node parent, Node tailnode) {
	unsigned int subidx = ((v->cnt -1) >> level) & 0x01f;
	Node ret = Node(new _Node);
	std::copy(parent->array->begin(), parent->array->end(), ret->array->begin());
	Node nodeToInsert;
	if (level == 5)
		nodeToInsert = tailnode;
	else {
		Node child = to_node((*parent->array)[subidx]);
		nodeToInsert = (child != nullptr) ? pushTail(v, level - 5, child, tailnode) : newPath(level - 5, tailnode);
	}
	(*ret->array)[subidx] = nodeToInsert;
	return ret;
}

Vector conj(Object val) {
	return conj(empty(), val);
}

Vector conj(Vector v, Object val) {
	if (v->cnt - tailoff(v) < 32) {
		ObjectArray newTail = new_object_array(v->tail->size()+1);
		*newTail = *v->tail;
		newTail->push_back(val);
		return Vector(new _Vector {v->cnt + 1, v->shift, v->root, newTail});
	}
	Node newroot;
	Node tailnode = Node(new _Node { v->tail });
	unsigned int newshift = v->shift;
	if ((v->cnt >> 5) > (1 << v->shift)) {
		newroot = Node(new _Node);
		(*newroot->array)[0] = v->root;
		(*newroot->array)[1] = newPath(v->shift, tailnode);
		newshift += 5;
	}
	else newroot = pushTail(v, v->shift, v->root, tailnode);
	return Vector(new _Vector {v->cnt+1, newshift, newroot, ObjectArray(new _ObjectArray{val})});
}

}

Object VSeq::first() const { return vector::nth(v, index); }
Seq VSeq::next() const { if (index+1 < v->cnt) return Seq(new VSeq(v, index+1));  return Seq(); }

}
