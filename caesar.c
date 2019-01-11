#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string ciphertext = "";
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        k = k % 26;
        string plaintext = get_string("plaintext:");
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plaintext); i++)
        {
          if (isalpha(plaintext[i]))
          {
              if (isupper(plaintext[i]))
              {
                  printf("%c",(plaintext[i] - 65 + k) % 26 + 65);
              }
              if (islower(plaintext[i]))
              {
                  printf("%c",(plaintext[i] - 97 + k) % 26 + 97);
              }
          }
          else
          {
              printf("%c",plaintext[i]);
          }
        }
        printf("\n");
    }

    else
    {
        printf("error");
        return 1;
    }
}