#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate through each candidate to find a name match
    for (int i = 0; i < candidate_count; i++)
    {
        // If name matches update the voter preference array
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    // Return false if no candidate name matches
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate through each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate through each preference for the voter
        for (int j = 0; j < candidate_count; j++)
        {
            // Find the highest ranked candidate who has not been eliminated
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++; // Increment the candidate vote count
                break;                                 // Stop searching preference for this voter
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate the number of votes needed for a majority (> 50%)
    int win_vote = voter_count / 2;

    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if a candidate has a majority of votes
        if (candidates[i].votes > win_vote)
        {
            printf("%s\n", candidates[i].name); // Print the winner namme and return true
            return true;
        }
    }

    // return false if no candidate has the mahjority of votes
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialise min_vote with a value greater than any voter count
    int min_vote = voter_count;

    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check only candidates who have not been eliminated
        if (!candidates[i].eliminated && candidates[i].votes < min_vote)
        {
            min_vote = candidates[i].votes;
        }
    }

    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If any non-eliminated candidate does not have the minimum value
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }

    // If all non-eliminated candidates has the minimum value return true
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Eliminate each non-eliminated candidate with the minimum score
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
