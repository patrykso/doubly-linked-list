# doubly-linked-list
### Implementation of doubly linked list made for university purposes.
\
**Interface:**
\
`i x y` - Initialize the x-th iterator to the position y. The value of y can be either BEG (beginning), END or a number of other iterator. The iterators (except BEG and END) are labeled from 0 to 9.
\
`+ x` - Move the x-th iterator forward. If moving forward is impossible, iterator will point to the last element.
\
`- x` - Move the x-th iterator backward. If moving backward is impossible, iterator will point to the first element.
\
`.A x y` - Add the number y before the position x. X can be either BEG, END, or a number of iterator.
\
`A. x y` - Add the number y after the position x. X can be either BEG, END, or a number of iterator.
\
`R x` - Remove an element given by the position x. X can be either BEG, END, or a number of iterator. If an element is removed, then all iterators pointing at it are going to point to the next element. In case of last element being removed, all iterators pointing to old last element are going to point to the new last element. In case of removing last element from the list, iterators will become uninitialized.
\
`P z` - Print the number on the position given by z. Z can be ALL or a number of iterator.