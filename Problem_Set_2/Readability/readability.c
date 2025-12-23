#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void print_grade(float index);

int main(void)
{
    // Prompt user for a text to check readability
    string text = get_string("Text: ");

    // Count the number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate the average of letters and sentences per 100 words
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // Coleman-Liau index formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the grade level based on the index
    print_grade(index);
}

// Count the number of letters in the text
int count_letters(string text)
{
    int count = 0;

    // Loop through each character
    for (int i = 0; text[i] != '\0'; i++)
    {
        // Count each alphabetic character
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Count the number of words in the texxt
int count_words(string text)
{
    int count = 0; // Set count as 0
    bool in_word = false; // Set in word as false in the beginning of the text

    // Loop through each character
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace(text[i]))
        {
            // If a letter starts a new word increase count by 1
            if (!in_word)
            {
                count++;
                in_word = true;
            }
        }
        // If it is a non letter then it is not in a word
        else
        {
            // Non-letter means end of a word
            in_word = false;
        }
    }
    return count;
}

// Count the number of sentences in a text
int count_sentences(string text)
{
    int count = 0;

    // Loop through every character
    for (int i = 0; text[i] != '\0'; i++)
    {
        // If a letter ends with a sentence ending punctuation then it ends a sentence increase count by 1
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

// Print the grade level based on index
void print_grade(float index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}
