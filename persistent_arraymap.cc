
#include "persistent_arraymap.hh"

#include <cstdlib>


namespace xt {
namespace map {

// static ArrayMap* empty_arraymap = nullptr;
// 
// ArrayMap* new_arraymap(XT_State* xt, Array* array) {
// // 	ArrayMap* map = (ArrayMap*)xt_gc_alloc(xt, sizeof(arraymap), Type::Map);
// 	auto map = xt::gc::alloc<ArrayMap>(xt, Type::Map);
// 	map->array = array;
// 	xt::gc::link(xt, obj2gco(map));
// 	return map;
// }
// 
// ArrayMap* empty(XT_State* xt) {
// 	if (!empty_arraymap) empty_arraymap = new_arraymap(xt, array_new(xt, 32));
// 	return empty_arraymap;
// }
// 
// int indexOf(ArrayMap* map, xt_value* key) {
// 	int i;
// 	for (i = 0; i < map->array->count; i+=2) {
// 		if (xt_equiv(key, array_get(map->array, i))) return i;
// 	}
// 	return -1;
// }
// 
// xt_value* getik(ArrayMap* map, int idx) {
// 	return array_get(map->array, idx*2);
// }
// 
// xt_value* getiv(ArrayMap* map, int idx) {
// 	return array_get(map->array, (idx*2)+1);
// }
// 
// ArrayMap* assoc(XT_State* xt, ArrayMap* map, xt_value* key, xt_value* val) {
// 	int i = indexOf(map, key);
// 	Array* newarray;
// 	if (i >= 0) {
// 		if (xt_equiv(array_get(map->array, i+1), val)) return map;
// 		newarray = array_copy(xt, map->array);
// 		array_append(newarray, key);
// 		array_append(newarray, val);
// 	} else {
// 		newarray = array_copy(xt, map->array);
// 		array_append(newarray, key);
// 		array_append(newarray, val);
// 	}
// 	return new_arraymap(xt, newarray);
// }
// 
// int len(ArrayMap* map) {
// 	return map->array->count/2;
// }
// 
// xt_value* get(ArrayMap* map, xt_value* key) {
// 	int i = indexOf(map, key);
// 	if (i >= 0) return array_get(map->array, i+1);
// 	return nil_value();
// }

}
}
