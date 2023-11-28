#include "helpers.h"
#include <math.h>

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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
