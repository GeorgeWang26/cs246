# Midterm Review

## True or False
1. True
2. False
3. True
4. True
5. False
6. False
7. False --
8. True syntax for `int * &y`

## Bash
1. `ls -p | grep -v "/"` to display only files in current directory

2. `$(())` need double (()) to perform arithmetic operations

3. "^(https://)?(www\.)?fredd(d)*yfreaker\.gov/blod\?post=[0-9][0-9]?[0-9]?$"

4. `ls *.txt` or `ls | grep "\.txt$"`

5. `ls abc.[x-zX-Z][x-zX-Z][x-zX-Z]` or `ls | egrep "^abc\.[x-zX-Z][x-zX-Z][x-zX-Z]$"`

## Short Answer C++

member function takes struct in as first argument due to `this`  
operator<< as a member function will need obj to be on left side of operator, so it works like `obj << stream` and `obj2 << (obj1 << stream)` instead of `stream << obj`  
operator+ as a member function takes struct in as both first and second argument, so doesnt matter if it's `obj1 + obj2` or 'obj2 + obj1`

``` c++
ostream & operator<< (ostream & out, const Node &n) {
    for (const Node *np = &n; np; np = np->next) {
        out << np->data << endl;
    }
    return out;
}
```


``` c++
Node operator* (const Node & n, int a) {
    Node rn = n;  // this is copy ctor even it uses = at declaration
    for (Node *np = &rn; np; np = np->next) {
        np->data *= a;
    }
    return rn;
}

Node operator* (int a, Node & n) {
    return n * a;
}
```


## Full Answer C++
``` c++
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *args) {
    ifstream f {"words.txt"};
    string word
    while (f >> word) {        
        cout << word << endl;
    }
}
```


``` c++
#ifndef MARIO_H
#define MARIO_H
#include <string>
Struct Mario {
    int x, y, speed;
    std::string form;
    
    Mario(int x, int y, std::string form);

    explicit Mario(std::string form);

    void takeDamage();
};
#endif
```


``` c++
Struct Yakuza {
    Yakuza * subordinates[5];
    string name;
    string title;
    int numSubords;

    Yakuza(string name, string title);
    
    ~Yakuza();
    Yakuza(Yakuza &other);
    Yakuza(Yakuza &&other);

    Yakuza & operator= (const Yakuza &other);
    Yakuza & operator= (Yakuza &&other);

    void swap(Yakuza &other);
    bool add(string name);
    bool remove(string name);
};

Yakuza::~Yakuza() {
    for (int i = 0; i < numSubords; i++) {
        delete subordinates[i];
    }
}

Yazuka::Yakuza(const Yakuza &other) : name{other.name}, title{other.title}, numSubords{other.numSubords} {
    for (int i = 0; i < other.numSubords; i++) {
        subordinates[i] = new Yakuza {other.subordinates[i]}
    }
}

Yakuza::Yakuza(Yakuza && other) : name{other.name}, title{other.title}, numSubords{other.numSubords} {
    for (int i = 0; i < numSubords; i++) {
        subordinates[i] = other.subordinates[i];
        other.subordinates[i] = nullptr;
    }
}

Yakuza & Yakuza::operator= (const Yakuza &other) {
    Yakuza tmp = other;
    swap(tmp);
    return &this;
}

Yakuza & Yakuza::operator= (Yakuza &&other) {
    swap(other);
    return &this;
}

void Yakuza::swap(Yakuza &other) {
    using std::swap;  // important
    // swap all fields
    swap(name, other.name);
    swap(title, other.title);
    swap(subordinates, other.subordinates);
    swap(numSubords, other.numSubords);
}
```
