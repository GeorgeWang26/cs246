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
```

correct version of neg, for each function call is chosen by the compiler (ie: at compile time), based on the number & types of the args in the function call

Overloads must differ in number OR types of args. Just differing in the return type is NOT enough.

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
References are like const ptrs with automatic dereferencing.  
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
    - this will compile but means something different (later)
- create an array of references, ~~`int &r[3] = {..., ..., ...};`~~

What **CAN** you do?
- pass as function params
    - `void inc (int &n) {++n;}`
        - `int &n`: const ptr to the argument x, changes to n affect x
        - `++n;`: no ptr dereference needed

``` c++
int x = 5;
// act like pass by reference, but C++ is still pass by value
inc(x);
cout << x;  // 6
```

Why does `cin >> x` work? It takes x by reference!

Function declaration of operator `>>` when reading int, takes n as reference. Cannot pass streams by value, always pass their reference (const ptr)
``` c++
istream &operator >> (istream &int, int &n);
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