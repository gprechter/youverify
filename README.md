# YouVerify

YouVerify is a simple imperative programming language based on the SMT-LIB set of theories and operators as a foundation.

The structure of every YouVerify program is as follows: 

```
{
	STRUCT DEFINITIONS
}
{
	GLOBAL VARIABLE AND FUNCTION DEFINITIONS
}
{
	CODE
}
```

### STRUCT DEFINITIONS

A user can define structures that contain fields of fundamental types.

```
struct STRUCTURE {
   a, b: INT
   flag: BOOL
}
```

### GLOBAL VARIABLE DECLARATIONS AND FUNCTION DEFINITIONS

### Global Variables

Any number of variables can be declared in the global scope, here's what a variable declaration looks like:

```
a: INT
b: (BITVEC 32)
c: BOOL
d: REAL
e: [INT]
f: STRUCTURE
... CODE ...
```

###  Functions

There are functions that may be defined at the beginning of the program. A function can be declared with any number of parameters, a return type, declared local variables, and any number of instructions including at least one `return` instruction (only available in afunction body). 

```
... GLOBALS ...
def FUNCTION(a: INT, b: INT) -> INT {
  c: INT
  c = a + b
	return c + 10
}
... GLOBALS ...
... CODE ...
```

### CODE

The code portion of a `.yvr` program is made-up of a positive number of `INSTRUCTION`s. Each `INSTRUCTION` can be one of two types:

#### Assignment Instruction

An assignment instruction is made up of some expression that evaluates to an assignable space, and an expression that evaluates to a like value:

```
<assignee> = <expression>
```

The `<assignee>` can either be a *variable*, a *field*, a *dereferenced pointer*, or an *indexed array element*.

Here are some examples:

```
a: INT
a = 10  // lhs is a variable
----------------------------------
struct STRUCTURE {
	a: INT
};
a: STRUCTURE
a.a = 10  // lhs is a field
----------------------------------
a: INT*
a = $mem(1)
*a = 10  // lhs is a dereferenced pointer
----------------------------------
a: [INT]
a = $mem(1)
a[0] = 10  // lhs is an indexed array element
```

### Goto Instruction

A goto instruction is of the following form:

```
if <predicate> goto <LABEL>
```

This instruction evaluates the predicate, which must be a boolean value. If the value is true, the program counter will be set to the line number of the instruction that contains the corresponding LABEL ***in the runtime environment***. (It's possible to have identical label names in the global frame and a function frame).

Here's an example:

```
a, result: INT
a = 10
if a == 10 goto END
	a = a + 10
LABEL END: result = a // result will be 10
```

## Built-In Types and Operators

The built-in types and operators available in YouVerify are meant to directly reflect those available in SMT-LIB. SMT-LIB is organized into multiple *Theories*, each with a number of *Sorts* and operators. A *Sort* is equivalent to a type.

### Array ([SMT-LIB "ArraysEx"](http://smtlib.cs.uiowa.edu/theories-ArraysEx.shtml))

YouVerify has arrays that can reference a specified amount of memory on the heap. Here's an example of operations that can be done with an array:

```
arr, result: [INT]
arr = $mem(10) // 10 WORDS of memory allocated on the heap
arr[4] = 100
result = arr[4] // result will equal 100
```

