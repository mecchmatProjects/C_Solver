# 1. Ідея курсового проєкту
## `MiniAI` — власний C++ framework для математичного машинного навчання

Протягом курсу студенти спільно розробляють одну програмну систему:

> **MiniAI — lightweight mathematical and machine-learning framework written from scratch in C++.**

Це не готова бібліотека машинного навчання.

Навпаки, студенти поступово реалізують власні:

* математичні функції;
* вектори;
* матриці;
* операції над матрицями;
* статистичні функції;
* функції активації;
* похідні;
* чисельне диференціювання;
* loss-функції;
* оптимізаційні алгоритми;
* структури даних;
* нейронні шари;
* просту нейронну мережу;
* навчання мережі;
* збереження/завантаження моделей;
* CLI для роботи з моделями;
* аналіз результатів навчання.

Фінальна програма повинна дозволяти виконати приблизно такі команди:

```text
miniai function sigmoid 2.0

miniai derivative sigmoid 2.0

miniai vector dot [1,2,3] [4,5,6]

miniai matrix multiply A B

miniai loss mse predicted target

miniai optimize rosenbrock

miniai train model.json dataset.txt

miniai predict model.bin input.txt

miniai inspect model.bin
```

Тобто протягом семестру вони переходять від

```text
cout << ...
```

до

```text
MiniAI model;
model.add(Dense(2, 8));
model.add(ReLU());
model.add(Dense(8, 1));
model.train(X, y);
```

---

# 2. Чому саме такий проєкт

Методичка передбачає 21 лабораторну роботу і побудована поступово: від лінійних програм, математичних функцій і циклів до масивів, вказівників, структур, файлів, класів, наслідування, поліморфізму, шаблонів та STL.

Тому не варто на першій лабораторній говорити студентам:

> «Напишіть нейронну мережу».

Натомість вони весь курс будують її **пошарово**.

### Логіка розвитку

```text
Lab 1
числа
  ↓
Lab 2
математичні функції
  ↓
Lab 3
вектори
  ↓
Lab 4
чисельні алгоритми
  ↓
Lab 5
рекурсія / оптимізація
  ↓
Lab 6
бітові операції / представлення даних
  ↓
Lab 7–8
масиви / матриці
  ↓
Lab 9
dynamic memory / pointers
  ↓
Lab 10
математичні структури
  ↓
Lab 11–14
datasets / serialization / text processing
  ↓
Lab 15
Vector / Matrix / Function classes
  ↓
Lab 16
Activation / Layer hierarchy
  ↓
Lab 17
exceptions / validation
  ↓
Lab 18
templates
  ↓
Lab 19–21
STL / algorithms / ML pipeline
  ↓
FINAL
MiniAI Neural Network Framework
```

---

# 3. Головна архітектура

Фінальна архітектура:

```text
                     MiniAI
                       │
       ┌───────────────┼────────────────┐
       │               │                │
   Mathematics      Machine Learning    IO
       │               │                │
       │          ┌────┼─────┐          │
       │          │    │     │          │
    Vector      Layer Loss Optimizer   Dataset
    Matrix       │             │          │
    Function     │             │          │
       │         └──────┬──────┘          │
       │                │                 │
       └────────────── Neural Network ────┘
                         │
                       Model
                         │
                  Train / Predict
```

Або більш технічно:

```text
                 ┌───────────────┐
                 │     CLI       │
                 └───────┬───────┘
                         │
                 ┌───────▼───────┐
                 │   Controller   │
                 └───────┬───────┘
                         │
          ┌──────────────┼──────────────┐
          │              │              │
     ┌────▼────┐    ┌────▼────┐   ┌────▼────┐
     │ Dataset │    │  Model   │   │ Analysis│
     └────┬────┘    └────┬─────┘   └────┬────┘
          │              │              │
          │        ┌─────▼─────┐        │
          │        │   Layers  │        │
          │        └─────┬─────┘        │
          │              │              │
          └──────────────┼──────────────┘
                         │
                  ┌──────▼──────┐
                  │   Tensor    │
                  │ Vector/Matrix│
                  └──────┬──────┘
                         │
                 ┌───────▼───────┐
                 │ Mathematics   │
                 └───────────────┘
```

---

# 4. Що буде фінальним продуктом

Студенти отримують framework, здатний навчити просту нейронну мережу.

Наприклад:

```cpp
MiniAI::Sequential model;

model.add(Dense(2, 8));
model.add(ReLU());

model.add(Dense(8, 8));
model.add(Sigmoid());

model.add(Dense(8, 1));

model.compile(MSE(), SGD(0.01));

model.fit(X, y, 1000);

model.save("model.bin");

auto prediction = model.predict(x);
```

Фінальна демонстрація:

```text
Dataset:
x1 x2 → y

0 0 → 0
0 1 → 1
1 0 → 1
1 1 → 0

Training...

Epoch 1      loss = 0.6932
Epoch 100    loss = 0.4217
Epoch 500    loss = 0.0821
Epoch 1000   loss = 0.0124

Prediction:
0 0 → 0.01
0 1 → 0.98
1 0 → 0.97
1 1 → 0.03
```

Тобто студенти власноруч доходять до реалізації XOR або іншої маленької задачі класифікації.

---

# 5. Команди студентів

## Team A — Numerical Core

5 студентів

Відповідають за:

```text
Scalar
Vector
Matrix
Tensor
Math functions
Statistics
Numerical methods
```

---

## Team B — Machine Learning

5 студентів

Відповідають за:

```text
Activation functions
Loss functions
Layers
Forward propagation
Backward propagation
Optimizer
Training
```

---

## Team C — Data & Algorithms

5 студентів

Відповідають за:

```text
Dataset
Parsing
File formats
Statistics
Sorting
Searching
Batch processing
Serialization
```

---

## Team D — Framework / Infrastructure

5 студентів

Відповідають за:

```text
CLI
Model
Layer interface
Exceptions
Configuration
Logging
Testing
Integration
Documentation
```


Є один repository:

```text
MiniAI/
```

і всі працюють над одним продуктом.

---

# 6. Приклад структури repository

На початку:

```text
MiniAI/
│
├── README.md
├── CMakeLists.txt
│
└── src/
    └── main.cpp
```

Пізніше:

```text
MiniAI/
│
├── README.md
├── CMakeLists.txt
│
├── include/
│   └── miniai/
│       ├── math/
│       ├── ml/
│       ├── data/
│       └── core/
│
├── src/
│   ├── math/
│   ├── ml/
│   ├── data/
│   └── core/
│
├── tests/
│
├── examples/
│
├── datasets/
│
└── models/
```

---

# 7. Відповідність лабораторним роботам

## LAB 1 — Scalar Engine

### Теми методички

* введення/виведення;
* дійсні типи;
* форматований вивід;
* математичні вирази.

Це відповідає першому розділу методички.

### MiniAI

Студенти створюють:

```text
Scalar
```

та базовий mathematical engine.

Завдання:

* addition;
* subtraction;
* multiplication;
* division;
* power;
* sqrt;
* exp;
* log;
* sin;
* cos.

Особливо добре сюди лягають задачі методички на науковий формат, математичні функції, середні та фізичні формули.

### Milestone

```text
MiniAI v0.1

scalar operations
+
CLI
```

---

# 8. LAB 2 — Mathematical Functions

Тут вже з'являється дуже сильний зв'язок із AI.

Методичка прямо містить:

* Rosenbrock;
* `sigmoid`;
* `softPlus`;
* `gauss`;
* `arctg`;
* `softSign`;
* `sigmweight`;
* похідні цих функцій.

Тому кожен студент реалізує одну математичну функцію:

```cpp
double sigmoid(double x);
double sigmoidDerivative(double x);
```

або:

```cpp
double relu(double x);
double reluDerivative(double x);
```

або:

```cpp
double gaussian(double x);
double gaussianDerivative(double x);
```

### Важлива ідея

Не просто:

```cpp
double sigmoid(double x)
```

а концепція:

```text
Function
 ├── value(x)
 └── derivative(x)
```

Поки що це можна реалізувати функціями.

Пізніше це стане класом.

---

# 9. LAB 3 — Vector Engine

Тут починається справжня AI-математика.

Методичка вже містить задачі на введення n-вимірного вектора, суму двох векторів та скалярний добуток.

Студенти створюють:

```text
Vector
```

Операції:

```text
+
-
*
dot()
norm()
distance()
sum()
mean()
min()
max()
```

Наприклад:

```cpp
Vector x{1, 2, 3};
Vector y{4, 5, 6};

Vector z = x + y;

double s = dot(x, y);
```

Milestone:

```text
MiniAI v0.3

Scalar
Function
Vector
```

---

# 10. LAB 4 — Numerical Approximation

Тут можна використати задачі методички з наближеного обчислення:

* π;
* sin;
* cos;
* sinh;
* cosh;
* exp;
* log;
* `1/(1+x)`.

Але в контексті AI завдання стає:

> Реалізувати власний numerical approximation engine.

Наприклад:

```cpp
double numericalDerivative(
    Function f,
    double x,
    double h
);
```

і порівняти:

```text
analytical derivative
vs
numerical derivative
```

Це вже дуже корисно для подальшого backpropagation.

---

# 11. LAB 5 — Optimization Engine

Ось тут проєкт починає ставати реально цікавим.

Методичка містить функцію Rosenbrock:

```text
R(x,y) = 100(x²-y)² + (x-1)²
```

Замість просто обчислити її студенти створюють:

```text
Optimizer
```

і реалізують:

```text
Gradient Descent
```

Наприклад:

```cpp
x = x - learningRate * gradient;
```

Фінальний результат:

```text
Rosenbrock optimization

initial:
x = -1.5
y = 2.0

iteration 0:
f = ...

iteration 100:
f = ...

iteration 1000:
f = ...

minimum:
x ≈ 1
y ≈ 1
```

Це чудовий міст від математичного аналізу до ML.

---

# 12. LAB 6 — Binary Representation

Тут не потрібно штучно вигадувати AI.

Студенти реалізують:

```text
BinaryEncoder
BinaryDecoder
```

Використовують:

* bitwise AND;
* OR;
* XOR;
* shifts;
* masks.

Методичка має задачі саме на кількість одиничних бітів, перевірку степеня двійки, спільні біти та бітове представлення.

У MiniAI це пізніше використовується для:

```text
model metadata
flags
binary serialization
```

---

# 13. LAB 7 — Dynamic Vector

Переходимо від:

```cpp
double x[100];
```

до:

```cpp
double* data;
size_t size;
```

Студенти реалізують власний:

```text
DynamicVector
```

з:

```text
constructor
destructor
resize
push_back
operator[]
copy
```

Це буде дуже корисно перед створенням `Matrix`.

---

# 14. LAB 8 — Matrix Engine

Це один із центральних етапів курсу.

Методичка прямо містить завдання на шаблонний клас `Matrix`, побудований через `vector<vector<T>>`, із:

* `operator<<`;
* додаванням матриць;
* множенням матриці на вектор;
* множенням матриць.

У MiniAI:

```cpp
Matrix A;
Matrix B;

Matrix C = A * B;
Vector y = A * x;
```

Потрібні операції:

```text
+
-
*
transpose
norm
row
column
```

---

# 15. LAB 9 — Memory & Pointers

Тут студенти досліджують:

```text
stack
heap
pointer
reference
dynamic allocation
ownership
```

і переносять `Vector/Matrix` на коректне керування пам'яттю.

Це хороший момент, щоб пояснити:

```text
why std::vector exists
```

а не просто змусити їх його використовувати.

---

# 16. LAB 10 — Mathematical Data Structures

Структури з методички можна перетворити на:

```text
Point
Vector
MatrixShape
Interval
DatasetRow
```

Наприклад:

```cpp
struct Point {
    double x;
    double y;
};
```

А потім:

```text
Point
 ↓
Vector
 ↓
Matrix
 ↓
Tensor
```

---

# 17. LAB 11–14 — Dataset Engine

Тут проєкт переходить від математики до реального ML pipeline.

Студенти працюють із:

```text
dataset.txt
dataset.bin
model.bin
config.txt
```

Методичка містить окремі лабораторні з бінарними файлами, потоками C++, класом рядків та текстовими файлами.

Наприклад:

```text
dataset.txt

0.1 0.4 1
0.2 0.7 1
0.8 0.1 0
...
```

Студенти створюють:

```cpp
Dataset
```

із:

```text
load()
save()
shuffle()
split()
normalize()
statistics()
```

---

# 18. LAB 15 — Object-Oriented Mathematical Framework

Ось тут старий procedural code перетворюється на справжній framework.

Методичка переходить до власних класів та інкапсуляції саме на цьому етапі.

Створюємо:

```text
class Vector
class Matrix
class Function
class Dataset
class Optimizer
```

Наприклад:

```cpp
class Function {
public:
    virtual double value(double x) const = 0;
    virtual double derivative(double x) const = 0;
};
```

---

# 19. LAB 16 — Layers, Inheritance, Polymorphism

Це буде один із найкращих моментів курсу.

Методичка має окремий розділ про наслідування та поліморфізм.

Створюємо:

```text
Layer
│
├── Dense
├── Activation
├── ReLU
├── Sigmoid
├── Linear
└── Softmax
```

Наприклад:

```cpp
class Layer {
public:
    virtual Vector forward(const Vector&) = 0;
    virtual Vector backward(const Vector&) = 0;

    virtual ~Layer() = default;
};
```

Тепер:

```cpp
vector<unique_ptr<Layer>> layers;
```

і можна написати:

```cpp
for (auto& layer : layers)
    x = layer->forward(x);
```

Це вже **справжній polymorphic architecture**.

---

# 20. LAB 17 — Exceptions & Type Conversion

Студенти додають:

```text
InvalidShape
InvalidDimension
InvalidArgument
DivisionByZero
DatasetError
ModelError
```

Наприклад:

```cpp
Matrix A(3, 4);
Matrix B(5, 2);

A * B;
```

повинно генерувати:

```text
MatrixDimensionError
```

а не падати десь у `operator*`.

---

# 21. LAB 18 — Templates

Тут можна повернутися до задачі методички з generic `Matrix<T>`.

Наприклад:

```cpp
template<class T>
class Matrix {
    ...
};
```

Тоді:

```cpp
Matrix<int>
Matrix<float>
Matrix<double>
```

можуть використовувати один framework.

Ще цікавіше:

```cpp
template<class T>
T sum(const vector<T>&);
```

---

# 22. LAB 19 — STL Containers

Тепер студенти замінюють частину власних структур на STL.

Методичка окремо присвячує лабораторну послідовним контейнерам та контейнерам-адаптерам.

Використання:

```text
vector
deque
list
stack
queue
```

Наприклад:

```cpp
vector<unique_ptr<Layer>> layers;
```

---

# 23. LAB 20 — Associative Containers

Тут з'являється:

```text
map
unordered_map
set
```

У MiniAI це можна використати дуже природно.

Наприклад:

```cpp
unordered_map<string, double> metrics;
```

дає:

```text
loss
accuracy
precision
recall
```

А:

```cpp
map<string, string> metadata;
```

зберігає:

```text
model_name
version
optimizer
dataset
```

---

# 24. LAB 21 — Algorithms & Function Objects

Методичка завершується STL алгоритмами та функціональними об'єктами.

Тут можна зробити фінальний refactoring.

Наприклад:

```cpp
std::transform(...)
std::accumulate(...)
std::sort(...)
std::find_if(...)
std::max_element(...)
```

і lambda expressions.

Наприклад:

```cpp
std::transform(
    values.begin(),
    values.end(),
    result.begin(),
    [](double x) {
        return sigmoid(x);
    }
);
```

---

# 25. Фінальний ML stack

До кінця курсу студенти повинні отримати:

```text
                    MiniAI
                      │
              ┌───────▼───────┐
              │ NeuralNetwork │
              └───────┬───────┘
                      │
              ┌───────▼───────┐
              │     Layer     │
              └───────┬───────┘
                      │
        ┌─────────────┼─────────────┐
        │             │             │
      Dense         ReLU         Sigmoid
        │             │             │
        └─────────────┼─────────────┘
                      │
               ┌──────▼──────┐
               │   Matrix    │
               └──────┬──────┘
                      │
               ┌──────▼──────┐
               │   Vector    │
               └──────┬──────┘
                      │
               ┌──────▼──────┐
               │ Math Engine │
               └─────────────┘
```

---

# 26. Які математичні можливості повинні бути у фінальній системі

## Scalar functions

```text
sin
cos
tan
exp
log
sqrt
abs
```

## AI activation functions

```text
ReLU
LeakyReLU
ELU
Sigmoid
SoftPlus
SoftSign
Gaussian
```

Це безпосередньо пов'язує проєкт із відповідними задачами методички.

## Derivatives

```text
f'(x)
```

для кожної activation function.

## Vector operations

```text
dot
norm
distance
normalize
mean
variance
```

## Matrix operations

```text
+
-
*
transpose
matrix-vector product
matrix multiplication
```

## Optimization

```text
Gradient Descent
```

## Loss

```text
MSE
```

а за можливості:

```text
MAE
Binary Cross Entropy
```

## Neural network

```text
Dense
Activation
Sequential
```

---

# 27. Особливо цікава частина — одна і та сама математика проходить через увесь курс

Це, на мою думку, головна перевага цього проєкту.

Наприклад, на початку:

```cpp
double sigmoid(double x)
```

Потім:

```cpp
double sigmoidDerivative(double x)
```

Потім:

```cpp
class Sigmoid : public Activation
```

Потім:

```cpp
Vector Sigmoid::forward(const Vector& x)
```

Потім:

```cpp
Vector Sigmoid::backward(const Vector& gradient)
```

І зрештою:

```cpp
model.add(Sigmoid());
```

Тобто студенти бачать **як одна математична ідея перетворюється на програмну абстракцію**.

---

# 28. Git-модель залишається такою ж, але стає професійнішою

Один repository:

```text
MiniAI
```

Не:

```text
student1_project
student2_project
...
```

Кожне завдання:

```text
GitHub Issue
      ↓
branch
      ↓
implementation
      ↓
tests
      ↓
commit
      ↓
Pull Request
      ↓
review
      ↓
merge
```

Наприклад:

```text
feature/math-sigmoid
feature/math-derivative
feature/vector-dot
feature/matrix-multiply
feature/ml-relu
feature/ml-dense
feature/optimizer-gd
feature/data-loader
```

Commit:

```text
feat(math): implement sigmoid function
```

```text
test(math): add sigmoid boundary tests
```

```text
feat(vector): implement dot product
```

```text
feat(optimizer): implement gradient descent
```

---

# 29. PR повинен бути маленьким

Наприклад, студент не робить:

```text
feat: implement entire neural network
```

А:

```text
PR #31
Implement sigmoid activation

Changes:
- add Sigmoid class
- implement forward()
- implement derivative()
- add tests
- update documentation
```

Інший:

```text
PR #32
Implement vector dot product
```

Третій:

```text
PR #33
Implement matrix multiplication
```

Таким чином викладач бачить реальний індивідуальний внесок кожного студента.

---

# 30. Дуже важливий принцип оцінювання

Я б оцінював не лише фінальний код.

Наприклад:

| Компонент                 | Частка |
| ------------------------- | -----: |
| Individual implementation |    30% |
| Git commits               |    10% |
| Pull Requests             |    15% |
| Code review               |    10% |
| Mathematical correctness  |    15% |
| Tests                     |    10% |
| Final integration         |    10% |

Це дуже добре захищає від ситуації:

> «Один студент написав усе, а ще четверо просто числяться в команді».

---

# 31. Фінальний результат

На останньому занятті студенти повинні мати можливість показати:

```text
$ miniai train xor.txt model.bin

Dataset loaded: 4 samples
Input dimension: 2
Output dimension: 1

Model:
Dense(2, 8)
ReLU
Dense(8, 1)
Sigmoid

Optimizer:
Gradient Descent
learning rate = 0.1

Training...

Epoch     Loss
----------------
0         0.6931
100       0.4212
500       0.0874
1000      0.0132

Model saved.
```

Потім:

```text
$ miniai predict model.bin 0 1

Prediction = 0.984
Class = 1
```

І це вже виглядає не як набір лабораторних робіт, а як **справжній маленький software engineering + mathematical AI project**.

---

# 32. Розвиток проєкту за версіями

roadmap:

```text
v0.1  Scalar Engine
v0.2  Mathematical Functions
v0.3  Vector
v0.4  Numerical Methods
v0.5  Optimizer
v0.6  Dynamic Memory
v0.7  Matrix
v0.8  Dataset
v0.9  File Storage
v1.0  Mathematical OOP Core
v1.1  Activation Functions
v1.2  Layer API
v1.3  Dense Layer
v1.4  Loss Functions
v1.5  Gradient Descent
v1.6  Neural Network
v1.7  Serialization
v1.8  STL Refactoring
v2.0  MiniAI Framework
```

## Фінальна мета

Не:

> «Студент виконав 21 лабораторну».

А:

> **«Студент протягом семестру брав участь у розробці власного C++ framework для математичного машинного навчання, використовуючи всі основні конструкції мови, які вивчалися на курсі».**

І це дуже добре відповідає самій філософії методички: вона також задумана як послідовне проходження лабораторних, де теми й завдання вводять синтаксис поступово.
