# Gaussian-Blur_CPP
My C++17 implementation of a Gaussian Blur for Image

## Concept
- the PNG file is class derived from File abstract class
- File abstract class forces to have read/write implementations
- I create an Image based on the type of file given
- Then I create the kernel (which relies on templating to have diverses multiplications solutions types as it might differ from Hardware)
- Then the Image is filtered
- a second PNG file is created and the write method is called
- The Idea was to 

--

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

from the litterature, I've read that there's possibility to optimize the kernel calculation using the separability of their kernel which is more efficient than performing a signle 2D convolution

---

## What's C++ google coding styles
https://github.com/google/styleguide
https://google.github.io/styleguide/cppguide.html

- optimize for reader
- be consistent with existing code
- avoid surprising or dangerous constructs
- Avoid constructs that our average C++ programmer would find tricky or hard to maintain
- Be mindful of our scale
- Concede to optimization when necessary
- Consider portability to other environments before using features from C++17 and C++20

## To-Do
- [ ] improvements about the automation of the build