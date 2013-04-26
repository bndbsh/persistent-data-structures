
#include "seq.hh"

namespace xt {
namespace seq {

bool contains(Seq s, Object o) {
	while (s) {
		if (s->first() == o) return true;
		s = s->next();
	}
	return false;
}

int index_of(Seq s, Object o) {
	int idx = 0;
	while (s) {
		if (s->first() == o) return idx;
		idx++;
		s = s->next();
	}
	return -1;
}

}
}