## Notes:

[Meeting Notes & Framework Design](https://docs.google.com/document/d/1qk7L6aTKUw9ykk0yhzhVlgbptl31UTwvZ6AsXmCjtvE/edit)

[SMT-LIB](http://smtlib.cs.uiowa.edu/index.shtml)

```
def summation(x (BitVec 32)):
	if x  == BitVec(32, 0):
		return BitVec(32, 0)
	return x + summation(x - BitVec(32, 1))
summaiton(BitVec(32, 100))
```

---->

```
summation(x (BitVec 32)) -> (BitVec 32): 
  _cond (Bool)
  _1 (BitVec 32)
  
  _cond := x == 0
  IF _cond GOTO summation_base
  _1 := x - 1
	RETURN x + summation(_1)
summation_base:
	RETURN 0
	
summation(100)
```

