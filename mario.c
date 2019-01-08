#include <stdio.h>
#include <cs50.h>



int main(void)
{
    int t = 0;
    int x;
    
    do
    {
        x = get_int("x: ");
    }
    while (x < 0 || x > 23)
        
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x - i - 1; j++)
        {
            printf(" ");
        }

    for (int j = 0; j <= i + 1; j++)
        {
            printf("#");
        }

    printf("\n");
    }
}
