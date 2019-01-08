#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int c = 0;
    float x = get_float("x: ");

    while ( x < 0)
    {
        x = get_float("x: ");
    }
    x = x * 100;
    double round(double x);
    if ((x / 25) > 0)
    {
        c = c + (x / 25);
        x = (int)x % 25;
    }

        if ((x / 10) > 0)
    {
        c = c + (x / 10);
        x = (int)x % 10;
    }

        if ((x / 5) > 0)
    {
        c = c + (x / 5);
        x = (int)x % 5;
    }

        if (x > 0)
    {
        c = c + x;
    }


    printf("%i\n", c);
}
