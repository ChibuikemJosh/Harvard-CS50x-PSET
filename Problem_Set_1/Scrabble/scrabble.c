#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
int calc_score(string word);
string calc_winner(int score1, int score2);

// Points assigned to each letter
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Get words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = calc_score(word1);
    int score2 = calc_score(word2);

    // Determine and print the winner
    string result = calc_winner(score1, score2);
    printf("%s", result);

    return 0;
}

// Calculates the score of a word
int calc_score(string word)
{
    int total = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            int index = toupper(word[i]) - 'A';
            total += points[index];
        }
    }
    return total;
}

// Determines the winner based on scores
string calc_winner(int score1, int score2)
{
    // Determine winner
    if (score1 > score2)
    {
        return "Player 1 wins!\n";
    }
    else if (score2 > score1)
    {
        return "Player 2 wins!\n";
    }
    else
    {
        return "Tie!\n";
    }
}
