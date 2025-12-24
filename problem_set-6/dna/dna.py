import csv
import sys

def longest_match(sequence, subsequence):
    longest = 0
    length = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0
        while True:
            start = i + count * length
            end = start + length
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest = max(longest, count)

    return longest


def main():

    # Make sure user runs program correctly
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read the database CSV
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        database = list(reader)

    # Read the DNA sequence
    with open(sys.argv[2]) as file:
        sequence = file.read()

    # Extract the STRs from CSV header
    strs = reader.fieldnames[1:]   # skip the 'name' column

    # Compute STR counts for the sequence
    results = {}
    for s in strs:
        results[s] = longest_match(sequence, s)

    # Compare with each person in the database
    for person in database:
        match = True
        for s in strs:
            if int(person[s]) != results[s]:
                match = False
                break
        if match:
            print(person['name'])
            return

    print("No match")


if __name__ == "__main__":
    main()
