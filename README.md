
# Slippy's Math Library

A simple C++ math library without overuse of templates. Made for the purpose of making game engines, though it is not particularly optimized.

Any suggestions or contributions on making this better are welcome. 

This library was made for readability, ease of use, and easy debugging. Rather than efficiency and flexibility, I preferred to make something I could _read_ and _improve_ on demand. C++ is already a pretty hard language to debug – creating tons of templates and macros only worsens that fact.

## Usage details

This library has some peculiarities that should be useful for development.

### Mutability & Immutability

All structures have copy-return immutable methods and operators as well as their inline mutable counterparts. I differentiate them by using imperative verbs for mutable methods (non const) and past-participle-tense for immutable ones (const).

Example:

```C++

Vec3 a{1, 2, 3};
Vec3 b{4, 5, 6};

// Both of these return a new Vec3 by copy.
// They don't alter 'a' or 'b' in any way.

Vec3 c = a + b; // 'c' is not 'a' nor 'b'
Vec3 d = a.translated(b); // 'd' is not 'a nor b'

// These, however, alter 'a' and 'b'.
// They also return their references so you can chain them.

Vec3& a_ref = a.translate(b); // returns 'a&'
Vec3& c_ref = c.translate(d).scale(2); // returns 'c&'
Vec3& b_ref = (b += c); // returns 'b&'

/* 

// You also can't use mutable methods in const objects (obviously)

const Vec3 immutable_zero{0, 0, 0};

// This line won't compile.
immutable_zero.translate(Vec3{1, 0, 0});

// This line, however, will.
const Vec3 immutable_x = immutable_zero.translated(Vec3{1, 0, 0}); 

*/
```
