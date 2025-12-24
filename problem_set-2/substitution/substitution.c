// Include libaries
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function prototype
string cipher(string plaintext, string key);

int main(int argc, char **argv)
{
    string key = argv[1]; // set key as first argument

    if (argc != 2) // check for only 1 argument
    {
        printf("./substition key\n");
        return 1;
    }

    if (strlen(key) != 26) // check if key is 26 characters
    {
        printf("Key should have 26 letters.\n");
        return 1;
    }

    int seen[26] = {false}; // set seen as false for all letters

    // iterate through each 26 letters
    for (int i = 0; i < 26; i++)
    {
        char c = key[i];

        // print error message if the character is not a letter
        if (!isalpha(c))
        {
            printf("Key should be alphabetic.\n");
            return 1;
        }

        // map each character with an index
        int index = toupper(c) - 'A';

        // print error message if the character has been seen
        if (seen[index] == true)
        {
            printf("The key should not have duplicate letters.\n");
            return 1;
        }
        // set seen character as true
        else
        {
            seen[index] = true;
        }
    }

    string plaintext = get_string("plaintext: \n"); // get plaintext
    string ciphertext = cipher(plaintext, key);     // cipher plaintext with key

    printf("ciphertext: %s\n", ciphertext); // print the ciphered text
}

// cipher function
string cipher(string plaintext, string key)
{
    string ciphertext = plaintext;

    // iterate through the plaintext until the end of the text
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        // cipher each alphabet
        if (isalpha(plaintext[i]))
        {
            char c = plaintext[i];
            int index = toupper(c) - 'A';

            // set ciphered text to lowercase key
            if (islower(c))
            {
                ciphertext[i] = tolower(key[index]);
            }
            // set cciphered texxt to uppercase key
            else
            {
                ciphertext[i] = toupper(key[index]);
            }
        }
    }
    return ciphertext;
}
