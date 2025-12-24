def main():
    # Prompt user for a text to check readability
    text = input("Text: ")

    # Count the number of letters, words and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculate the average letters and sentences per 100 words
    L = (letters / words) * 100
    S = (sentences / words) * 100

    # Calculate the index using Coleman-Liau index formula
    index = (0.0588 * L) - (0.296 * S) - (15.8)

    # Print grade level based on index
    print_grade(index)


# Count the number of letters in text
def count_letters(text):
    count = 0  # Set count as 0

    # Iterate through each character
    for char in text:
        # Count each alphabetic character
        if char.isalpha():
            count += 1

    return count


def count_words(text):
    count = 0  # Set count as 0
    in_word = False  # Set in_word as False in the beginning of the text

    # Iterate through each character
    for char in text:
        if not char.isspace():
            if not in_word:
                # If a letter starts a new word increase count by 1 and set in_word as True
                count += 1
                in_word = True
        # if it is a space then set in_word as False
        else:
            in_word = False

    return count


# Count the number of sentences in text
def count_sentences(text):
    count = 0  # Set count as 0

    for char in text:
        # If a letter ends with a sentence ending punctuation then it ends a sentence increase count by 1
        if char in ('.', '?', '!'):
            count += 1

    return count


def print_grade(index):  # Print the grade level based on index
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade", round(index))


if __name__ == "__main__":
    main()
