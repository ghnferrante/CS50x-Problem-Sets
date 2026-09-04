#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int get_length(long number);
int get_start(int qty_start_numbers, int length, long number);
int verify_luhn(int length, long number);

int main(void)
{
    long card_number = get_long("Number: "); // Prompt user for Card Number

    int length = get_length(card_number); // Get number length between 13-16 (if not, print
                                          // INVALID and stop)

    int luhn = verify_luhn(length, card_number); // Verify checksum according to Luhn's algorithm
                                                 // (if incorrect, print INVALID and stop)

    int start_numbers = get_start(2, length, card_number); // Get the 2 first numbers's digits

    // Check validity for each Credit Card Brand (if none, print INVALID)
    if (length == 15 && (start_numbers == 34 || start_numbers == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (start_numbers >= 51 && start_numbers <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (start_numbers >= 40 && start_numbers <= 49))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Get number length between 13-16 (if not, print INVALID and stop)
int get_length(long number)
{
    int n;

    for (int i = 13; i <= 16; i++)
    {
        n = number / pow(10, i - 1);
        if (n >= 1 && n <= 9)
        {
            return i;
        }
    }

    printf("INVALID\n");

    exit(0);
}

// Get the 2 first numbers's digits
int get_start(int qty_start_numbers, int length, long number)
{
    int n = number / pow(10, length - qty_start_numbers);

    return n;
}

// Verify checksum according to Luhn's algorithm (if incorrect, print INVALID and stop)
int verify_luhn(int length, long number)
{

    int n = 0;

    for (int i = 1; i <= length; i++)
    {
        if (i % 2 == 0) // even length
        {
            int p = 2 * (number % 10);

            if (p >= 10)
            {
                p = (p / 10) + (p % 10);
            }

            n = n + p;
        }

        if ((i % 2) != 0) // odd length
        {
            n = (number % 10) + n;
        }

        number /= 10; // extract last digit for restarting loop
    }

    if (n % 10 == 0)
    {
        return 1;
    }
    else
    {
        printf("INVALID\n");

        exit(0);
    }
}
