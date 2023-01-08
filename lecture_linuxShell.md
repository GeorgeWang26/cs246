# Lecture 1
Shell
- interface to the OS
- get the OS to run programs, manage files, etc.
- graphical (click/touch)
- command line
    - type commands at a prompt
    - much more versatile

This couse: bash bshell, get shell type with `echo $0`

Files, input, output  
`cat` - displays the contents of a file

In Linux, directory is a special kind of file. In Linux, every line of a valid text file must end with a newline character, *INCLUDING THE LAST LINE* (marmoset checks for this)

`ls` - list files in the current dir (non-hidden files)  
`ls -a` - list all files (including hidden)

hidden files - name starts with `.` (dot)

`pwd` - prints current directory

What if you just type cat? Print everything you type, like echo bot.  
Useful? Maybe if we can capture the output in a file

Observe: `cat > myfile.txt`  
To stop: ^D (ctrl-D) at the beginning of a line, send an end-of-file (EOF) signal to cat

## Output redirection
In general, `command args > file`  
executes command args + captures the output in file instead of sending to the screen

## Input redirection
Can also redirect input `cat < file`  
- takes input from *file* instead of keyboard
- display contents of *file*
- **seems** equivalent to cast myfiles.txt

what's the difference? (***important***)
- `cat file`
    - passes the name *file* as an argument to the program
    - **cat opens** the file & displays its contents
- `cat < file`
    - cat is being run without arguments
    - the **shell opens** the file & passes the contents to cat in place of keyboard input

`wc file` vs `wc < file`  
pass argument =/= input redirection

## globbing pattern
`*.txt` is globbing pattern, `*` means match any sequence of chars. Shell finds all files in the current dir that match the pattern & substitues them onto the command line. `cat *.txt` is replaced with `cat aaa.txt bb.txt c.txt`. cat prints the contents of all these files, one after another

can do both input & output redirection `cat < inputfile > outputfile`
- takes chars from inputfile & sends to outputfile
- copies the file, same as `cp inputfile outputfile`

eg: `cat -n < inputfile > outputfile`, argument `-n` will number the lines

## stream
Every process is connected to 3 ***streams***
```
stdin ---------> program ---------> stderr
                         ---------> stdout
```

By default, stdin = keyboard, stdout & stderr = screen  
Input redirection `<` connects stdin to a file  
Output redirection `>` connects stdout to a file

stderr
- separate output stream for error msgs
- so we can send stderr & stdout to different places

Also
- stdout may be buffered
- system may wait to accumulate chars before actually displaying them (flushing the buffer)
- stderr is never buffered
    - so you see your error msgs immediately

redirect stderr, `program < input > output 2> errfile`

## pipes
- use the output of one program as the input of another
- set 2nd program's stdin to the 1st program's stdout

Eg: How many words occur in the first 20 lines of myfile.txt?  
`head -n file` - first n lines  
`wc` - counts lines, words, chars  
`wc -w` - only count words  

`head -20 myfile.txt | wc -w`, use `|` for piping


# Lecture 2
`uniq` removes **adjacent** duplicate entries. If entry is sorted then will remove **all** duplicates  
`sort` sorts lines

eg: `cat words*.txt | sort | uniq`

## program as args
Can we use output of one program as the **arg** of another? YES!  

eg: `echo "today is $(date) and I am $(whoami)"`, shell executes "data" and "whoami" and substitutes the result onto the cmd line
``` bash
echo "a          b"   =>   a          b  
echo a          b   =>   a b  
```
" " is important

careful: `echo 'Today is $(date)'` => Today is \$(date), no $-expension inside single quotes

`echo *` => print non-hidden files in current directory (like ls)  
Both kinds of quotes suppress glob expression *

## pattern matching in textfiles - regex
grep/egrep "(extended) global regular expression print"

`egrep pattern file` - print every line in file that contains pattern

ex: Print every line in myfile that contains cs246  
`egrep cs246 myfile`

ex: How many lines in myfile contain cs246 or CS246?  
`egrep "cs246|CS246" myfile | wc -l`  
OR with pattern "(cs|CS)246"

Available patterns - called regular expressions - NOT the same as globbing
- "(c|C)(s|S)246"
- "[cC][sS]246"
- both allows cS246 and Cs246 in addition to cs and CS

`[...]`: any ***one*** char in "..."  
`[^...]`: any ***one*** char except "..."

Add optional space: "[cC][sS] ?246" (there is a space before ?)

`?`: 0 or 1 of preceding expression  
`*`: 0 or more of preceding expression

"(cs)*246" -> 246, cs246, cscs246, ...

`+`: 1 or more of precesing  
`.`: any single char  
`.*`: anything/everything  
`.+`: anything but NOT nothing, could also use `..*`

`egrep "cs.*246" myfile` - lines containg cs...(anything)...246

`^, S`: beginning/end of line  
`"^cs246"` - lines that start with cs246  
`"^cs246$"` - lines exactly equal to cs246

Ex: lines with even length  
`"^(..)*$"`  
It can't know unless look at whole line -> use `"^...$"`

Ex: Files in the current dir whose name contain exactly one a  
`ls | egrep "^[^a]*a[^a]*$"`

All words in the dictonary that start with e and have 5 chars  
`egrep "^e[a-z][a-z][a-z][a-z]$"`

use `\.` to find char `.` instead of any char

## Permissions
`ls -l` - long form list

```
-rw-r----- 1 j2smith j2smith 25 sep 9 15:27 abc.txt

-(type)rw-(u)r--(g)---(o) 1(# of links) j2smith(owner) j2smith(group) 25(size) sep 9 15:27(last modified date) abc.txt(name)
```

type:  
`-`: ordinary file  
`d`: directory  

groups:  
a user can belong to one or more groups  
a file can be associated with one group

user bits - apply to the file's owner
group bits - apply to file's group (other than the owner)
other bits - apply to everyone else

`r w x`: read write execute

```
Bits      Meaning for ordinary file      Meaning for directory
-----------------------------------------------------------------
r         file can be read               directory can be read
                                         (ex: ls, globbing, tab completion)

w         file can be modified           directory content can be modified
                                         (can add/remove files)

x         file can be executed           directory can be navigated
          as a program                   (can cd into the dir)
```

Note: dir x-bit not set => no access at all, nor to any file/subdir within it

dir u = x (u only has x)
- can cd
- no ls

But can still cat knowing file name

dir u - x (u has no x), no cd/ls/"cat dir/file.txt"


# Lecture 3
chmod mode file

mode:
- usertypes: u, g, o, a (all)
- operator: `+` (add perm), `-` (remove perm), `=` (set perm)
- perms: r, w, x

Ex:  
give others read perm, `chmod o+r file`, o=r will remove other perms  
make everyone rx, `chmod a=rx file`
give owner full control, `chmod u=rwx file` or `chmod u+rwx file`

## Shell scripts
Files containing sequences of shell commands, executed as program  

Eg: print current date, user, directory  

myscript
``` bash
#!/bin/bash  - "shebang" line, execute this file as a bash script
date
whoami
pwd
```
```
chmod u+x myscript      give execute perm
./myscript              run file
```

### variables
`x=1` NO spaces  
`echo $x`

Note: use \$ to fetch the value of a var. No \$ when setting a var. Good practise `${x}`. All vars contain ***strings***. eg: x above is the string "1"

ex:
```
dir=~/246       ~ become abs path before stored 
echo $dir       -> /usr/home/...
ls $dir
```

Some "global" vars available  

IMPORTANT: `PATH` 
- list of dirs
- when you type a command, the shell searches these dirs, *in order*, for a prorgam with that name

\$ expansionhappen inside " " but NOT in ' '

command line args for scripts: $1, $2, ..., etc   

Eg: check whether a word is in the directory `./isItAWord hello`

``` bash
#!/bin/bash
egrep "^$1$" /usr/share/dict/words     # or  "^${1}$"
```

prints nothing if word not found, prints the word if found

### conditional - if
if ... elif ... elif ... else ... fi

Ex: A good password is not in the directory - answers whether a word is a good password

``` bash
#!/bin/bash
egrep "^$1$" /usr/share/dict/words > /dev/null     # suppresses output
if [ $? -eq 0 ]; then      # could also use    if egrep ...; then
    echo bad password
else
    echo maybe a good password
fi
```

Note: Every program returns a status code when finished  
egrep - returns 0 if found, 1 if not found (in Linux, 0 = success, non-zero = failure)  
`$?` - status of most recently executed command

Verify # of args, print err msg if wrong

``` bash
#!/bin/bash
usage(){
    echo "Usage: $0 password" 1>&2   # redirect stdout to stderr, $0 is name of program
}

if [ $# -ne 1 ]; then
    usage
    exit 1
fi

egrep ... (as before)
```

### loops - for/while
``` bash
#!/bin/bash
x=1
while [ $x -le $1 ]; do
    echo $x
    x = $((x+1))      # $((...))    for arithmetic
                      # x = ${x} + 1 => x is now "1+1", remember that everything is string
done
```

Looping over a list

``` bash
for x in a b c; do
    echo $x
done
```

Ex: Rename all .cpp files to .cc

``` bash
#!/bin/bash
for x in *.cpp; do      # glob, replace with all matching files in current directory
    mv ${x} ${x%cpp}cc     # value of x without trailing cpp
done
```

How many times does word $1 occur in file $2?
``` bash
#!/bin/bash
x=0
for word in $(cat $2); do
    if [ "$word" = "$1" ]; then     # wrap with " " in case $1 has "]" in it, might confuse bash
        x=$((x+1))
    fi
done
echo $x
```

Eg: Payday is last Friday of the month, when is this month payday? 2 tasks: compute date, report answer  
`cal | awk '{print $6}' | egrep "[0-9]" | tail -1`

``` bash
#!/bin/bash
report(){
    if [ $1 -eq 31 ]; then
        echo "this month: the 31st"
    else
        echo "this month: the ${1}th"
    fi
}

report $(cal | awk '{print $6}' | egrep "[0-9]" | tail -1)       # compute date, pass as arg $1
```

Generalize to any month  
`cal October 2022` - gives calendar for Oct, 2022

let `./payday October 2022` give October 2022's payday

change to `report $(cal $1 $2 | awk '{print $6}' | egrep "[0-9]" | tail -1) $1`  
Note that $1 to ./payday is now $2 to report()


# Lecture 4
Recall:
``` bash
#!/bin/bash
report() {
    if [ $2 ]; then
        echo -n $2
    else
        echo -n "this month"
    fi

    if [ $1 -eq 31 ]; then
        echo ": the 31st"
    else
        echo ": the ${1}th"
    fi
}

# Note that $1 to ./payday is now $2 to report()
report $(cal $1 $2 | awk '{print $6}' | egrep "[0-9]" | tail -1) $1
```

## SE Topic: Testing
essential part of program development

ongoing 
- begins before you start coding, test suites, expected behaviour
- continuous while you are going

Testing =/= Debugging
- can't debug without first testing
- cannot gurantee correctness
- can only prove wrongness

Human Testing 
- human look over code, find flaws
- code inspection, walkthrough

Machine Testing
- run program on selected inputs, compare with expected outputs
- can't test everything (choose carefully)

Black/White/Grey box testing - no/full/some knowledge of program implementation

Start with black box, supplement with white box

Black box
- various classes of input (eg: numerical ranges, pos vs neg)
- boundary of valid ranges (edge cases)
- multiple simultaneous boundaries (corner cases)
- intuition/experience
- extreme cases (within reason)

White box
- execute all logical paths through the program
- make sure every function runs

DO NOT TEST
- invalid input, unless a behaviour has been prescribed
- if the input is invalid, there is no corresponding correct output, any such test case is meaningless

Performance testing 
- is the program efficient enough?

Regression testing 
- make sure new changes to the program don't break test cases
- test suites, testing scripts
