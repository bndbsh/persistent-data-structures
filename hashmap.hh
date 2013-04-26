#ifndef _XT_HASHMAP_HH_
#define _XT_HASHMAP_HH_

#include <memory>
#include "object.hh"

namespace xt {

class _INode;
typedef std::shared_ptr<_INode> INode;
class _INode : public std::enable_shared_from_this {
	INode assoc(int shift, int hash, Object key, Object val, Object leaf) = 0;
};

struct _HashMap {
	const int count;
	const bool hasNil;
	const Object nilValue;
};

typedef std::shared_ptr<_HashMap> HashMap;

}

#endif
