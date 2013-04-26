#ifndef _XT_SEQ_HH_
#define _XT_SEQ_HH_

#include "object.hh"

namespace xt {

class ISeq;
typedef std::shared_ptr<ISeq> Seq;
class ISeq {
public:
	virtual Object first() const = 0;
	virtual Seq next() const = 0;
};

namespace seq {

bool contains(Seq s, Object o);
int index_of(Seq s, Object o);

}

}

#endif
