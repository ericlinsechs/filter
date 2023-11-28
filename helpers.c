#include "helpers.h"
#include <math.h>
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
