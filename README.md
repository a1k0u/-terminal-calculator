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
Input:
    
    exp(-j*PI*alpha*len/v0)
    alpha = sqrt(PI*len/(s1+s2))
    s1 = cos(real(S11)*real(S22))
    s2 = (sin(imag(S11*S22)))^2
    len = 191.76
    v0 = 299.799
    S11 = -0.01-0.92j
    S22 = 0.0001+0.997j
        
result = ...
```

### Documentation
> Empty

### Progress

- [x] Write C library to work with dynamic string
- [x] Struct of Nodes
- [ ] Parsing expression
- [ ] Tokenization objects
- [ ] Stack of functions
- [ ] Hash table for variables
- [ ] Polish notations
- [ ] Processing tokens
- [ ] Raising of warnings
- [ ] Result
