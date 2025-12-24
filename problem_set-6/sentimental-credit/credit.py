def main():
    # Continuosly prompt for an input until a valid number is entered
    while True:
        card_no = input("Number: ")
        # Check if the input is a number, if it is break the loop
        if card_no.isdigit():
            break

    # Run the Luhn algorithm to validate the card number
    if luhn(card_no):
        # if valid, determine and print card type
        print(card_type(card_no))
    else:
        print("INVALID")


def luhn(card_no):
    sum = 0
    reverse_digits = card_no[::-1] # Reverse the card number to iterate from right to left

    for index, digit in enumerate(reverse_digits):
        digit = int(digit)
        # Double every odd indexed digit
        if index % 2 == 1:
            digit *= 2
            # If result > 9, substract 9 (same as adding the two digits)
            if digit > 9:
                digit -= 9
        sum += digit
    # return true, if vaild (i.e if sum is a multiple of 10), False if invalid
    return sum % 10 == 0


def card_type(card_no):
    if card_no.startswith(("34", "37")) and len(card_no) == 15:
        return "AMEX"
    elif card_no.startswith(("51", "52", "53", "54", "55")) and len(card_no) == 16:
        return "MASTERCARD"
    elif card_no.startswith(("4")) and len(card_no) in [13, 16]:
        return "VISA"
    else:
        return "INVALID"


# Only run main() if this file is executed directly (not imported)
if __name__ == "__main__":
    main()
