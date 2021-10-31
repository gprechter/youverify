# YouVerify

YouVerify is a simple imperative programming language based on the SMT-LIB set of theories and operators as a foundation. The YouVerify symbolic execution framework provides a symbolic execution engine on the YouVerify language, with the intention that all operators and code written with the YouVerify language can be symbolically executed using the companion symbolic execution engine. The symbolic execution engine exposes a comprehensive API allowing developers to prototype application specific symbolic execution algorithms.

## Language Features

Each `YouVerify` program (file extension `.yvr`) is composed as follows, divided into two sections:

```
<GLOBAL DECLARATIONS>
...
<STATEMENTS>
...
```

At the top of the program file, there are the global definitions consisting of **global variable declarations** along with **function declarations**, and **record type declarations**. Functions can only be declared globally. Below all of the declarations are the statements, or the body of the program. 

### Variable Declarations

```
x: INT						# Integer type declaration
b: BOOL						# Boolean type declaration
bv: BV[32]				# A bit vector of length 32 bits
arr: ARRAY{INT}		# Array type declaration of array with integer elements
rec: point  		  # record type declaration
```

A variable declaration is written using the following syntax:

```
<variable name> : <built-in sort | custom record type>
```

### Built-in Sorts and Custom Record Types

Values can be typed as either built-in sorts (those that are supported by the underlying SMT-LIB 2 sorts), or using custom record types, which provide a type that contains multiple built-in sort typed values.

#### Built-in Sorts

The current supported built-in sorts are: `INT`, `BOOL`, `BV`, `ARRAY`. Array types are associated with another type known as the *element type*; this type can be any other *built-in sort*, including `ARRAY`.

#### Custom Record Types

A record type is created as follows:

```
record point(x: INT, y: INT)
```

### Functions:

Functions are defined as follows:

```
define <function-name> ( <variable declarations as parameters> ) [-> <return type>]:
		<LOCAL DECLARATIONS [VARIABLES ONLY]>
		...
		<STATEMENTS>
		...
```

Functions can take in any amount of parameters, represented using variable declaration notation in the parentheses. Functions can optionally have a return type. If a function has a return type, all paths through the funciton ***must*** terminate in a return statement returning the corresponding type. If the function has no return type, it must terminate without returning a value.

Within the body of the function, like at the global level, all local declarations must come first. Following the local declarations, the statements that make up the body of the function is written.

##### Example:

```
define fact(n: INT) -> INT:
		rec_call: INT
		next_n: INT
		if n > 0 goto END
		return 1
		LABEL END: next_n = n - 1
		call rec_call = fact(next_n)
		return rec_call * n
```

### Statements

Below the delcarations and definitions above, there are the statements that make up the body of the program or function.

#### Labeled Statements

Every statement can optionally be labeled: `LABEL <LABEL_NAME>: <STATEMENT>`. Every labeled statement is made available as a branch destination to be used by conditional and unconditional branching statements. Within a given scope (i.e. global, function local), there **must** not be duplicate label names. That is, each statement that is labeled within a scope must have a unique name.

#### Assignment Statements

The most basic statement is the assignment statement which is written as follows:

```
<ASSIGNMENT TARGET> = <EXPRESSION>
```

The right hand side of an assign statement can be any valid expression, so long as it evaluates to the same type as the assignment target.

The ***assignment target*** can be one of the following three:

1) An identifier which corresponds to a variable. `x = 10`

2) An array index expression, which corresponds to storing into a certain index in an array: `arr[10] = 10`

3) A record index expression, which corresponds to assigning to an element in a record: `rec.x = 10`

#### Branching Statements

There are two flavors of branching statements **conditional** and **unconditional**.

##### Conditional Branching Statements

A conditional branch statement depends on a condition and will either increment the program counter by one to the next statement if the condition is false and will set the program counter to the line number of the labeled expression if the condition is true. The conditional expression can be any valid expression that evaluates to the `BOOL` sort.

```
if <CONDITIONAL EXPRESSION> goto <LABEL NAME>
```

##### Unconditional Branching Statement

The unconditional branching statement is a short hand way of writting `if true goto <LABEL NAME>`:

```
goto <LABEL NAME>
```

#### Function Call Statements

A function call is expressed not as an expression but rather as it's own individual statement. There are two flavors of the funciton call statement, the first is if the function call return value is supposed to be assigned to a variable in the caller frame, and the second is if the function call return value is **not** supposed to assign to a variable in the caller frame.

##### Function Call then Assign Statement

```
call <ASSIGNMENT TARGET> = <FUNCTION NAME> ( <ARGUMENTS> )
```

**note:** *only* functions that have a return value of the appropriate type can be used in a call then assign statement.

##### Function Call with No Assign Statement

```
call <FUNCTION NAME> ( <ARGUMENTS> )
```

Any function can be called using this notation.

#### Return Statements [*Funcitons Only*]

Depending on the desired behavior, a return statement can either have a value to return or not. 

```
return
```

```
return x
```

A return statement without a return value can be used to return from a function without a declared return type. If a function has a return type, the return statement with a value of the corresponding type must be used.

#### Assert Statements

An assert statement is utilized by appending a given condition to the path constraint, acting as a conditional branching statement branching to the end of the program. The statement following the `assert` keyword must evaluate to the `BOOL` sort.

```
assert <CONDITIONAL EXPRESSION>
```

### Expressions

Expressions are utilized in the many types of statements:

#### Atomic Expressions

There are a few atomic expressions that consist of the following categories:

##### Concrete Values:

```
10 							# Value of type INT sort
true						# Value of type BOOL sort
false 					# Value of type BOOL sort
BV{4, 32}				# Value of type BV sort, with value and length 
ARRAY[]{INT} 		# An ARRAY sort of integers with indefinite length
ARRAY[10]{INT}	# An ARRAY sort of integers with a fixed length of 10
```

##### Variable Identifier

```
x
b
point
factorial_value
```

##### Symbolic Values:

````
$sym{BOOL}		# A symbolic value of sort BOOL with a random unique name
$sym{b, BOOL}	# A symbolic value of sort BOOL with the name 'b'
````

**note:** symbolic values, every time an atomic expression with no name is evaluated a NEW symbol with a unique name is created.

#### Array Index Expressions

```
arr[<INDEX>]	# Where INDEX must be an integer sort, and must be within bounds
```

#### Record Element Index Expression

```
<variable name> . <element name>
```

#### Unary Expressions

```
<UNARY OPERATOR> <ATOMIC EXPRESSION>
```

#### Binary Expressions

```
<ATOMIC EXPRESSION> <BINARY OPERATOR> <ATOMIC EXPRESSION>
```

#### Ternary Expressions

Only `ite`.

```
<ATOMIC EXPRESSION> ? <ATOMIC EXPRESSION> : <ATOMIC EXPRESSION>
```



## Testing and Validation

 

| Feature                                                      | Notes                                        | Status        |
| ------------------------------------------------------------ | -------------------------------------------- | ------------- |
| [Boolean Sort and Operators](https://github.com/gprechter/youverify/tree/master/python_src/tests/boolean) |                                              | ✅ Completed   |
| [Integer Sort and Operators](https://github.com/gprechter/youverify/tree/master/python_src/tests/integer) | `div`, `mod`, `abs` not supported by `pysmt` | ✅ Completed   |
| [Bit Vector Sort and Operators](https://github.com/gprechter/youverify/tree/master/python_src/tests/bitvectors) |                                              | ❌ In Progress |
| [Array Sort and Operators](https://github.com/gprechter/youverify/tree/master/python_src/tests/arrays) [Including Fixed Sized] |                                              | ❌ In Progress |
| Labels and Branching Statements                              |                                              | ❌ In Progress |
| [Functions](https://github.com/gprechter/youverify/tree/master/python_src/tests/functions) |                                              | ❌ In Progress |
| [Assert Statements](https://github.com/gprechter/youverify/tree/master/python_src/tests/assert) |                                              | ❌ In Progress |
| Symbolic Values and Programs                                 |                                              | ❌ In Progress |
| [Records](https://github.com/gprechter/youverify/tree/master/python_src/tests/records) |                                              | ❌ In Progress |

