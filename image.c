#include "helpers.h"
#include <math.h>

// Convert image to grayscale
//functions averages the colors to make it
///a shade of gray
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
//using certian equation
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed  + .769 * image[i][j].rgbtGreen  + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed  + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed  + .534 * image[i][j].rgbtGreen  + .131 * image[i][j].rgbtBlue);

            ///cannot be over 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;

        }
    }
    return;
}

// Blur image
///box method
//averages the colors of nearby pixals
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int averageRed;
    int averageBlue;
    int averageGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            averageRed = 0;
            averageBlue = 0;
            averageGreen = 0;

            ////pixal in corner
            ////
            ///top to bottom
            ///left to right
            if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == height - 1 && j  == width - 1))
            {
                if (i == 0 && j == 0)
                {
                    averageRed = round((image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                    averageGreen = round((image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + 
                                          image[i][j].rgbtGreen) / 4.0);
                    averageBlue = round((image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) /
                                        4.0);
                }
                else if (i == 0 && j == width - 1)
                {
                    averageRed = round((image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                    averageGreen = round((image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 
                                          image[i][j].rgbtGreen) / 4.0);
                    averageBlue = round((image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 
                                        4.0);
            
                }
                else if (i == height - 1 && j == 0)
                {
                    averageRed = round((image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                    averageGreen = round((image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                          image[i][j].rgbtGreen) / 4.0);
                    averageBlue = round((image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) /
                                        4.0);
            
                }
                else
                {
                    averageRed = round((image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                    averageGreen = round((image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                          image[i][j].rgbtGreen) / 4.0);
                    averageBlue = round((image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                                        4.0);
                }
            }
            ////pixal in left boder
            else if (j == 0)
            {
                for (int x = i - 1; x <= i + 1 ; x++)
                {
                    averageRed = averageRed + image[x][j].rgbtRed + image[x][j + 1].rgbtRed;
                    averageGreen = averageGreen + image[x][j].rgbtGreen + image[x][j + 1].rgbtGreen;
                    averageBlue = averageBlue + image[x][j].rgbtBlue + image[x][j + 1].rgbtBlue;
                }
                averageRed = round((averageRed) / 6.0);
                averageGreen = round((averageGreen) / 6.0);
                averageBlue = round((averageBlue) / 6.0);

            }
            ////pixal on right bordor
            else if (j == width - 1)
            {
                for (int x = i - 1; x <= i + 1 ; x++)
                {
                    averageRed = averageRed + image[x][j].rgbtRed + image[x][j - 1].rgbtRed;
                    averageGreen = averageGreen + image[x][j].rgbtGreen + image[x][j - 1].rgbtGreen;
                    averageBlue = averageBlue + image[x][j].rgbtBlue + image[x][j - 1].rgbtBlue;
                }
                averageRed = round((averageRed) / 6.0);
                averageGreen = round((averageGreen) / 6.0);
                averageBlue = round((averageBlue) / 6.0);
            }

            ////pixal on top border
            else if (i == 0)
            {
                for (int x = j - 1; x <= j + 1 ; x++)
                {
                    averageRed = averageRed + image[i][x].rgbtRed + image[i + 1][x].rgbtRed;
                    averageGreen = averageGreen + image[i][x].rgbtGreen + image[i + 1][x].rgbtGreen;
                    averageBlue = averageBlue + image[i][x].rgbtBlue + image[i + 1][x].rgbtBlue;
                }
                averageRed = round((averageRed) / 6.0);
                averageGreen = round((averageGreen) / 6.0);
                averageBlue = round((averageBlue) / 6.0);
            }
            ////pixal on bottom border
            else if (i == height - 1)
            {
                for (int x = j - 1; x <= j + 1 ; x++)
                {
                    averageRed = averageRed + image[i][x].rgbtRed + image[i - 1][x].rgbtRed;
                    averageGreen = averageGreen + image[i][x].rgbtGreen + image[i - 1][x].rgbtGreen;
                    averageBlue = averageBlue + image[i][x].rgbtBlue + image[i - 1][x].rgbtBlue;
                }
                averageRed = round((averageRed) / 6.0);
                averageGreen = round((averageGreen) / 6.0);
                averageBlue = round((averageBlue) / 6.0);
            }

            ////middle pixal
            else
            {
                for (int x = i - 1; x <= i + 1; x++)
                {
                    for (int y = j - 1; y <= j + 1; y++)
                    {
                        averageRed = averageRed + image[x][y].rgbtRed;
                        averageGreen = averageGreen + image[x][y].rgbtGreen;
                        averageBlue = averageBlue + image[x][y].rgbtBlue;

                    }
                }
                averageRed = round((averageRed) / 9.0);
                averageGreen = round((averageGreen) / 9.0);
                averageBlue = round((averageBlue) / 9.0);

            }
            temp[i][j].rgbtRed = averageRed;
            temp[i][j].rgbtBlue = averageBlue;
            temp[i][j].rgbtGreen = averageGreen;


        }
    }
    ////// for loop transfers new image to out.bmp
    ///
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
