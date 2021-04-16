# YouVerify Language Overview

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
arr = $mem(10) // 10 elements of memory allocated
arr[4] = 100
result = arr[4] // result will equal 100
```

This reflects the two possible operations available in the SMT-LIB arrays with extensionality. An array can be selected from, retrieving a single element. It can also be stored to creating a new array, inserting an eleemnt at a given index.

### Core ([SMT-LIB "Core"](http://smtlib.cs.uiowa.edu/theories-Core.shtml))

The Core theory defines the sort of boolean values and operators.

There are two boolean values:

```
t: BOOL
f: BOOL
t = true // the true value
f = false // the false value
```

Here are the operators available:

#### Unary Operators

##### `!` : not

```
t: BOOL
f: BOOL
t = true
f = !t // f will equal false
```

#### Binary Operators

##### `=>` : implies

```
t: BOOL
f: BOOL
r1, r2, r3, r4: BOOL
t = true
f = false
r1 = t => t // true
r2 = t => f // false
r3 = f => t // true
r4 = f => f // true
```

##### `&&` : and

```
t: BOOL
f: BOOL
r1, r2, r3, r4: BOOL
t = true
f = false
r1 = t && t // true
r2 = t && f // false
r3 = f && t // false
r4 = f && f // false
```

##### `||` : or

```
t: BOOL
f: BOOL
r1, r2, r3, r4: BOOL
t = true
f = false
r1 = t || t // true
r2 = t || f // true
r3 = f || t // true
r4 = f || f // false
```

##### `^` : xor

```
t: BOOL
f: BOOL
r1, r2, r3, r4: BOOL
t = true
f = false
r1 = t ^ t // false
r2 = t ^ f // true
r3 = f ^ t // true
r4 = f ^ f // false
```

##### `==` : equivalence

```
t: BOOL
f: BOOL
r1, r2, r3, r4: BOOL
t = true
f = false
r1 = t == t // true
r2 = t == f // false
r3 = f == t // false
r4 = f == f // true
```

##### `!=` : distinct

```
t: BOOL
f: BOOL
r1, r2, r3, r4: BOOL
t = true
f = false
r1 = t != t // false
r2 = t != f // true
r3 = f != t // true
r4 = f != f // false
```

#### Ternary Operators

##### `... ? ... : ...` : ite

```
i1, i2: BOOL
t, e, r: INT
i1 = true
i2 = false
t = 1
e = 2

r = i1 ? t : e // r will equal 1
r = i2 ? t : e // r will equal 2
```

### Integers ([SMT-LIB "Integers"](http://smtlib.cs.uiowa.edu/theories-Ints.shtml))

The theory of integers provides the integer sort, and the following operators:

#### Unary Operators

##### `-` : Unary Minus

```
i, r: INT
i = 10
r = -i // r will equal negative 10
i = -20 // i will equal negative 20
r = -i // r will equal 20
```

##### `abs`: Absolute Value

```
i, r: INT
i = -10
r = abs i // r will equal 10
r = abs 10 // will equal 10
```

#### Binary Operators

##### `-` : Subtract

```
x, y: INT
r: INT
x = 10
y = 5
r = x - y // r will equal 5
r = y - x // r will equal -5
```

##### `+` : Add

```
x, y: INT
r: INT
x = 10
y = 5
r = x + y // r will equal 15
r = 100 + 10 // r will equal 110
```

##### `*` : Multiply

```
x, y: INT
r: INT
x = 10
y = 5
r = x * y // r will equal 50
r = 100 * 10 // r will equal 1000
```

##### `//` : Divide

```
x, y: INT
r: INT
x = 10
y = 5
r = x // y // r will equal 2
r = 100 // 10 // r will equal 10
```

##### `%` : Modulo (Remainder)

```
x, y: INT
r: INT
x = 10
y = 6
r = x % y // r will equal 4
r = 100 % 10 // r will equal 0
```

##### `<=` : Less than or equal

```
x, y: INT
r: BOOL
x = 10
y = 5
r = x <= y // r will equal false
r = y <= x // r will equal true
```

##### `<` : Less than

```
x, y: INT
r: BOOL
x = 10
y = 5
r = x < y // r will equal false
r = y < x // r will equal true
```

##### `>=` : Greater than or equal

```
x, y: INT
r: BOOL
x = 10
y = 5
r = x >= y // r will equal true
r = y >= x // r will equal false
```

##### `<` : Less than

```
x, y: INT
r: BOOL
x = 10
y = 5
r = x > y // r will equal true
r = y > x // r will equal false
```

