#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//program accepts a string and encrypts it with a key value provided by user.
// 1. prompt for a key value
//      - ensure it is a Number, if not, keep asking
// 2. prompt for a text / string
// 3. take each alpha character in string, and transpose it by the key value provided in step 1
//    - if the number is bigger than 26, then subtract by multiples of 26 until it is 26 or under.
// 4. output encrypted string


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int n = strlen(argv[1]);
    // printf("%i\n",n);
    for (int i = 0; i < n; i++)
    {
        if (isdigit(argv[1][i]))
        {
            // printf("nice job\n");
            // return 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    // printf("%i\n", key);

    string text;
    do
    {
        text = get_string("plaintext: ");
    }
    while (text <= 0);

    int remainder = key % 26;
    // printf("%i\n", remainder);

    printf("ciphertext: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if (islower(text[i]))
        {
            // printf("%c", text[i]+remainder);
            //If lower-case alpha (122 is binary for "z")
            if (text[i] + remainder > 122)
            {
                printf("%c", text[i] + remainder - 26);
            }

            else

            {
                printf("%c", text[i] + remainder);
            }

            //remainder =text[i]+remainder-26;
            // printf("%i,", (int)text[i]);
            // printf("%c", text[i]+key);
        }

        else if (isupper(text[i]))
        {
            //If upper-case alpha (90 is binary for "Z")
            if (text[i] + remainder > 90)
            {
                printf("%c", text[i] + remainder - 26);
            }
            else
            {
                printf("%c", text[i] + remainder);
            }
        }

        else
        {
            printf("%c", text[i]);
        }

    }

    printf("\n");

    // printf("%s\n", text);

    //65:A
    //90: Z
    //97: a
    //122: z

    // printf("Success\n");
    // printf("%s\n",argv[1]);
    // return 0;
    // do
    // {
    //     text = get_string("Text: ");
    // }
    // while (text <= 0);
}