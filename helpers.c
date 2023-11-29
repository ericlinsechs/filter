#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sum = image[i][j].rgbtRed + image[i][j].rgbtGreen +
                      image[i][j].rgbtBlue;

            int ave = round((float) sum / 3);

            RGBTRIPLE gray_scale = {
                .rgbtRed = ave, .rgbtGreen = ave, .rgbtBlue = ave};
            image[i][j] = gray_scale;
        }
    }
    return;
}

void swap(RGBTRIPLE *p1, RGBTRIPLE *p2)
{
    RGBTRIPLE tmp_p = *p1;
    *p1 = *p2;
    *p2 = tmp_p;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = round((float) width / 2);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < mid; j++)
            swap(&image[i][j], &image[i][width - 1 - j]);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_img[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            unsigned int cnt = 0;

            for (int x = i - 1; x <= (i + 1); x++) {
                if (x < 0 || x >= height)
                    continue;
                for (int y = j - 1; y <= (j + 1); y++) {
                    if (y < 0 || y >= width)
                        continue;
                    sum_r += image[x][y].rgbtRed;
                    sum_g += image[x][y].rgbtGreen;
                    sum_b += image[x][y].rgbtBlue;
                    cnt++;
                }
            }

            tmp_img[i][j].rgbtRed = round((float) sum_r / cnt);
            tmp_img[i][j].rgbtGreen = round((float) sum_g / cnt);
            tmp_img[i][j].rgbtBlue = round((float) sum_b / cnt);
        }
    }

    memcpy(image, tmp_img, sizeof(RGBTRIPLE) * height * width);

    return;
}

int *convolution(const int height,
                 const int width,
                 const int col,
                 const int row,
                 const int kernel[3][3],
                 RGBTRIPLE image[height][width])
{
    int *sum = malloc(sizeof(int) * 3);
    if (!sum)
        return NULL;

    // Initialize the sum values
    sum[0] = 0; // Red
    sum[1] = 0; // Green
    sum[2] = 0; // Blue

    for (int x = col - 1, kx = 0; kx <= 2 && x < height; x++, kx++) {
        if (x < 0)
            continue;
        for (int y = row - 1, ky = 0; ky <= 2 && y < width; y++, ky++) {
            if (y < 0)
                continue;
            sum[0] += image[x][y].rgbtRed * kernel[kx][ky];
            sum[1] += image[x][y].rgbtGreen * kernel[kx][ky];
            sum[2] += image[x][y].rgbtBlue * kernel[kx][ky];
        }
    }

    return sum;
}

BYTE combine(int gx, int gy)
{
    unsigned long gradient = (unsigned long) round(sqrt(gx * gx + gy * gy));
    if (gradient > 0xff)
        gradient = 0xff;

    return (BYTE) gradient;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define Sobel kernels
    int mx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int my[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE tmp_img[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int *gx, *gy;
            gx = convolution(height, width, i, j, mx, image);
            gy = convolution(height, width, i, j, my, image);

            tmp_img[i][j].rgbtRed = combine(gx[0], gy[0]);
            tmp_img[i][j].rgbtGreen = combine(gx[1], gy[1]);
            tmp_img[i][j].rgbtBlue = combine(gx[2], gy[2]);

            free(gx);
            free(gy);
        }
    }

    memcpy(image, tmp_img, sizeof(RGBTRIPLE) * height * width);

    return;
}
