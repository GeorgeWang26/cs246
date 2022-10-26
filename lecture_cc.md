# Lecture 4

## Hello World
``` c++
#include <iostream>
using namespace std;

int main() {
    cout << "Hellow World!" << endl;  // endl will insert newline and flush the buffer
    return 0;   # could be ommited
}
```

## Compiling C++ program
```
g++ -std=c++14 -Wall -g program.cc -o myprogram
g++14 program.cc -o myprogram  # if g14 is alaised 

-Wall: warning
-g: debugging information
-o myprogram: rename executable, default a.out
-c: generate object files
```

## Input/Output
3 I/O stream:  
`cout/cerr` - printing to stdout/strderr  
`cin` - reading from stdin  

2 I/O operators:  
`<<` - outoput  
`>>` - input  

**Note**: `cin` skips leading whitespace (space/tab/newline) like scanf  

Adding 2 numbers
``` c++
// these two lines will be ommited in later exampels
#include <iostream>
using namespace std;

int main() {
    int x y;
    cin >> x >> y;  // x will be the first number, read from left to right
    cout << x + y << endl;
}
```

### Input fails
If the read failed: `cin.fail()` => true  
If it failed because EOF: `cin.fail()` and `cin.eof()` => true  
But NOT until the attempted read fails

**Note**:  
- there is an implicit conversion from `cin` to bool type. Let `cin` be used as a condition. `!cin` == `cin.fail()`  
- `cin` returns a non-null pointer or true if strem is valid. Otherwise it returns a null pointer or false if stream is invalid (failed)
- Since `cin >> var` returns `cin`, so it can be used as a condition as well

Read all ints from stdin & echo them, one per line, to stdout. Stop on bad input or EOF
``` c++
int main() {
    int i;
    while (true) {
        cin >> i;
        if (!cin) break;  // equivalent to cin.fail()
        // could be simplified to "if (cin >> i)" to both read and check input validity
        cout << i << endl;
    }
}
```


# Lecture 5

## >>
`>>` is right bit shift operator in C/C++  
`a >> b` shifts a's bits to the right by b places  
Ex: `21 >> 3` => 2. Because 21 = 1010 becomes 10 after right shift by 3 bits.

But when the LHS is a stream, `>>` is the input operator. operator >> arguments  
- operator: `cin` (input stream)
- arguments: data (several possible types)
- return value: gives back `cin` (istream)
    - this is why we can write `cin >> x >> y >> z`, it read from left to right, so it becomes `cin >> y >> z` => `cin >> z` => `cin`

Read all ints & echo to stdout until EOF. Skip non-integer input
``` c++
int main() {
    int i;
    while (true) {
        if (!(cin >> i)) {
            if (cin.eof()) break;
            // after cin fails, need to manually reset error flg for cin to read ANYTHING again
            cin.clear();
            // throw away chars, defaul to 1 char
            cin.ignore();
        }
    }
}
```

## IO manipulator
``` c++
cout << 95;  // prints 95
cout << hex << 95;  // prints 5f, hex representation of 95
cout << 14;  // prints e, cin still in hex mode
cout << dec << 14;  // prints 14
cout << 20;  // prints 20, still in dec mode
```

## Strings
C string: array of char (`char *` or `char []`) terminated by \0
- must explicitly manage memory, allocate more memory as string gets larger
- easy to overwite \0, and will corrupt memory

C++ string: `#include <string>` with type `std::string`
- grow as needed (no need to manage memory)
- safer to manipulate

Ex: `string s = "hello";`  
C++ string created from a C string, char array of {H, e, l, l, o, \0}, on initialization

### String operations
- string equality
    - ~~`strcmp(s1, s2)` in C~~
    - `s1 == s2`, `s1 != s2`
- string comparison (lexicographical order)
    - ~~`strcmp(s1, s2)` in C~~
    - `s1 <= s2`, etc.
- string length
    - ~~`strlen(s)` in C~~
    - `s.length()`, with O(1) time. Can now be used as condition in loops
- fetching individual characters
    - same as in C, [index], s[0], s[1], s[2], ...
- concatenation
    - ~~`strcat(s1, s2)` in C~~
    - `s3 = s1 + s2`, `s4 += s5`

``` c++
int main() {
    string s;
    cin >> s;
    cout << s << endl;
}
```
reading string with `cin` stop at whitespace. So it can only read single word at a time. Leading space/tab/newline are ignored.

What if we want the spaces? Use `getline(cin, s);`
- reads from current position to the next newline into s

## Stream abstraction
Streams abstraction applies to other sources of data

Stream is like a queue, first in first out, so if a general stream is defined (can both write to << and read from >>), then which ever was written first will be read first.

### File as stream
Read from a file instead of from stdin, `#include <fstream>`
- `std::ifstream` - file for reading
- `std::ofstream` - file for writting

File access in C
``` c
#include <stdio.h>

int main() {
    char s[256];
    FILE *f = fopen("file.txt", "r");
    while (true) {
        fscanf(f, "%255s", s);
        if (feof(f)) break;
        printf("%s\n", s);
    }
    fclose(f);
}
```

File access in C++
``` c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // declare & defined the ifstream variable f, opens the file stream
    ifstream f {"file.txt"};
    string s;
    while (f >> s) {
        cout << s << endl;
    }
}
// file stream is automatically closed when f goes out of scope (main in this example)
```
Anything you can do with cin/cout, you can do with ifstream/ofstream
### String as stream
attach a stream to a string variable & read from/write to a string, `#include <sstream>`
- `std::istringstream` - read from string
- `std::ostringstream` - write to string

This is very useful for type casting, int/double/float/... <-> string
``` c++
string intToString(int n) {
    ostringstream sock;
    sock << n;
    // pass by reference, just like dynamic allocation
    // string created from stream live outside scope
    return sock.str();
}

voic stringToInt(){
    int n;
    while (true) {
        cout << "Enter a numer " << endl;
        string s;
        cin >> s;
        istringstream sock {s};
        if (sock >> n) break;
        cout << "I said, ";
    }
    cout << "You entered " << n << endl;
}
```

Example revisited, echo all numbers, skip non-nums
``` c++
int main() {
    string s;
    while (cin >> s) {
        // no need for stream.clear() and stream.ignore()
        // stream is automatically closed and redefiend each iteration
        istringstream sock {s};
        int n;
        if (sock >> n) cout << n << endl;
    }
}
```

## Default function params
``` c++
void printSuiteFile(stirng name = "suite.txt") {
    ifstream f {name};
    string s;
    while (f >> s) cout << s << endl;
}
printSuiteFile("suite2.txt");
printSuiteFile();  // uses default param "suite.txt"
```

**Note**: optinal parameters MUST be last!!!


# Lecture 6

## Overloading
in C
``` c
int negint (int n) {return -n;}
bool negBool (bool b) {return !b;}
```

in C++: Fucntions with different param lists can share the same name
``` c++
int neg(int n) {return -n;}
bool neg (bool b) {return !b;}

// different args order
void foo (int a, double b);
void foo (double b, int a);
```

correct version of neg, for each function call is chosen by the compiler (ie: at compile time), based on the number & types of the args in the function call

Overloads must differ in number OR types of args OR order of args. Just differing in the return type is NOT enough.  

We've seen this already: 
- `>>`, `<<` are overloaded
    - can be used as bitshift and input/output. Behaviour depends on types of args.
- `+`
    - can add numbers and concatenate strings depending on types of args.


## Structs
``` c++
struct Node {
    int data;
    // struct Node *next;
    Node *next;  // keyword "struct" is not needed in C++
};  // don't forget the semicolon
```

This is wrong, can't have struct in struct. Only struct pointer is allowed in struct.
``` c++
struct Node {
    int data;
    Node next;
};
```

Ways to initialize/define struct in C++14  
Lines that are commented out are invalid. (this is asked on piazza, update answers here)
``` c++
Vec a = {1, 2};
// Vec b = (1, 2);
Vec c {1, 2};
// Vec d (1, 2);
Vec e = a;
Vec f {a};
Vec g (a);
Vec h = {a};
Vec i = (a);
```

## Constants
``` c++
// constants must be initialized
const int maxGrade = 100;
```

declare as many things const as you can, help catch errors.

`NULL` is a constant defined as 0, so it is still int type at its heart. `nullptr` has pointer type.
``` c++
// syntax for null ptrs in c++
// Do not use NULL or 0
Node n {5, nullptr};
// immutable copy of n, can't change n2's fields
const Node n2 = n;
```


## Parameter Passing
Pass by value: 
- inc recieves a *copy* of x, mutates the copy
- original x unchanged
``` c++
void inc(int n) {++n;}
...
int x = 5;
inc(x);
cout << x;  // 5
```

Pass by reference:
- if a function needs to mutate an argument, pass a pointer
``` c++
void inc(int *n) {++*n;}
...
int x = 5;
// x's address passed by value
// inc changes the data at that address, which is visible to the caller
inc(&x);
cout << x;  // 6
```

## Refereces - Important
Q: Why `cin >> x` and not `cin >> &x`?  
A: C++ has another ptr-like type, ***references***
``` c++
int y = 10;
// z is an "lvalue reference" to an int (y)
// like a constant ptr to y, similar to "int *const z = &y;"
int &z = y;

z = 12;  // NOT "*z = 12;"
// now y == 12
int *p = &z;  // gives the address of y
```
References are *like* const ptrs with automatic dereferencing.  
But references are **NOT** ptr. sizeof(reference) gives the size of the referenced object, instead of always 8, which is the size of a ptr.
- in all cases, z behaves exactly like y  
- z is an *alias* (another name) for y  

Things you **CANNOT** do with lvalue references:
- leave them uninitialized   ~~eg: `int &x;`~~
    - must be initialized with somthing that has an address (an *lvalue*), since references are ptrs
        - ~~`int &x = 3;`~~
        - ~~`int &x = y + z;`~~
        - `int &x = y;`
- create a ptr to a reference: ~~`int &*x;`~~ (read from right to left, x is a ptr to a reference to an int)
    - reference to ptr is OK
        - `int *&x = ...;` (x is a reference to a ptr to an int)
- create a reference to a reference, ~~`int &&r = ...;`~~
    - this will compile but means something different (rvalue reference)
- create an array of references, ~~`int &r[3] = {..., ..., ...};`~~

What **CAN** you do?
- pass as function params
    - `void inc (int &n) {++n;}`
        - `int &n`: like const ptr to the argument x, changes to n affect x
        - `++n;`: no ptr dereference needed

``` c++
int x = 5;
// act like pass by reference, but C++ is still pass by value
inc(x);
cout << x;  // 6
```

Why does `cin >> x` work? It takes x by reference!

Function declaration of operator `>>` when reading int, takes in as reference. Cannot pass streams by value, always pass their reference (like const ptr)
``` c++
istream & operator>> (istream &in, int &n);
```

Pass by value: `void f(int n)` copies the argument
- if the argument is big, copy is expensive

``` c++
struct ReallyBig {...};

// copy argument, slow
void f(ReallyBig rb) {...}

// alias, fast
// but could change rb in the caller
void g(ReallyBig &rb) {...}

// use alias, fast, no copy
// parameter cannot be changed
void h(const ReallyBig &rb) {...}
```

**Advice**: Prefer pass-by-const-reference over pass-by-reference for anything larger than a ptr. Unless the function needs to create a copy anyway, then just use pass-by-value

Also:
``` c++
int f(int &n) {...}
int g(const int &n) {...}
// can't initialize lvalue reference n to a literal value.
// if n changes, can't change the literal value 5.
f(5);  // WRONG

// since n can never be changed, compiler allows this.
// How? 5 sits in a temporary location for n to point at
g(5);  // OK
```

## Dynamic memory allocation
C (don't use these in C++):
``` c
int *p = malloc(num * sizeof(int));
...
free(p);
```

Instead: new/delete
- type aware, less error prone

``` c++
struct Node {
    int *data;
    Node *next;
};
Node *np = new Node;
...
delete np;
```

# Lecture 7

## Dynamic memory allocation ctd.
- all local variables reside on the stack
    - vars deallocated when they go out of scope (stack is popped)
- allocated memory (ie: the result of `new`) resides on the heap
    - remain allocated until `delete` is called
    - if you don't delete all allocated memory, it causes *memory leak* (this happend when function ends without returning allocated object)
        - program will eventually fail
        - we regard this as an incorrect program

Array on the heap:
``` c++
Node *nodeArray = new Node[10];
...
delete[] nodeArray;
```
Memory allocated with `new` must be freed with `delete`  
Memory allocated with `new type[size]` must be freed with `delete[]`  
Mixing these result in undefined bahaviour

## Return by value/ptr/ref
``` c++
// expensive - n is coped to the caller's stack frame on return
Node getMeANode() {
    Node n;
    return n;
}
```

return a ptr (or ref) insted?

``` c++
// BAD
// returns a ptr to stack-allocated data, which is dead on return
Node *getMeANode() {
    Node n;
    return &n;
}

// also BAD, for same reason
Node &getMeANode() {
    Node n;
    return n;
}
```

``` c++
// OK
// return a ptr to heap data, still alive
// But don't forget to delete it when done with it
Node *getMeANode() {
    return new Node;
}
```

Which should you pick? Return by value. Not as expensive as it looks. (we'll find out why later)


## Operator overloading
Give meanings to C++ operators for our own types
``` c++
struct Vec {
    int x, y;
};

Vec operator+(const Vec &v1, const Vec &v2) {
    Vec v {v1.x + v2.x, v1.y + v2.y};
    return v;
}

Vec operator*(const int k, const Vec &v) {
    // OK, because the compiler knows it's a Vec, based on the return type.
    return {k * v.x, k * v.y};
}

Vec operator*(const Vec &v, const int k) {
    return k * v;
}
```

### Special cases: overloading << and >>
ostream type include cout, cerr, ofstream, ostringstream, ...  
istream type include cin, ifstream, istringstream, ...
``` c++
struct Grade {
    int theGrade;
};

ostream &operator<<(ostream &out, const Grade &g) {
    out << g.theGrade << '%';
    return out;
}

istream &operator>>(istream &in, Grade &g) {
    in >> g.theGrade;
    if (g.theGrade < 0) g.theGrade = 0;
    if (g.theGrade > 100) g.theGrade = 100;
    return in;
}
```

## The preprocessor
Transforms the program before compiler sees it  
`#___`, pre processor directive (eg: `#include`)  

Including old C headers - new naming convention  
instead of `#inclyde <stdio.h>`, now `#include <cstdio>`

`define Var VALUE` sets a preprocessor variable, then all occurences of VAR in the source file are replaced with VALUE

``` c++
#define MAX 10
// transformed to "int x[10];"
int x [MAX];
```
use const definitions instead

``` c++
// sets variable FLAG, value is the empty string
#define FLAG
```

Defined constant useful for conditional compilation
``` c++
#define SECURITYLEVEL 1    (or 2)
#if SECURITYLEVEL == 1
    short int  // removed before compiler sees it if securitylevel != 1
#elif SECURITYLEVEL == 2
    long long int  // removed before compiler sees it if securitylevel != 2
#endif
    // type of varaible is defined based on #if
    // this is not possible with regular if-else
    publickey;
```

Special case:
``` c++
// never true, all inner text suppressed
// heavy duty "comment out"
// #if nests properly
#if 0
    ...
#endif
```

Can also define symbols via compiler arguments `g++ -DX=15`
``` c++
int main() {
    cout << X << endl;>>>>
}
```

`#ifdef NAME`, `#ifndef NAME`, true if the preprocessor variable NAME (has/has not) been defined

``` c++
int main() {
    #ifdef DEBUG
        cerr << "setting x=1\n";
    #endif
    int x = 1;
    while (x < 10) {
        ++x;
        #ifdef DEBUG
            cerr << "x is now" << x << endl;
        ##endif
    }
    cout << x << endl;
}
```


## Separate compilation
Split program into composable modules, which each provide
- **interface (.h files)**: type definitions, function headers
- **implementation (.cc file)**: full definitions for every provided function



# Lecture 8

## Separate compilation
Recall: interface + implementation

Note: 
- declaration: asserts existence, `int f(int x);`
- definition: full details, allocates space `int f(int x) {...}`

interface (vec.h)
``` c++
struct Vec {
    int x, y;
}
Vec operator+(const Vec & v1, const Vec & v2);
```

implementation (vec.cc)  
Recall: an entity can be declared many times, but defined only once.
``` c++
#include "vec.h"

Vec operator+(const Vec & v1, const Vec & v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}
```

main.cc
``` c++
#include "vec.h"

int main() {
    Vec v{1, 2};
    v = v + v;
    ...
}
```

compiling separately  
Note: .h file is not compiled by itself
``` bash
# -c: compile only, do not link, do not build executable
# produces object file (.o)
g++14 -c vec.cc
g++14 -c main.cc
# links oject files into executable
g++14 main.o vec.o -o main
./main
```

What happens if we change vec.cc?  
Only need to recompile vec.cc and relink (fast). Instead of compiling everything together (slow for large project)

What happens if we change vec.h?  
Need to recompile **both** vec.cc and main.cc (they both include vec.h), then relink  

### make
How can we keep track of dependencies and perform minimal recompilation?  
Linux tool: `make`

Create a `Makefile` that says which files depend on which other files:  
**NOTE:** Makefile does NOT recognize alias (eg: c++14)
``` makefile
# main: target
# main.o, vec.o: dependencies, main depends on these
main: main.o vec.o
    # recipe for building target from dependencies
    # must have one TAB for indent
    g++ main.o vec.o -o main

main.o: main.cc vec.h
    g++ -std=c++14 -c main.cc

vec.o: vec.cc vec.h
    g++ -std=c++14 -c vec.cc

# optional target
.PHONY: clean
clean: rm *.o main
```
Then from terminal: `make`. This build the whole project

Now change just vec.cc, then make
- compiles vec.cc only, *NOT* the whole project
- relinks

Command
- `make target` - builds the requested target. eg: `make clean`
- `make`, no target specified => build the first target

`make`
- builds main
    - What does main depend on?
        - recursively build the dependencies if necessary
- if a target is older than it's dependencies, it is rebuilt

ex: vec.cc changes
- newer than vec.o
- rebuild vec.o, now it's newer than main
- rebuild main

Add some variables:
``` makefile
CXX = g++ (compiler's name)
CXXFLAGS = -std=c++14 -Wall -g (compiler options)
OBJECTS = main.o vec.o
EXEC = main

${EXEC}: ${OBJECTS}
    ${CXX} ${OBJECTS} -o ${EXEC}

# Make "guesses" the right recipe
main.o: main.cc vec.h

vec.o: vec.cc vec.h

.PHONY: clean

clean:
    rm ${OBJECTS} ${EXEC}
```

**Biggest problem with writting Makefiles**
- writting dependencies & keeping them up to date

Can get help from g++ `g++ -MMD main.cc`
- creates main.o and main.d

contents in main.d
```
main.o: main.cc vec.h
```
Now just include whis into Makefile

``` makefile
CXX = g++ (compiler's name)
CXXFLAGS = -std=c++14 -Wall -g -MMD(compiler options)
OBJECTS = main.o vec.o  # depend on current project
EXEC = main  # depend on current project
DEPENDS = ${OBJECTS: .o = .d}

${EXEC}: ${OBJECTS}
    ${CXX} ${OBJECTS} -o ${EXEC}

-include  ${DEPENDS}

.PHONY: clean

clean:
    rm ${OBJECTS} ${EXEC}
```

As the project grows, only have to add .o files to the Makefile

### Global variable
What if we want a module to provide a global variable?  
abc.h
``` c++
// declaration AND definition
int globalNum;
```
Every file that includes abc.h will defines a separate globalNum
- program will NOT link

Solution: put the variable in a .cc  
abc.h
``` c++
// declaration, but NOT definition
extern int globalNum;
```

abc.cc
``` c++
// this is definition
int globalNum;
```

Suppose we write a linear algebra module:  
linalg.h
``` c++
#include "vec.h"
...
```

linalg.cc
``` c++
#include "linalg.h"
#include "vec.h"
...
```

main.cc
``` c++
#include "linalg.h"
#include "vec.h"
```

Won't compile  
linalg.h include vec.h, and in both linalg.cc and main.cc, vec.h is included again. So struct Vec is defined multiple time (twice). This is NOT allowed

Need to prevent files from being included more than once  
solution: `#include guard`

vec.h
``` c++
#ifndef VEC_H
#define VEC_H
// regular file contents
...
#endif
```

First time vec.h is included, the symbol VEC_H is not defined, so file is included.  
Subsequently when vec.h is included again, VEC_H is already defined, so contents of vec.h are suppressed

***Always*** put `#include guards` in .h files  

***Never*** 
- put `using namespace std;` in .h files
    - The `using` directive will be forced upon any client who includes the file
- compile .h files
- `#include` .cc files
    - will cause repeated definition




# Lecture 9
## Classes
Can put functions inside of structs  
student.h
``` c++
struct Student {
    int assns, mt, final;
    float grade;
};
```

student.cc
``` c++
#include "student.h"
// :: used when thing on left is class or namespace
float Student::grade() {
    return assns * 0.4 + mt * 0.2 + final * 0.4;
}

// client
// Student is the class, s is the object
Student s{60, 70, 80};
// s is the receiver object
cout << s.grade();
```

**Class** 
- essentially a structure type that can contain functions
- C++ does have a `class` keyword (will cover later)

**Object**
- instance of a class

**function in grade**
- called a member function (or method)

**::**
- called the scope resolution operator
- C::f means f in the context of class C
- :: is like . where the LHS is a class (or namespace) not an object

What do assns, mt, final mean in side of Student::grade?
- they are fields of the receier object, the object upon which grade was called

``` c++
Student s {...};
// uses s's assns, mt, final
s.grade();
```

Formally: methods (class functon) take a hidden extra param called `this`, which is a ptr to the reciever object

``` c++
s.grade();
// secretly takes in this = &s (is a pointer)
// but this cannot be passed explicitly
// nor can have this as an argument name

// can write
struct Student {
    ...
    // method defined inside struct def, instead of with :: from outside
    // Method body can be written within the class
    // will do this in class for brevity
    // should put bodies in .cc files
    // So only put initialization in struct in .h
    float grade() {
        return this->assns * 0.4 + this->mt * 0.2 + this->final * 0.4;
    }
};
```

## Initializing Ojects
`Student s {60, 70, 80};` OK, but limited

Better solution
- write a method that initializes a constructor (abbreviated as ctor)

``` c++
struct Student {
    int assns, mt, final;
    float grade();
    // no return type, ctor always return the type of struct (ie: struct Student)
    Student(int assns, int mt, int final);
};

Student::student(int assns, int mt, int final) {
    this->assns = assns;
    this->mt = mt;
    this->final = final;
}

Student s {60, 70, 80};
// this is better even tho have same syntax
// if a ctor has been defined, the parameters are passed as args to the ctor
// and C-style struct initialization is no longer available

// OR
Student s = Student {60, 70, 80};

// Heal allocation
Student *p = new Student {60, 70, 80};
```

Advantages of ctors:
- default params, overloading, sanity checks

``` c++
struct Student {
    ...
    Student (int assns = 0, int mt = 0, int final = 0) {
        this->assns = assns;
    }
};

Student s2 {70, 80};  // 70, 80, 0
Student s3;  // 0, 0, 0

// this is still valid, but OLD C++
Student s4 (10, 20);
// could even do 
int x {5};
```

**Note:** Every class comes with a default ctor (ctor with no agrs). It just default-constructs all fields that are OBJECTS (so int fields will be arbitrary).

``` c++
Vec v;  //default ctor (does nothing in this case)
// If Vec is a field in Student
Student s;
// If Student is a field in Vec
Vec v;
// Both will get Vec fields (int x, y) unknown
// and Student fields set to 0
```

But the built-in default ctor goes away if you write **any** ctor
``` c++
struct Vec {
    int x, y;
    Vec(int x, int y) {this->x = x; this->y = y;}
};
Vec v{1, 2};  // OK
Vec w;  // won't compile, cuz there is NO default ctor anymore
```

What if a class contains constants or refs?
Must be initialized
``` c++
struct MyStruct {
    // WONT COMPILE
    const int myConst;
    int & myRef;
};
```

``` c++
int z;
struct MyStruct {
    // will compile but is not good
    const int myConst = 5;
    int & myRef = z;
};
```
Does every instance of MyStruct need the same myConst?  
Probably not.

``` c++
struct Student {
    const int id;  // constant, but not the same for all students
    ...
}
```

Where do we initialize? Ctor body?  
ctor is too late, fields must be fully constructed by then.

What happens when an object is created?
1. Spaceis is allocated
2. fields are constructed in declaration order (ctors run for fields that are **objects**, so not int/double...)
3. ctor body runs

Need to put const initialization in 2)  
How? Member Initialization List (MIL)

``` c++
Student::Student(int id, int assns, int mt, int final) : id {id}, assns {assns}, mt {mt}, final {final}
{
// ctor body
}

// in MIL, the syntax is fields {parameter}
// if MIL present, then "this->fields = parameter;" is not needed
```
**Note:**
- can initialize any field this way, not just consts or refs
- Fields are always constructed in declaration order, even if the MIL orders them differently

MIL
- somtimes more efficient than setting fields in the body (otherwise, run default ctor in step2, then reassign in step3)
- this won't be affecting primitive data types (int, double, bool, ...), since they are NOT objects, they don't have default ctor

``` c++
struct Student {
    string name;
};
```

What if a field is initialized inline AND in the MIL?
``` c++
struct Vec {
    int x = 0, y = 0;
    Vec(int x) : x {x} {}
    // MIL takes precedence (field is not initialized twice)
};
```

Now consider
``` c++
Student s {60, 70, 80};
Student t = s;
```
- How does this initialization happen?
- the "copy constructor"
- for constructing one object as a copy of another

**Note:** Every class comes with 
- default ctor (lost if you write any ctor)
- copy ctor
- copy assignment operator
- destructor
- more constructor
- move assignment operator

Building your own copy ctor:
``` c++
struct Student {
    int assns, mt, final;
    ...
    // this is equivalent to built in copy ctor
    Student (const Student & other) : 
        assns {other.assns},
        mt {other.mt},
        final {other.final}
    {}
};
```

When is the built-in copy ctor not correct?


# Lecture 10

Consider
``` c++
struct Node {
    int data;
    Node *next;
};

Node *n = new Node {1, new Node {2, new Node {3, nullptr}}};
// both these are copy ctor
Node m = *n;
Node *p = new Node {*n};
```

In the memory:
- n is in stack, point to Node 1 in heap
- m is in stack is Node 1, which point to Node 2 in heap
- p is in stack, point to a different Node 1 in heap, that point to Node 2 in heap

Simply copy of fields => only the first node is actually copied (shallow copy)  
If you want a **deep copy** (copits the whole list) must write your own copy ctor

``` c++
Node::Node(const Node & other) :
    data {other.data},
    next {other.next ? new Node {*other.next} : nullptr}
{}

// new Node {*other.next}
// copy ctor call => recursion, copies the rest of the list
```

The copy ctor is called
1. When an object is initialized by another object of the same type
2. When an object is passed by value
3. When an object is returned by a function

This is true for now, more details soon

Note: be careful with ctors that can take **one** parameter

``` c++
Struct Node {
    ...
    Node (int data, Node *next = nullptr);
};
```

Single-arg ctors crate implicit conversions:
``` c++
Node n {4};
// But also
Node n = 4;  // implicit conversion from int to Node

// implicit conversion from c-string (const char *) to cpp-string (string)
string s = "Hello";


// Problem arises with
void f(Node n);
f(4);  // OK
// Takes away the compiler's ability to distinguish between int and Node
// therfore takes away its ability to tell you you've done something wrong
```

Disable the implicit conversion - makes the ctor explicit
``` c++
struct Node {
    ...
    explicit Node(int data, Node *next = nullptr);
};

Node n {4}; // OK
Node n = 4;  // won't compile
f(4);  // won't compile
f(Node {4});  // OK
```





# WTF???????? WHY IS SINGLEARG CTOR NOT MEANT TO BE NODE?







## Destructors
When an object is destroyed (stack: goes out of scope, heap: is deleted), a method called the destructor runs

When an object is destroyed:
1. dtor body runs
2. fields are destructed (ie: dtors are invoked for fields tht are objects) in reverse-declaration order (bottom up)
3. space deallocated

Built-in dtor => calls dtors for all fields that are objects

When do we need to write a dtor?

``` c++
Node *np = new Node {1, new Node {2, new Node {3, nullptr}}};
// If np goes out of scope
//      - the ptr is reclaimed (stack-allocated)
//      - the list is leaked
// If we say delete np
//      - calles *np's dtor, which does nothing.
//          First Node is freed, the rest of the list are leaked
```

Write a dtor to ensure the whole list is freed
``` c++
struct Node {
    ...
    ~Node() {
        delete next;
        // delete triggers dtor
        // recursively calls *next's dtor, so whole list is freed

        // delete nullptr is perfectly fine, safe, guranteed to do nothing
    }
};

Node *np = new Node {1, new Node {2, new Node {3, nullptr}}};
delete np;
// now this frees the whole list
```

## Copy assignment operator
``` c++
Student s {60, 70, 80};
Student s2 = s;  // copy ctor
Student s3;  // default ctor

// copy assignment operator - uses compiler-supplied default
s3 = s2;  // copy, but not a construction
```

May need to write your own:
``` c++
struct Node {
    ...
    // return type is Node& so that cascading works
    // ie: a = b = c = 4
    // NO MIL, cuz this is NOT ctor

    Node & operator=(const Node &other) {  // Dangerous
        data = other.data;
        // delete not needed for copy ctor
        // for copy assignment, fields already have value and can cause leak
        delete next;
        next = other.next ? New node {*other.next} : nullptr;
        return *this;
    }

    // Why dangerous?
    Node n {1, new Node {2, new Node {3, nullptr}}};
    n = n;
    // deletes n & tries to copy n to n
    // undefined behaviour
}
```

When writting operator= ALWAYS be sure it works for self-assignment

``` c++
Struct Node {
    ...
    Node & operator=(const Node & other) {
        if (this == &other) return *this;
        // proceed as before
    }
};
```

Better  
If `new` fails, Node will NOT have a corrupted `next` ptr
``` c++
Node & Node::operator=(const Node & other) {
    if (this == &other) return *this;
    Node *tmp = next;
    next = other.next ? new Node {*other.next} : nullptr;
    // if NEW fails, original list is still intact
    data = other.data;
    delete tmp;
    return &this;
}
```

# Lecture 11
Continue from last example: NEW may fail if left over memory is not enough

Alternative: copy & swap idiom
``` c++
#include <utility>
struct Node {
    ...
    void swap(Node &other) {
        using std::swap;
        swap(data, other.data);
        swap(next, other.next);
    }
    ...
    // writting copy ASSIGNMENT operator
    Node & operator= (const node &other) {
        // this usescopy CONSTRUCTOR
        Node tmp = other;
        // will this create shallow or deep copy?
        swap(tmp);
        return *this;
    }
    ...
};
```


## rvalues & rvalue reference
Recall: 
- An lvalue is anything with an address
- An lvalue reference (&) is like a const ptr with auto dereferencing
    - always initialized to an lvalue (unless is const &)

Consider:
``` c++
Node plusOne(Node n) {
    for (Node *p = n; p; p = o->next) {
        ++ p->data;
    }
    return n;
}
Node n {1, new Node {2, nullptr}};
Node n2 = plusOne(n);  // copy construction
```
- plusOne(n) is the "other" param in copy ctor def - reference to what?
- compiler creates a temporary object to hold the result of plusOne
- "other" in the copy ctor, is a ref to this temporary
- copy ctor deep-copies the data from this temporary

But
- the temporary is going to be discarded anyway, as soon as the statement `Node n2 = plusOne(n);` is done
- wasteful to have to copy data from the temp
- why not just steall it instead?

Node n2 = n;


C++ - rvalue reference Node && is a reference to a temporary object of type Node - need to be able to tell whether "other" is a ref to a temporary object (rvalue) or a standalone obj (an lvalue)

Version of the ctor that takes a Node&&  
Move ctor
``` c++
struct Node {
    ...
    Node (Node &&other) : //called a move ctor (steal other's data)
        data {oter.data},
        next {other.next}
    {
        other.next = nullptr;
    }

}
```

Similarly
``` c++
Node m;
m = plusOne(n);  // assignment from temporary (NOT CTOR)
```

Move assignment operator
``` c++
struct Node {
    ...
    Node & operator= (Node &&other) {
        // steal other's data
        // destroy my old
        // easy: swap without copy
        swap(other);
        return *this;
        // the temporary will be destroyed and take our old data with it
    }
}
```

## Copy/Move Elision
``` c++
Vec makeAVec() {
    return {0, 0};  // invoke ordinary ctor
}
Vec v = makeAVec();  // what runs? copy ctor? move ctor?
```

Compiling above example in g++, ONLY get the ordinary ctor, no copy ctor, no move ctor.

In some cases (which you don't need to know) the compiler is allowed to skip calling copy/move ctors (but doesn't have to)

In this example: makeAVec writes its result ({0, 0}) directly into the sapce occupied by v in the caller, rather than copy it later.

``` c++
// pass-by-value copy/move ctor
void f(Vec v);
// result of makeAVec() written directly into the param
// no copy or move
f(makeAVec());
```
This is allowed, even if dropping ctor calls would change the behaviour of the program (ex: if the ctor print something)

Only need to know that elision is possible. Don't need to know *when* it will run

If you want all your ctors to run: `g++14 -fno-elite-constructors`. But this can slow down your program, by making a bunch of ctor calls that wasn't used before

**In summary: Rule of 5 (Big 5)**  
If need to write any one of the following, then usually need to write **all** 5
1. copy ctor
2. copy assignment
3. move ctor
4. move assignment
5. destructor

Notice: `operator=` member functuon, not a standalone function

When an operator is declared as a member function, `this` plays the role of the first operand

``` c++
struct Vec {
    int x, y;
    ...
    Vec operator+ (const Vec &other) {
        return {x + other.x, y + other.y}
    }

    // member function
    // v * k, since this(Vec itself) is always first argument
    Vec operator* (const int k) {
        return {x * k, y * k};
    }
}
```

How would we implement `k * v`?  
Can't be a member func, first arg not Vec!  
Must be standalone!

``` c++
Vec perator* (const int k, const Vec &v) {
    return v * k;
}
```

## I/O operators
``` c++
struct Vec {
    ...
    ostream & operator<< (ostream &out) {
        return out << x << ' ' << y;
    }
};
```
Whats wrong with this? Makes vec the first operand, not the second. So it is used as v << cout, v << (w << cout)

So define <<, >> as standalone

Certain operators **MUST** be members:
- operator=
- operator[]
- operator->
- operator()
- operator T      (where is T is a type, ie: "bool(stream)" will be defined as "operator bool")

## Arrays of Objects
``` c++
struct Vec {
    int x, y;
    Vec (int x, int y) : x{x}, y{y} {};
}
// Error!
// Both these want to call the default ctor on each item
// If no default ctor is defined => can't initialize items => error
Vec *p = new Vec[10];
Vec arr[10];
```

Options:
1. write a default ctor
2. For stack arrays:  
`Vec arr[3] = {{0, 0}, {1, 1}, {2, 4}};`
3. For heap arrays:  
create an array of ptrs  
``` c++
Vec **vp = new Vec*[5];
vp[0] = new Vec {0, 0};
vp[1] = new Vec {1, 1};
...
for (int i = 0; i < 5; i++) {
    delete vp[i];
}
delete[] vp;
```


# Lecture 12
## Const objects
`int f(const Node &n) {...}`  
Const objects arise often, especially as params

What is a const object?  
Can't modify fields

Can we call methods on a const object?  
Issus: method may modify fields, which would violate const  
Yes! We can call methods tht **promise** not to modify fields.

### Const method
``` c++
struct Student {
    int assns, mt, final;
    // this method doesn't modify fields, so declare it const
    float grade() const;
};
```
Compiler checks that const methods don't modify fields. Only const methods can be called on const objects.

### Mutable field
Now consider: want to collect usage stats on student objects
``` c++
struct Student {
    int assns, mt, final;
    int numMethodCalls = 0;
    float grade() const {
        // will result compiling error
        ++numMethodCalls;
        return ...;
    }
};
```

Now can't call grade on const students  
Mutating numMethodCalls affects only the physical constness of the object (whether the bit pattern has changed).  
But **not** the logical constness (whether the obkect should still be considered the same)

Want to be able to update numMethodCalls, even if the obj is const.  
Declare the field `mutable`

``` c++
struct Student {
    // can be changed, even if the obj is const
    mutable int numMethodCalls = 0;
    float grade() const {
        ++numMethodCalls;
        return ...;
    }
};
```

## Static fields & methods
numMethodCalls tracked the number of times a method was called on a **particular** object.

What if we want to track the number of times a method is called over **all** Student objects?

Or what if we want to track how many students are created?

**Static members** are associated with the class itself, not with any specific instance (object)

constness 

``` c++
struct Student {
    ...
    static int numInstances;
    // ctor
    Student() : ... {
        ++numInstances;
    }
};

int Student::numInstances = 0;  // in a .cc file
// static fields must be defined external to the class
```

global variables need to have extern to only have declaration and NOT definition

static follow it's own rules


int Student::numInstances = 0;  // in a .cc file
CANT BE IN HEADER WITH INCLUDE GUARD
INCLUDE GUARD ONLY PREVENT INCLUDE TWICE IN SAME FILE BUT ALLOWS INCLUDE IN DIFFERENT FILE (NOT WANTED WITH STATIC FIELD)


### Static member functions
- don't depend on the specific instance (no `this` as hidden first parameter)
- can only access static fields & call other static methods

``` c++
struct Student {
    ...
    static int numInstances;
    ...
    static void howMany() {
        cout << numInstances << end;
    }
};

Student s1 {60, 70, 80}, s2 {70, 80, 90};

Student::howMany();  // 2
```

Can access static fields & methods with class name directly `class::field` `class::method()`

---
midterm cutoff
---


## Invariants & Encapsulation
Recall:
``` c++
struct Node {
    int data;
    Node *next;
    ...
    ~Node() {delete next;};
};

Node n1 {1, new Node {2, nullptr}};
Node n2 {3, nullptr};
// ERROR
Node n3 {4, &n2};
```

What happens when these go out of scope?  
- n1 - dtor runs, entire list is deleted. OK
- n2, n3 - n3's dtor tries to delete n2, but n2 is on stack, not the heap! Undefined behaviour!

Class Node relies on an assumption for its proper operation, that next is either nullptr or is allocated by new

This assumption is an example of an **invariant** - statement that must hold true - upon which Node relies

But we can't gurantee this invariant, because we can't trust the use to use Node properly

Ex: stack provides an invariant
- last item pushed is the first item popped
- but not if the client can rearrange the underlying data

Hard to reason about programs if you can't rely on invariants

To enforce invariants, we introduce **encapsulation**
- want clients to treat objects as black boxes (capsules)
- creates an abstraction
    - seal away implementation
    - only interact via provided methods
- regains control over our objects

Ex:
``` c++
struct vec {
    // default visibility is public
    Vec(int x, int y);
    
    private:
        // only accessible within vec
        int x, y;
    
    public:
        // anyone can access
        Vec operator+ (const Vec &other);
    ...
};
```

In general: want private fields; only methods should be public

Better to have default visibility be private, but we can't do that (c++ carry struct from c, where all struct attributes are public)

Static also obey public/private visibility rules in struct


## Class
Switch from `struct` to `class`. Class have everything default to private
``` c++
class Vec {
    int x, y;
    
    public:
        Vec(int x, int y);
        Vec operator+ (const Vec &other);
};
```

Difference between struct & class is **default visibility**
- public in struct
- private in class

Let's fix our linked list class

list.h
``` c++
class List {
    // private nested class List::Node
    // not accessible outside List
    struct Node;
    Node *theList = nullptr;
    int length = 0;

    public:
        void addToFront(int n) {
        // obj.ith(5) = 10;
        int &ith (int i);
        ~List();
    }
};
```

list.cc
``` c++
#include "list.h"

// nested class
struct List::Node {
    int data;
    Node *next;
    ...
    ~Node() {delete next;}
};

void List::addToFront(int n) {
    theList = new Node {n, theList};
    ++length;
}

int &List::ith(int i) {
    Node *cur = theList;
    for (int n = 0; n < i; ++n) {
        cur = cur->next;
    }
    return cur->data;
}
```
# ASK SWAP
