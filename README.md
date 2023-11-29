# Filter

This program performs various image processing operations, including grayscale conversion, horizontal reflection, image blurring, and edge detection using the Sobel operator.

## Features

1. **Grayscale Conversion:** Converts the input image to grayscale.

2. **Horizontal Reflection:** Reflects the input image horizontally.

3. **Image Blurring:** Applies a blur effect to the input image.

4. **Edge Detection:** Applies the Sobel edge detection algorithm to highlight edges in the image.

## How to Use

Compile the code using the provided Makefile:

   ```bash
   make
   ```

Run the compiled executable:

    ./filter [flag] infile outfile
`[flag]` is a single character specifying the desired filter: 
* `-b`: blur
* `-e`: edges
* `-g`: grayscale
* `-r`: reflection.

For example:

    ./filter -g images/yard.bmp out.bmp

## Reference
The source code for this project is based on the [Harvard University’s CS50 course](https://cs50.harvard.edu/x/2023/). You can find the original source code and problem description from the ["Filter (More)" problem set](https://cs50.harvard.edu/x/2023/psets/4/filter/more).