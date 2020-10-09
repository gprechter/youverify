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
summation(x): 
  _cond (Bool) := x (BitVec 32) == 0 (BitVec 32)
  IF _cond GOTO summation_base
  _1 := x (BitVec 32) - 1 (BitVec 32)
	RETURN x (BitVec 32) + summation(_1) (BitVec 32)
summation_base:
	RETURN 0 (BitVec 32)
	
summation(100 (BitVec 32))
```

