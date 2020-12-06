#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Cash money

int main(void)
{
    float change;
    do
    {
        change = get_float("How much change we owe you?\n");
    }
    while (change <= 0);

    //Prompts user to enter amount of change. Must be positive, otherwise the program will continue to ask.

    //program logic starts here.

    int cents = round(change * 100);

    int q, d, n, p;
    q = cents / 25;
    // printf("%i\n", q);
    cents = cents - q * 25;

    d = cents / 10;
    // printf("%i\n", d);
    cents = cents - d * 10;

    n = cents / 5;
    // printf("%i\n", n);
    cents = cents - n * 5;

    p = cents / 1;
    // printf("%i\n", p);
    int coins = q + d + n + p;
    printf("%i\n", coins);
}

