#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int l = 0;
    if (argc !=2)
    {
        printf("error\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("error\n");
            return 1;
        }
    }
    string k = argv[1];
    string plaintext = get_string("plaintext:");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
      if (isalpha(plaintext[i]))
      {
        if (isupper(plaintext[i]))
          {
            if (isupper(k[i % strlen(k)]))
            {
              printf("%c",(plaintext[i] - 65 + k[l % strlen(k)] - 65) % 26 + 65);
              l++;
            }
            if (islower(k[i % strlen(k)]))
            {
              printf("%c",(plaintext[i] - 65 + k[l % strlen(k)] - 97) % 26 + 65);
              l++;
            }
          }
          if (islower(plaintext[i]))
          {
            if (isupper(k[i % strlen(k)]))
            {
              printf("%c\n",(plaintext[i] - 97 + k[l % strlen(k)] - 65) % 26 + 97);
              l++;
            }
            if (islower(k[i % strlen(k)]))
            {
             printf("%c",(plaintext[i] - 97 + k[l % strlen(k)] - 97) % 26 + 97);
             l++;
            }
          }
      }
      else
      {
       printf("%c",plaintext[i]);
      }
     }
     printf("\n");
}
