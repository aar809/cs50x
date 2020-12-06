#include <cs50.h>
#include <stdio.h>

//this program builds a pyramid of hashes according to height inputted by user.

int main(void)
{
    int n;
    do
    {
        n = get_int("Height (between 1 and 8): ");
    }
    while (n < 1 || n > 8);

    //Prompts user to enter Height for pyramid. Must be between 1 and 8, otherwise the program will continue to ask.

    for (int i = 1; i <= n; i++)
    {
        for (int k = 1; k <= n - i ; k++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
//prints the pyramid with the inputted height, right-aligned.

