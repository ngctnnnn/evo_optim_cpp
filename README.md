<div align='center'>

## Test function optimization using Evolution Computation

</div>

Currently built for:
- Differential Evolution

to optimize:

- Sphere function

```math
f(x) = \sum_{i = 1}^d x_i^2
```

s.t., $x \in \left[-32.678, 32.678\right]^d$

- Rastrigin function

```math
f(x) = A + \sum_{i = 1}^d[x_i^2 - A \cos(2 \pi x_i)]
```

s.t.,
- $A = 10$
- $x \in \left[-5.12, 5.12]\right]^d$

--- 
# Run this code
```bash
make test_fn=test_function_name
```
s.t., `test_function_name` is the name of test function you would like to test
