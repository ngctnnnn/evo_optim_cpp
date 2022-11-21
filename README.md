<div align='center'>

## Test function optimization using Evolution Computation

</div>

### List of algorithms support
1. [Differential Evolution](https://link.springer.com/article/10.1023/A:1008202821328)

### List of test function

#### 1. Sphere function

```math
f(x) = \sum_{i = 1}^d x_i^2
```

s.t., $x \in \left[-32.678, 32.678\right]^d$

- Global minimum: $f(x^{\ast}) = 0$, at $x^{\ast} = (0,...,0)$

#### 2. Rastrigin function

```math
f(x) = A + \sum_{i = 1}^d[x_i^2 - A \cos(2 \pi x_i)]
```

s.t.,
- $A = 10$
- $x \in \left[-5.12, 5.12]\right]^d$      

- Global minimum: $f(x^{\ast}) = 0$, at $x^{\ast} = (0,...,0)$

#### 3. Rosenbrock function 

```math
f(x) = \sum_{i = 1}^{d - 1}\left[100(x_{i+1}-x_i^2) + (x_i - 1)^2\right]
```
s.t., $x_i \in [-5;10]$

- Global minimum: $f(x^\ast) = 0$ at $x^{\ast}=(1,...,1)$

### Run this code
```bash
make test_fn=test_function_name
```
s.t., `test_function_name` is the name of test function you would like to test
