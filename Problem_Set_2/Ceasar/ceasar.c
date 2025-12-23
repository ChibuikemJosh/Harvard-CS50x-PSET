#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype to cipher text with key
string cipher(string plain_text, int key);

int main(int argc, string argv[])
{
    // check if it has two outputs and remind the user that it needs to input ./ceaser key to
    if (argc != 2)
    {
        printf("./caesar key\n");
        return 1;
    }

    // iterate each character in the argument
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // print ./ceasar key if a character is not a digit
        if (!isdigit(argv[1][i]))
        {
            //
            printf("./caesar key\n");
            return 1;
        }
    }

    // convert the argument to a number
    int key = atoi(argv[1]);

    string plain_text = get_string("plaintext: \n");
    string cipher_text = cipher(plain_text, key); // cipher plaintext and save as cipher_text
    printf("ciphertext: %s\n", cipher_text);
}

string cipher(string plain_text, int key)
{
    string cipher_text = plain_text;

    // iterate each character in the plaintext
    for (int i = 0; plain_text[i] != '\0'; i++)
    {
        if (isalpha(plain_text[i])) // check if the character is an alphabet
        {
            if (islower(plain_text[i])) // check if each character is lower case
            {
                cipher_text[i] = ((plain_text[i] - 'a' + key) % 26) + 'a'; // cipher as a lowercase character
            }
            else if (isupper(plain_text[i])) // check if each character is lower case
            {
                cipher_text[i] = ((plain_text[i] - 'A' + key) % 26) + 'A'; // cipher as a uppercase character
            }
        }
        else
        {
            cipher_text[i] = plain_text[i]; // leave as plaintest if the character is not an alphabet
        }
    }
    return cipher_text;
}
