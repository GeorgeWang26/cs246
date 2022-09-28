# Tutorial 1
## Redirection and stdout, stdout convertion
0: stdin  
1: stdout  
2: stderr  

* `echo "ERROR" 1>&2` stdout becomes stderr
* to redirect stdout and stderr both to same file, `./program &> outfile`
  * convert stderr to stdout before piping `./program > out 2>&1`
  * stdout to stderr before pipe `./program > out 1>&2`
* shell read from right to left, so convertion is on the right side of pipe

### Find 10 most popular words in file
* `sort wordCollection | uniq -c | sort -n | tail > top10` tail default to tail -10
* could also use `sort wordCollection | uniq -c | sort -r | head > top10`


## Quotes
### Double quotes
* preserve whitespace
* supress globbing
* allow variable substitution and embedded commands
  * echo *
  * echo "*"
  * echo "$(cat word.txt)"
  * echo "$HOME"

### Single quotes
* preserve whitespace
* supress globbing and variable substitution and embedded commands

### No quotes
* supress whitespace
* allow globbing and variable substitution and embedded commands

## egrep and regex
always use double quotes, single quotes supress everything and make the pattern a pure string
* ^ : beginning of line
* $ : end of line
* . : any single non-newline character
* ? : 0 or 1 occurrences of previous character
* \* : 0 or more occurrences of previous character 
* \+ : 1 or more occurrences of previous character (same as ..*)
* [] : match any one in the set
* [^] : match any one not in the set
* () : grouping
* \- : ranges (e.g. [a-z])
* | : inclusive or
* \ : take next character as string (\\. is treated as just character . and not wildcard)


## Bash variable
* `var=42`
* `echo $var` NOT just `$var` unless `$var` is a command (or `${var})
* exit code of the latest program is stored to `$?` variable
* everything stored as string, even for `var=42`. Note: no space for assign
* `${var%<suffix>}` remove suffix from variable, MUST use {}
``` bash
x=thisismyname
echo ${x%name}  # this prints thisismy
```



# Tutorial 2

## Special Bash variable
* `$0` : name of current script
* `$1, $2` : argument (parameter) 1, 2, etc of current script
* `$#` : number of arguments of current script (not including `$0`, the script itself)
* `$@` : list of arguments supplied to current script (not including `$0`)
* `$?` : return exit code of most recent command/function/program


## Subroutines/functions in Bash
* mini bash scripts within a bash script, a series of command that can be called
* can be passed arguments similar to how a program is apssed command line arguments
* cannot directly access command line arguments to the script, need to pass the arguments into the functions from global
* can access global variables

## Condition in bash
* `num1 -eq num2` : num1 == num2
* `num1 -ne num2` : num1 != num2
* `num1 -gt num2` : num1 > num2
* `num1 -ge num2` : num1 >= num2
* `num1 -lt num2` : num1 < num2
* `num1 -le num2` : num1 <= num2
* `string1 = string2` : string1 == string2
* `-e file` : file exists
*  use `!` `||` and `&&` within `{ [ ... ]; };` to group commands together.  such as `if { [ $a -lt 0 ] || [ $a -eq 10 ]; }; then` 

## Arithmetic operations
Use `((...))` for arithmatics
```
a=10
((a++))   # a = 11
y=$((a+=10))   # a,y = 21
((a -= 5))   # a = 16
```

## Bash debugging
use `bash -x <script>`

## Add to PATH
* store executable at ~/bin
* add ~/bin to PATH by adding `PATH="$HOME/bin:$PATH"` to ~/.bashrc

``` bash
#!/bin/bash

sum() {
  echo $(( ${1} + ${2} ))
}

product() {
  echo $(( $1 * $2 ))
}

# not how arguments/variables can be access in two different ways
sum $( product $1 ${1} ) $( product ${2} $2 )
```

``` bash
for var in words; do
  ...
done
```

``` bash
while [ cond ]; do
  ...
done
```

``` bash
# '[ cond ]' can be replaced with other commands and the exit code will be checked
if [ cond ]; then
  ...
elif [ cond2 ]; then
  ...
......  # more elif
else
  ...
fi
```

## Test Scope
* Basic cases – sanity checks, assignment examples
* Size – tiny inputs, large inputs
* Edge cases – program should stop working exactly when it needs to
* Corner cases – two variables edge tested at once
* Weird cases – testing for undefined behaviour, error checking (but only if specified!)
* Don’t test for things you don’t need to
