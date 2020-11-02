#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = roundf((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/(double)3);
            // avg = roundf(avg);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
//   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = roundf(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = roundf(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = roundf(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

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

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(j < width/2)
            {
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            }
            else
            {
            image[i][j].rgbtBlue = temp[i][width-1-j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][width-1-j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][width-1-j].rgbtRed;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                //top left corner case (1 pixel)
                float avgRed = roundf((
                + temp[i][j].rgbtRed
                + temp[i][j+1].rgbtRed
                + temp[i+1][j].rgbtRed
                + temp[i+1][j+1].rgbtRed
                )/(double)4);

                float avgGreen = roundf((
                temp[i][j].rgbtGreen
                + temp[i][j+1].rgbtGreen
                + temp[i+1][j].rgbtGreen
                + temp[i+1][j+1].rgbtGreen
                )/(double)4);

                float avgBlue = roundf((
                temp[i][j].rgbtBlue
                + temp[i][j+1].rgbtBlue
                + temp[i+1][j].rgbtBlue
                + temp[i+1][j+1].rgbtBlue
                )/(double)4);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }

            //top row except for corners
            else if (i == 0 && j > 0 && j < width-1)
            {
                    float avgRed = roundf((
                      temp[i][j-1].rgbtRed
                    + temp[i][j].rgbtRed
                    + temp[i][j+1].rgbtRed
                    + temp[i+1][j-1].rgbtRed
                    + temp[i+1][j].rgbtRed
                    + temp[i+1][j+1].rgbtRed
                    )/(double)6);

                    float avgGreen = roundf((
                      temp[i][j-1].rgbtGreen
                    + temp[i][j].rgbtGreen
                    + temp[i][j+1].rgbtGreen
                    + temp[i+1][j-1].rgbtGreen
                    + temp[i+1][j].rgbtGreen
                    + temp[i+1][j+1].rgbtGreen
                    )/(double)6);

                    float avgBlue = roundf((
                      temp[i][j-1].rgbtBlue
                    + temp[i][j].rgbtBlue
                    + temp[i][j+1].rgbtBlue
                    + temp[i+1][j-1].rgbtBlue
                    + temp[i+1][j].rgbtBlue
                    + temp[i+1][j+1].rgbtBlue
                    )/(double)6);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;

            }

            //top right corner case
            else if (i == 0 && j == width -1)
            {
                float avgRed = roundf((
                  temp[i][j-1].rgbtRed
                + temp[i][j].rgbtRed
                + temp[i+1][j-1].rgbtRed
                + temp[i+1][j].rgbtRed
                )/(double)4);

                float avgGreen = roundf((
                  temp[i][j-1].rgbtGreen
                + temp[i][j].rgbtGreen
                + temp[i+1][j-1].rgbtGreen
                + temp[i+1][j].rgbtGreen
                )/(double)4);

                float avgBlue = roundf((
                  temp[i][j-1].rgbtBlue
                + temp[i][j].rgbtBlue
                + temp[i+1][j-1].rgbtBlue
                + temp[i+1][j].rgbtBlue
                )/(double)4);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }

            //left edge except corners
            else if (i > 0 && i < height - 1 && j == 0)
            {
                float avgRed = roundf((
                  temp[i-1][j].rgbtRed
                + temp[i-1][j+1].rgbtRed
                + temp[i][j].rgbtRed
                + temp[i][j+1].rgbtRed
                + temp[i+1][j].rgbtRed
                + temp[i+1][j+1].rgbtRed
                )/(double)6);

                float avgGreen = roundf((
                  temp[i-1][j].rgbtGreen
                + temp[i-1][j+1].rgbtGreen
                + temp[i][j].rgbtGreen
                + temp[i][j+1].rgbtGreen
                + temp[i+1][j].rgbtGreen
                + temp[i+1][j+1].rgbtGreen
                )/(double)6);

                float avgBlue = roundf((
                  temp[i-1][j].rgbtBlue
                + temp[i-1][j+1].rgbtBlue
                + temp[i][j].rgbtBlue
                + temp[i][j+1].rgbtBlue
                + temp[i+1][j].rgbtBlue
                + temp[i+1][j+1].rgbtBlue
                )/(double)6);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }

            //right edge except corners
            else if (i > 0 && i < height - 1 && j == width-1)
            {
                float avgRed = roundf((
                  temp[i-1][j-1].rgbtRed
                + temp[i-1][j].rgbtRed
                + temp[i][j-1].rgbtRed
                + temp[i][j].rgbtRed
                + temp[i+1][j-1].rgbtRed
                + temp[i+1][j].rgbtRed
                )/(double)6);

                float avgGreen = roundf((
                  temp[i-1][j-1].rgbtGreen
                + temp[i-1][j].rgbtGreen
                + temp[i][j-1].rgbtGreen
                + temp[i][j].rgbtGreen
                + temp[i+1][j-1].rgbtGreen
                + temp[i+1][j].rgbtGreen
                )/(double)6);

                float avgBlue = roundf((
                  temp[i-1][j-1].rgbtBlue
                + temp[i-1][j].rgbtBlue
                + temp[i][j-1].rgbtBlue
                + temp[i][j].rgbtBlue
                + temp[i+1][j-1].rgbtBlue
                + temp[i+1][j].rgbtBlue
                )/(double)6);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }
            //bottom edge
            else if (i == height-1 && j > 0 && j < width -1)
            {
                float avgRed = roundf((
                  temp[i-1][j-1].rgbtRed
                + temp[i-1][j].rgbtRed
                + temp[i-1][j+1].rgbtRed
                + temp[i][j-1].rgbtRed
                + temp[i][j].rgbtRed
                + temp[i][j+1].rgbtRed
                )/(double)6);

                float avgGreen = roundf((
                  temp[i-1][j-1].rgbtGreen
                + temp[i-1][j].rgbtGreen
                + temp[i-1][j+1].rgbtGreen
                + temp[i][j-1].rgbtGreen
                + temp[i][j].rgbtGreen
                + temp[i][j+1].rgbtGreen
                )/(double)6);

                float avgBlue = roundf((
                  temp[i-1][j-1].rgbtBlue
                + temp[i-1][j].rgbtBlue
                + temp[i-1][j+1].rgbtBlue
                + temp[i][j-1].rgbtBlue
                + temp[i][j].rgbtBlue
                + temp[i][j+1].rgbtBlue
                )/(double)6);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }
            //bottom left corner
            else if (i == height-1 && j == 0)
            {
                float avgRed = roundf((
                  temp[i-1][j].rgbtRed
                + temp[i-1][j+1].rgbtRed
                + temp[i][j].rgbtRed
                + temp[i][j+1].rgbtRed
                )/(double)4);

                float avgGreen = roundf((
                  temp[i-1][j].rgbtGreen
                + temp[i-1][j+1].rgbtGreen
                + temp[i][j].rgbtGreen
                + temp[i][j+1].rgbtGreen
                )/(double)4);

                float avgBlue = roundf((
                  temp[i-1][j].rgbtBlue
                + temp[i-1][j+1].rgbtBlue
                + temp[i][j].rgbtBlue
                + temp[i][j+1].rgbtBlue
                )/(double)4);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }
            //bottom right corner
            else if (i == height-1 && j == width -1)
            {
                float avgRed = roundf((
                  temp[i-1][j-1].rgbtRed
                + temp[i-1][j].rgbtRed
                + temp[i][j-1].rgbtRed
                + temp[i][j].rgbtRed
                )/(double)4);

                float avgGreen = roundf((
                  temp[i-1][j-1].rgbtGreen
                + temp[i-1][j].rgbtGreen
                + temp[i][j-1].rgbtGreen
                + temp[i][j].rgbtGreen
                )/(double)4);

                float avgBlue = roundf((
                  temp[i-1][j-1].rgbtBlue
                + temp[i-1][j].rgbtBlue
                + temp[i][j-1].rgbtBlue
                + temp[i][j].rgbtBlue
                )/(double)4);

                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }

            //this scenario should take up >99.9% of cases (middle cases)
            else if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                float avgRed = roundf((
                                          temp[i-1][j-1].rgbtRed
                                        + temp[i-1][j].rgbtRed
                                        + temp[i-1][j+1].rgbtRed
                                        + temp[i][j-1].rgbtRed
                                        + temp[i][j].rgbtRed
                                        + temp[i][j+1].rgbtRed
                                        + temp[i+1][j-1].rgbtRed
                                        + temp[i+1][j].rgbtRed
                                        + temp[i+1][j+1].rgbtRed
                                        )/(double)9);

                float avgGreen = roundf((
                                          temp[i-1][j-1].rgbtGreen
                                        + temp[i-1][j].rgbtGreen
                                        + temp[i-1][j+1].rgbtGreen
                                        + temp[i][j-1].rgbtGreen
                                        + temp[i][j].rgbtGreen
                                        + temp[i][j+1].rgbtGreen
                                        + temp[i+1][j-1].rgbtGreen
                                        + temp[i+1][j].rgbtGreen
                                        + temp[i+1][j+1].rgbtGreen
                                        )/(double)9);

                float avgBlue = roundf((
                                           temp[i - 1][j - 1].rgbtBlue
                                           + temp[i - 1][j].rgbtBlue
                                           + temp[i - 1][j + 1].rgbtBlue
                                           + temp[i][j - 1].rgbtBlue
                                           + temp[i][j].rgbtBlue
                                           + temp[i][j + 1].rgbtBlue
                                           + temp[i + 1][j - 1].rgbtBlue
                                           + temp[i + 1][j].rgbtBlue
                                           + temp[i + 1][j + 1].rgbtBlue
                                        ) / (double)9);
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
            }

            else
            {
                float avg = roundf((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (double)3);
                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtRed = avg;

            }
        }
    }
    return;
}
