#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//program assesses the readability grade level of a text passage.

int main(void)
{
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (text <= 0);

    int n = strlen(text);
    printf("%i characters\n", n);
    int alpha = 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i <= n; i++)
    {
        if (isalpha(text[i]))
        {
           alpha++;

        }
    }

     printf("%i letters\n", alpha);

    //checking for # of words now
    for (int i = 0; i <= n; i++)
    {
        if (isspace(text[i]))
        {
           words++;
        }
    }
    printf("%i words\n", words);

    //checking for # of sentences now
    for (int i = 0; i <= n; i++)
    {
        //if (text[i] == "." || text[i] == "!" || text[i] == "?")
        // if(strcmp(text[i], "."))
        if (text[i] == *(".") || text[i] == *("!") || text[i] == *("?"))

        {
            sentences++;
        }
    }
    printf("%i sentences\n", sentences);

    //L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    //index = 0.0588 * L - 0.296 * S - 15.8

    float L = (float) alpha / (float) words * 100;
    printf("L: %f\n", L);

    float S = (float) sentences / (float) words * 100;
    printf("S: %f\n", S);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1.5)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 15.5)
    {
        printf("Grade 16+\n");
    }
    else
    {    
        printf("Grade %.0f\n", index);
    }
}