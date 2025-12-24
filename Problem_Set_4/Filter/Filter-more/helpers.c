#include "helpers.h"
#include <math.h> // Include math.h for round() function
#include <stdlib.h> // Not strictly needed for these functions, but often useful

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of Red, Green, and Blue, then round it
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int rounded_avg = round(avg);

            // Set all channels to the average
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels using a temporary RGBTRIPLE
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image to read from
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through each pixel in the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalR = 0;
            float totalG = 0;
            float totalB = 0;
            int count = 0;

            // Loop through the 3x3 neighbor grid (including the pixel itself)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighbor is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalR += copy[ni][nj].rgbtRed;
                        totalG += copy[ni][nj].rgbtGreen;
                        totalB += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average and update the original image
            image[i][j].rgbtRed = round(totalR / count);
            image[i][j].rgbtGreen = round(totalG / count);
            image[i][j].rgbtBlue = round(totalB / count);
        }
    }

    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            copy[i][j] = image[i][j];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxR = 0, GxG = 0, GxB = 0;
            float GyR = 0, GyG = 0, GyB = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        GxR += copy[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        GyR += copy[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        // Repeat for Green and Blue...
                        GxG += copy[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        GyG += copy[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        GxB += copy[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];
                        GyB += copy[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }

            int red = round(sqrt(GxR * GxR + GyR * GyR));
            int green = round(sqrt(GxG * GxG + GyG * GyG));
            int blue = round(sqrt(GxB * GxB + GyB * GyB));

            image[i][j].rgbtRed = red > 255 ? 255 : red;
            image[i][j].rgbtGreen = green > 255 ? 255 : green;
            image[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
}
