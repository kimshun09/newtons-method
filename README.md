# Newton's Method

ニュートン法でいろんな方程式を解いてみた

### 2分法

`asg01/main.cpp`では，2分法により以下の多項式の方程式を解く．

![\begin{align*}
 f(x) = w_0 + w_1 x + w_2 x^2 + \ldots w_{d-1} x^{d-1} + w_{d} x^d = 0
\end{align*}](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%7D%0A+f%28x%29+%3D+w_0+%2B+w_1+x+%2B+w_2+x%5E2+%2B+%5Cldots+w_%7Bd-1%7D+x%5E%7Bd-1%7D+%2B+w_%7Bd%7D+x%5Ed+%3D+0%0A%5Cend%7Balign%7D)

実行例は以下の通り．

```
w = -20   0  -2  -2 0.5 0.1   0   0   0   0
Binary search for polynomial function
-------------------------
Iteration = 0
a = 5, b = -1
f(a) = 305, f(b) = -19.6
|a - b| = 6
-------------------------
Iteration = 1
a = 5, b = 2
f(a) = 305, f(b) = -32.8
|a - b| = 3
-------------------------
(略)
-------------------------
Iteration = 28
a = 3.5358, b = 3.5358
f(a) = 4.99165e-08, f(b) = -1.68016e-06
|a - b| = 2.23517e-08
-------------------------
Iteration = 29
a = 3.5358, b = 3.5358
f(a) = 4.99165e-08, f(b) = -8.15123e-07
|a - b| = 1.11759e-08
Binary search successfully terminated
Approximated solution of f(x) = 0 is 3.5358
====================================================
w = -30   0  -7  -5 0.3 0.2   0   0   0   0
Binary search for polynomial function
-------------------------
Iteration = 0
a = 10, b = -10
f(a) = 17270, f(b) = -12730
|a - b| = 20
-------------------------
Iteration = 1
a = 10, b = 0
f(a) = 17270, f(b) = -30
|a - b| = 10
-------------------------
(略)
-------------------------
Iteration = 29
a = 5.05131, b = 5.05131
f(a) = 3.51496e-06, f(b) = -9.60789e-06
|a - b| = 3.72529e-08
-------------------------
Iteration = 30
a = 5.05131, b = 5.05131
f(a) = 3.51496e-06, f(b) = -3.04646e-06
|a - b| = 1.86265e-08
Binary search successfully terminated
Approximated solution of f(x) = 0 is 5.05131
```

### 1次元のニュートン法

`asg02/main.cpp`では，先程の方程式をニュートン法で解く．

以下は実行例．

```
w = -20   0  -2  -2 0.5 0.1   0   0   0   0
-------------------------
Iteration = 0
x = -3
f(x) = 32.2
-------------------------
Iteration = 1
x = -2.41982
f(x) = 5.47431
-------------------------
Iteration = 2
x = -2.27045
f(x) = 0.351494
-------------------------
Iteration = 3
x = -2.25945
f(x) = 0.00185778
-------------------------
Iteration = 4
x = -2.25939
f(x) = 5.29053e-08
-------------------------
Iteration = 5
x = -2.25939
f(x) = 8.88178e-16
Newton successfully terminated
Approximated solution of f(x) = 0 is -2.25939
==============================================
w = -30   0  -7  -5 0.3 0.2   0   0   0   0
-------------------------
Iteration = 0
x = 5
f(x) = -17.5
-------------------------
Iteration = 1
x = 5.05303
f(x) = 0.606649
-------------------------
Iteration = 2
x = 5.05131
f(x) = 0.000652953
-------------------------
Iteration = 3
x = 5.05131
f(x) = 7.59087e-10
Newton successfully terminated
Approximated solution of f(x) = 0 is 5.05131
```

ニュートン法のほうが遥かに少ないループ数で解が求まった．

これは，2分方は線形収束，ニュートン法は2次収束であるからだといえる．

### 多次元のニュートン法

`asg03/main.cpp`では，以下の2つの非線形連立方程式を多変量のニュートン法により解く．

1. ![
   \begin{align*}
   f_1(\boldsymbol{x}) = \exp \left(- \exp \left( - x_1 - x_2 \right) \right) - x_2 \left( 1 + x_1^2 \right) &= 0 \\
   f_2(\boldsymbol{x}) = x_1 \cos x_2 + x_2 \sin x_1 - \frac{1}{2} &= 0
   \end{align*}](https://render.githubusercontent.com/render/math?math=%5Clarge+%5Cdisplaystyle+%0A%5Cbegin%7Balign%2A%7D%0Af_1%28%5Cboldsymbol%7Bx%7D%29+%3D+%5Cexp+%5Cleft%28-+%5Cexp+%5Cleft%28+-+x_1+-+x_2+%5Cright%29+%5Cright%29+-+x_2+%5Cleft%28+1+%2B+x_1%5E2+%5Cright%29+%26%3D+0+%5C%5C%0Af_2%28%5Cboldsymbol%7Bx%7D%29+%3D+x_1+%5Ccos+x_2+%2B+x_2+%5Csin+x_1+-+%5Cfrac%7B1%7D%7B2%7D+%26%3D+0%0A%5Cend%7Balign%2A%7D)
2. ![
   \begin{align*}
   f_1(\boldsymbol{x}) = x_1^2 + x_2^2 + x_1 x_3 - x_1 - x_2 - 1 &= 0 \\
   	     f_2(\boldsymbol{x}) = x_1^3 + x_3^3 + 3 x_1^2 - x_3^2 + 2 x_2 x_3 - 2 x_3 - 4 &= 0 \\
   	     f_3(\boldsymbol{x}) = 3 x_1 x_2 + 2 x_1 x_3 + 4 x_2 x_3 - 3 x_2 - 4 x_3 - 2 x_1 &= 0
   \end{align*}](https://render.githubusercontent.com/render/math?math=%5Clarge+%5Cdisplaystyle+%0A%5Cbegin%7Balign%2A%7D%0Af_1%28%5Cboldsymbol%7Bx%7D%29+%3D+x_1%5E2+%2B+x_2%5E2+%2B+x_1+x_3+-+x_1+-+x_2+-+1+%26%3D+0+%5C%5C%0A%09+++++f_2%28%5Cboldsymbol%7Bx%7D%29+%3D+x_1%5E3+%2B+x_3%5E3+%2B+3+x_1%5E2+-+x_3%5E2+%2B+2+x_2+x_3+-+2+x_3+-+4+%26%3D+0+%5C%5C%0A%09+++++f_3%28%5Cboldsymbol%7Bx%7D%29+%3D+3+x_1+x_2+%2B+2+x_1+x_3+%2B+4+x_2+x_3+-+3+x_2+-+4+x_3+-+2+x_1+%26%3D+0%0A%5Cend%7Balign%2A%7D)

多変量であるため，解の更新はヤコビ行列の逆行列を用いる．

以下は実行例．

```
-------------------Problem 1-------------------
x1 = 0.8 0.9
-------------------------
Newton iteration setting
Problem dimension: 2, Stopping tolerance: 1e-08
Newton successfully terminated
=========================
Solution for the problem 1: 
0.353247 0.606082
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x1 = -0.7 -0.4
-------------------------
Newton iteration setting
Problem dimension: 2, Stopping tolerance: 1e-08
Newton successfully terminated
=========================
Solution for the problem 1: 
0.353247 0.606082
-------------------Problem 2-------------------
x2 = 1.2 1.2 1.2
-------------------------
Newton iteration setting
Problem dimension: 3, Stopping tolerance: 1e-08
Newton successfully terminated
=========================
Solution for the problem 2: 
1 1 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x2 = 5.3 1.7 2.6
-------------------------
Newton iteration setting
Problem dimension: 3, Stopping tolerance: 1e-08
Newton successfully terminated
=========================
Solution for the problem 2: 
0.972127  1.30288 0.650619
```

