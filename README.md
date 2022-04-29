# Terminal calculator

### About project

> Here's a terminal calculator with some "__human 
> use experience__". There is already realise few features of functionality.   
> - *operations*: +, -, ^, /
> - *constants*: PI, e, j
> - *functions*: cos, sin, ln, exp, sqrt, real, imag, mag and phase
>
> > *Guaranteed that argument of cos, sin, ln and exp will be a **real number**.*
>
> Your expression able to use **variables**.

### Example

```c
>> exp(-j*PI*alpha*len/v0)
alpha? >> sqrt(PI*len/(s1+s2))
len? >> 191.76
s1? >> cos(real(S11)*real(S22))
S11? >> -0.01-0.92j
S22? >> 0.0001+0.997j
s2? >> (sin(imag(S11*S22)))^2
v0? >> 299.799

<< ... = 0.584118 + 0.811669j
```

### How does it work?
> Several libraries have been written for this program, such as:
> _string.h, stack.h, node.h and hash_table.h_;
> 
> First of all, we put an input expression and tokenizing it, for example:
> 
> >_1.3232j + xxx - cos(-4)_ __turned into__ _1.3232j(CMP)
> +(OPN) xxx(VAR) -(OPN) cos(FUN) ((OPN) -4(DBL) )(OPN)_
>
> Where FUN = function, OPN = operation, DBL = double, COMP = complex
> and VAR = variable are flags;
>
> After that, the algorithm will construct the reverse Polish notation:
> >1.3232j xxx + -4 cos -
>
> All unknown variables that are not written to the hash table 
> will be requested from the user and then stored in the global table.
> 
> Finally, using our flags, the expression will be calculated
> and the answer is given.

### Documentation
> Empty

### Progress

- [x] Write C library to work with dynamic string
- [x] Struct of Nodes
- [x] Parsing expression
- [x] Tokenization objects
- [x] Stack of functions
- [x] Hash table for variables
- [x] Polish notations
- [x] Processing tokens
- [x] Raising of warnings
- [x] Result
