## multiple choice
1. b, only traversing pointer index
2. a
`throw s;` could create slicing and change actual type of exception
`throw new Exception{s};` is syntactically wrong, not just slicing, dont create heap allocated exception to throw

## true false
1. true
2. false
auto lets user get auto typing, example: `for (auto v : list)`, **automatically set type on the left hand side of `assignment =` to be the type of the object on the right hand side of `assignment =`**

3. false
composition is "owns a", when A deleted, B is deleted, B doesnt exist outside A
aggregation is "has a", when A

4. true

5. false
1) space allocated
2) superclass ctor invoked
3) subclass fields created in declaration order (not MIL order)
4) ctor body runs

6. true
7. true
8. false
abstract class is a class that has pure virtual function, abstract class is used to organize inheritance and cannot they instantiated (Student s)

9. false
exception safety is when exceptions happen, program dont crash on exception AND no data is corrupted AND don't have any memory leak

10. true
**low coupling high cohesion**


## short answer
1. because it allows child to access parent fields, this **violates encapsulation and invariants**, child can do whatever they want (mutate). Better to make private fields with protected getter() and setter()

2. polymorphism is when one promise/invariant is valid under multiple implementations across different classes. Virtual methods is example of polymorphism. **Accommodating multiple types under one abstration is called polymorphism**

3. so with polymorphism, when superclass ptr is destroyed, the actual dtor of the object will run, so child fields can be destroyed. Otherwise (with non-virtual dtor) only parent dtor will run and child fields will be leaked

4. 
``` c++
// Vec.h
class VecImpl;

class Vec {
    VecImpl *v;
public:
    Vec(int x = 0, int y = 0);
    int getX();
    int getY();
    ~Vec();
};

// VecImpl.h
// ================================ use struct for impl, to allow access to fields
// ================================ impl is used for private implementation, so if fields change, only need to compile Vec.cc, since it'll be the only field including VecImpl.h If impl not used, changes will be in Vec.h and every file that include Vec.h will need to recompile for any change
struct VecImpl {
    int x;
    int y;
};

// Vec.cc
#include "VecImpl.h"
#include "Vec.h"
Vec::Vec(int x = 0, int y = 0): v {new VecImpl {x, y}} {}

int Vec::getX() {
    return v->x;
}
int Vec::getY() {
    return v->y;
}
Vec::~Vec() {
    delete v;
}
```

5. 
rvalue reference "point"/refer to a rvalue, but the rvalue reference variable itself is a lvalue

6.
for lvalue object x, std::move(x) will treat x as rvalue

std::move() implementation
``` c++
template <typename T> typename
```

7. 
**partial assignment**, Book::operator=() runs because operator=() is not virtual


8. 
1) make parent **abstract class**, and parent operator= protected, only have public operator= in child
2) ***USE CASTING***

9. 
Not on final
won't compile, cuz 3 is int, 3.5f is float, not same type, so need to give <int> or <float> to template function explicitly. If they are same type, then don't need to give explicit type.

10.
no, if exception happen, pointer is not deleted, fix by putting pointer into smart pointer, so when stack is popped, pointer is automatically destroyed

11.

# program crash with basic gurantee?

1) basic gurantee: program will be in valid state after exception happen, no corrupted data, no leaked memory
2) strong gurantee: if exception throw, program is revert to state before function was run
3) no throw gurantee: no exception will ever be thrown, task will always be completed


12. 
1) too powerful, could be easily abused
2) hard to find c style casting in debugging `<new_type>`
