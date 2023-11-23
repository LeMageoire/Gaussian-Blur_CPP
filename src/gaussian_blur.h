#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#define EXPECTED_ARGUMENTS (4)
#define ARG_INPUT_FILE (1)
#define ARG_KERNEL_SIZE (2)
#define ARG_SIGMA (3)

typedef struct s_Pixel {
    unsigned char red, green, blue, alpha;
} t_Pixel;

#endif //GAUSSIAN_BLUR_H