C++ implementations of Clojure's [persistent data structures](http://clojure.org/data_structures).

Like their Clojure counterparts, these structures are dynamic. They are accessed via smart pointers and all memory is managed.

Based on the Clojure [implementation](http://github.com/clojure/clojure).

Statically typed versions with better runtime guarantees are planned, depending on how this pans out.

The implementations aren't yet complete.

# Usage

## Vector

`v = xt::vector::vec({1, 2, 3}) => [1, 2, 3]`

`v2 = xt::vector::conj(v, 4) => [1, 2, 3, 4]`

`v3 = xt::vector::assocN(v, 1, 5) => [1, 5, 3]`

`xt::vector::nth(v, 1)  => 2`

`xt::vector::vec({v, v2, v3}) => [[1, 2, 3], [1, 2, 3, 4], [1, 5, 3]]`

`for (int i = 0; i < xt::vector::len(v); ++i) xt::vector::nth(i);`
