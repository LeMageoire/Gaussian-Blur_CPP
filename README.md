# Gaussian-Blur_CPP
My C++17 implementation of a Gaussian Blur for Image

```bash
g++ -o Gaussian_Blur_CLI gaussian_blur.cpp  -lpng -I/third-party/libpng/ -L/third-party/libpng/build clear
```

## To-Do
- [ ] find a .png I/O lib
- [ ] feature 
- [ ] tests 
- [ ] Reading C++ style covention of Google
- [ ] Add a CI for linting of my C++ code (usage of cpplint)


## Special cases
- Kernel size should be an odd number
- Specific handling should be taken into account for "edges" of the images (because the convolution would be "out" of boundaries of the image)
    - the implementation use the "mirroiring"

```
Image:             Mirrored Image:
+---+---+---+       +---+---+---+
| A | B | C |       | C | B | A |
+---+---+---+       +---+---+---+
| D | E | F |  -->  | F | E | D |
+---+---+---+       +---+---+---+
| G | H | I |       | I | H | G |
+---+---+---+       +---+---+---+
```
- here's a basic representation with a 3x3 kernel, and the concept can be propagated to bigger odd numbers (5x5,7x7)

you have differents scenarios :
1) the first column is outside (showed in picture), you use the third one (meaning A->C, D->F, G->I) as "neighbours pixels", so you don't introduce artifacts in the image ("spatial continuity").

2) Special case : if ABCDG is out of the original image, what should I do ? many solutions exists and there's nuances
```
Image:             Mirrored Image:
+---+---+---+       +---+---+---+
| A | B | C |       | I | H | I |
+---+---+---+       +---+---+---+
| D | E | F |  -->  | F | E | F |
+---+---+---+       +---+---+---+
| G | H | I |       | I | H | I |
+---+---+---+       +---+---+---+
```
other proposition :

Extend :
Image:             Mirrored Image:
+---+---+---+       +---+---+---+
| A | B | C |       | E | E | H |
+---+---+---+       +---+---+---+
| D | E | F |  -->  | E | E | F |
+---+---+---+       +---+---+---+
| G | H | I |       | H | H | I |
+---+---+---+       +---+---+---+
Image:             Mirrored Image:
+---+---+---+       +---+---+---+
| A | B | C |       | I | H | I |
+---+---+---+       +---+---+---+
| D | E | F |  -->  | F | E | F |
+---+---+---+       +---+---+---+
| G | H | I |       | I | H | I |
+---+---+---+       +---+---+---+
Other solution implies circular buffering 

litteratures on this suggest theses technics
extend : the nearest border pixels are conceptually extended as far as necessary
wrap : values are taken from the opposite corner
mirroir:
cropping: you don't calculated the outer pixels , so the image output is smaller
kernelcropping: you adjust the kernel , the 
constant: you

## Cmake notes
- cmake -S -B .
- update the Cmakelist.txt


## Definition of the Gaussian Blur
```pseudo-code
for each image row in input image:
    for each pixel in image row:

        set accumulator to zero

        for each kernel row in kernel:
            for each element in kernel row:

                if element position  corresponding* to pixel position then
                    multiply element value  corresponding* to pixel value
                    add result to accumulator
                endif
         set output image pixel to accumulator
```
from the litterature, I've read that there's possibility to optimize the kernel calculation using the separability of their kernel which is more efficient than performing a signle 2D convolution


## What's are C++ coding styles
https://github.com/google/styleguide
https://google.github.io/styleguide/cppguide.html

- optimize for reader
- be consistent with existing code
- avoid surprising or dangerous constructs
- Avoid constructs that our average C++ programmer would find tricky or hard to maintain
- Be mindful of our scale
- Concede to optimization when necessary
- Consider portability to other environments before using features from C++17 and C++20
### Concretes actions
- do not use not standard C++ such as :
  GCC's attribute
  intrinsic function
  prama
  elvis operator ?: (A ? A : B => A ?: B)
- every .cc file should have a .h file (except for unit test and main())

- header files should self-contained
- header with header guards
- define guard are  <PROJECT>_<PATH>_<FILE>_H_.
- so uniqueness is guranteed
- only include the used include header file
- do not rely on transitive inclusion
- meaning if foo.h include bar.h you should include both


- do not use forward declaration (declaration without definition)
#### names and order of includes

- header
- forward declaration
- names and order of includes
- scoping 
- internal linkage
- nonmember, static member, and Global functions
- Local variables
- Static and Global variables
- Thread_local variables
- Classes
- Copyable and movable types
- Struct vs Copy
- Structs vs pair and tuples
- Inheritance
- Operator Overloading
- Access Control
- Declaration Order
- Functions
- Inputs and Outputs
- function Overloading
- default arguments
- Trailing Return Type Syntax
- Google-Specific Magic
    - Ownership and Smart Pointers
    - use cpplint.py to detect style error (is has FP and FN)
- Other C++ Features
    - Rvalue references
    - Friends
    - Exceptions (do not use)
    - noexpect 
    - RTTI (Run-Time type information)
    - Casting
    - PreIncrement and Predecrement
    - Use of const
    - Use of constexpr, const init and consteval
    - Integer Types
    - 64-bit portability
    - Preprocessor Macros
    - 0 and nullptr/NULL
    - sizeof
    - type deduction (including auto)
    - function template argument deduction
    - local variable type deduction
    - local varuable type deduction
    - return type deduction
    - parameter type deduction
    - lambda init captures
    - structured bindings
    - Class Template Argument Deduction
    - Designated Initializers
    - Lambda Expressions
    - Template Metaprogramming
    - Concepts and Constraints
    - Boost libraries (use only approuved
    - Other C++ Features
    - Nonstandard
    - Aliases
    - Switch Statements
- Inclusive Language
- Naming
- General Naming Rules
- File Names
- Type Names
- Variable Names (SNAKE CASED = table_name)
- Constant Name (k behind the word)
- Function Names
- Names space names
- Enumerator Names
- Macro Names
- Exceptions to Naming Rules
- Comments
- Comment Style
- File Comments
- Legal Notice and Author Line
- Struct and Class Comments
- Variables Comments
- TODO comments
- FORMATTING
- Exceptions to the Rules

---

## Cmake notes

```Cmake
ADD_SUBDIRECTORY()
ADD_EXECUTABLE()
INCLUDE_DIRECTORIES()
ADD_DEFINITIONS
TARGET_LINK_LIBRARIES()
```
- problem
- problem of modularity
- public dependancy
	- go upwards
- Forbid /report circular and hidden dependencies

---

# usage of a PNG reader ()
git@github.com:lvandeve/lodepng.git

```

```

# PNG docs
http://www.libpng.org/pub/png/pngdocs.html