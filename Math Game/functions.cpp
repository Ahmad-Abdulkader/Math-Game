#include "functions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

//=====================================================================
//                          INPUT FUNCTIONS
//=====================================================================

// Prompts the user with the given message and reads an integer,
// repeating the prompt until a value greater than zero is entered.
int ReadPositiveNumber(string message) {
    int number;

    // Loop until the entered value passes the positive check.
    do {
        cout << message << endl;
        cin >> number;
    } while (number <= 0);

    return number;
}

// Prompts the user with the given message and reads a single token
// (cin >> stops at the first whitespace character, so this cannot
// contain spaces).
string ReadString(string message) {
    string str;

    cout << message << endl;
    cin >> str;

    return str;
}

// Prompts the user for a full line of free-form text.
// getline() is used instead of cin >> so spaces are preserved.
string ReadText() {
    string Text;

    cout << "Please enter text\n";
    getline(cin, Text);

    return Text;
}


//=====================================================================
//                          RANDOM FUNCTIONS
//=====================================================================

// Generates a random integer in the closed interval [From, To].
// The remainder of rand() modulo the interval width maps the raw
// random value into a 0-based range, which is then shifted by "From".
int RandomNumber(int From, int To) {
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

// Generates one random character belonging to the requested category.
// Each enum case maps to the ASCII range that represents that category:
//   SmallLetter      -> 'a' to 'z'   (97  - 122)
//   CapitalLetter    -> 'A' to 'Z'   (65  - 90)
//   SpecialCharacter -> '!' to '/'   (33  - 47)
//   Digit            -> '0' to '9'   (48  - 57)
char GetRandomCharacter(enCharType CharType) {
    switch (CharType) {
    case enCharType::SmallLetter:
    {
        return char(RandomNumber(97, 122));
        break;
    }
    case enCharType::CapitalLetter:
    {
        return char(RandomNumber(65, 90));
        break;
    }
    case enCharType::SpecialCharacter:
    {
        return char(RandomNumber(33, 47));
        break;
    }
    case enCharType::Digit:
    {
        return char(RandomNumber(48, 57));
        break;
    }
    }

    // Fallback in case an unexpected enum value is passed in.
    return '\n';
}

// Builds a word of the requested length by generating one random
// character of the requested type per position and appending it.
string GenerateWord(enCharType CharType, short Length) {
    string Word;

    for (int i = 1; i <= Length; i++) {
        Word = Word + GetRandomCharacter(CharType);
    }

    return Word;
}

// Builds a license/activation-style key made of four blocks of four
// random capital letters, separated by dashes:
// e.g. "ABCD-EFGH-IJKL-MNOP".
string GenerateKey() {
    string Key = "";

    Key = GenerateWord(enCharType::CapitalLetter, 4) + "-";
    Key = Key + GenerateWord(enCharType::CapitalLetter, 4) + "-";
    Key = Key + GenerateWord(enCharType::CapitalLetter, 4) + "-";
    Key = Key + GenerateWord(enCharType::CapitalLetter, 4);

    return Key;
}

// Generates and prints "Number" activation keys, one per line,
// each labeled with its position in the sequence.
void GenerateKeys(short Number) {
    for (int i = 1; i <= Number; i++) {
        cout << "Key [" << i << "]:";
        cout << GenerateKey() << endl;
    }
}


//=====================================================================
//                          ARRAY FUNCTIONS
//=====================================================================

// Prints every element of the array on a single line, separated by spaces.
void PrintArray(int arr[], int arrLength) {
    cout << "Array Elements: ";

    for (int i = 0; i < arrLength; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

// Asks the user how many elements to generate, then fills the array
// with that many random integers in the range [1, 100].
// arrLength is passed by reference so the caller receives the count
// that was actually entered.
void FillArrayWithRandomNumbers(int arr[], int& arrLength) {
    cout << "Enter number of elements:" << endl;
    cin >> arrLength;

    for (int i = 0; i < arrLength; i++) {
        arr[i] = RandomNumber(1, 100);
    }

    cout << endl;
}

// Fills the array with consecutive integers starting at 1:
// arr[0] = 1, arr[1] = 2, arr[2] = 3, and so on up to arrLength.
void FillArraySequential(int arr[], int arrLength) {
    for (int i = 0; i < arrLength; i++) {
        arr[i] = i + 1;
    }

    cout << endl;
}

// Loads a fixed, hard-coded set of six demo values into the array
// and sets the length accordingly. Useful for quick manual testing
// of other array functions without prompting for input.
void FillArray(int arr[], int& arrLength) {
    arrLength = 6;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 30;
    arr[4] = 20;
    arr[5] = 10;
}

// Prompts the user for the number of elements, then reads each
// element individually, showing its position number in the prompt.
void ReadArray(int arr[], int& arrLength) {
    cout << "Enter number of elements:" << endl;
    cin >> arrLength;

    for (int i = 0; i < arrLength; i++) {
        cout << "Element[" << i + 1 << "]: ";
        cin >> arr[i];
    }

    cout << endl;
}

// Appends a single value to the first free slot of the array
// (index arrLength) and increases arrLength by one to reflect the
// new size. This is the building block used by several of the
// "copy" functions below.
void AddArrayElement(int Number, int arr[], int& arrLength) {
    arrLength++;
    arr[arrLength - 1] = Number;
}

// Repeatedly stores "Number" into the array and asks the user after
// each insertion whether to add another copy. The loop continues as
// long as the user answers with a non-zero value.
void AddNumberToArray(int arr[], int& arrLength, int Number) {
    int i = 0, counter = 0, Num = 1;

    while (Num != 0) {
        arr[i++] = Number;

        cout << "Do you want to add more number?[0]NO [1]yes " << endl;
        cin >> Num;

        counter++;
        arrLength = counter;
    }
}

// Repeatedly reads a positive number from the user and appends it to
// the array via AddArrayElement, asking after each entry whether to
// continue. Stops as soon as the user answers "no" (0).
void InputUserNumberInArray(int arr[], int& arrLength) {
    bool AddMore = true;

    do {
        AddArrayElement(ReadPositiveNumber("Enter number"), arr, arrLength);

        cout << "\nDo you want to add more numbers? [0]:No,[1]:yes? ";
        cin >> AddMore;
    } while (AddMore);
}

// Exchanges the values held by the two referenced integers using a
// temporary variable.
void Swap(int& a, int& b) {
    int Temp;
    Temp = a;
    a = b;
    b = Temp;
}

// Randomizes the order of the array's elements by repeatedly swapping
// two randomly chosen positions. The number of swap operations equals
// the array length, which is sufficient to thoroughly mix the values.
void ShuffleArray(int arr[], int arrLength) {
    for (int i = 0; i < arrLength; i++) {
        Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
    }
}

// Copies the source array into the destination array with the
// element order reversed, so the last source element becomes the
// first destination element and vice versa.
void CopyArrayInReverseOrder(int arrSource[], int arrDestination[], int arrLength) {
    for (int i = 0; i < arrLength; i++) {
        arrDestination[i] = arrSource[arrLength - 1 - i];
    }
}

// Scans the array from the beginning and returns the index of the
// first element equal to "Number". Returns -1 if no match is found.
short FindNumberPositionInArray(int Number, int arr[], int arrLength) {
    // Loop through each element in the array.
    for (int i = 0; i < arrLength; i++) {
        // Check if the current element equals the searched number.
        if (arr[i] == Number)
            return i; // Return the index immediately when the number is found.
    }

    // If the loop completes without finding the number, return -1.
    return -1;
}

// Convenience wrapper around FindNumberPositionInArray that returns
// a plain true/false result instead of a position.
bool IsNumberInArray(int Number, int arr[], int arrLength) {
    // Use FindNumberPositionInArray and check if the result is not -1.
    return FindNumberPositionInArray(Number, arr, arrLength) != -1;
}

// Copies every element from the source array into the destination
// array, appending one element at a time through AddArrayElement so
// arrDestinationLength stays accurate throughout the process.
void CopyArrayUsingAddArrayElement(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength) {
    // Loop through each element of the source array.
    for (int i = 0; i < arrLength; i++)
        // Use AddArrayElement to copy the element to the destination array and update its length.
        AddArrayElement(arrSource[i], arrDestination, arrDestinationLength);
}

// Copies only the odd-valued elements from the source array into the
// destination array.
void CopyOddNumbersToArray(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength) {
    // Loop through each element of the source array.
    for (int i = 0; i < arrLength; i++) {
        if (arrSource[i] % 2 != 0) {
            // Use AddArrayElement to copy the element to the destination array and update its length.
            AddArrayElement(arrSource[i], arrDestination, arrDestinationLength);
        }
    }
}

// Copies only the prime-valued elements from the source array into
// the destination array, using CheckPrime to test each element and
// AddArrayElement to perform the copy.
void CopyPrimeNumbersToArray(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength) {
    // Loop through each element of the source array.
    for (int i = 0; i < arrLength; i++) {
        if (CheckPrime(arrSource[i]) == enPrimeNotPrime::Prime) {
            // Use AddArrayElement to copy the element to the destination array and update its length.
            AddArrayElement(arrSource[i], arrDestination, arrDestinationLength);
        }
    }
}

// Alternate implementation of a prime-number copy: instead of relying
// on AddArrayElement, it tracks the destination index with its own
// local counter and writes directly into arrDestination.
void CopyArray(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength) {
    int counter = 0;

    for (int i = 0; i < arrLength; i++) {
        if (CheckPrime(arrSource[i]) == enPrimeNotPrime::Prime) {
            arrDestination[counter] = arrSource[i];
            counter++;
        }
    }

    arrDestinationLength = counter;
}

// Copies only the distinct (non-duplicate) values from the source
// array into the destination array, skipping any value that has
// already been placed in the destination.
void CopyDistinctNumbersToArray(int arrSource[], int arrDestination[], int SourceLength, int& DestinationLength) {
    // Loop through each element in the source array.
    for (int i = 0; i < SourceLength; i++) {
        // If the current element is not already in the destination array...
        if (!IsNumberInArray(arrSource[i], arrDestination, DestinationLength)) {
            // ...then add it to the destination array.
            AddArrayElement(arrSource[i], arrDestination, DestinationLength);
        }
    }
}

// Checks whether the array reads the same from front to back as it
// does from back to front (a palindrome), by comparing mirrored
// pairs of elements.
bool IsPalindromeArray(int arr[], int arrLength) {
    // Loop through each element of the array.
    // We only need to check up to the middle of the array.
    for (int i = 0; i < arrLength; i++) {
        // Compare the element at position i with its corresponding element from the end.
        if (arr[i] != arr[arrLength - i - 1]) {
            return false;  // If any pair doesn't match, the array is not a palindrome.
        }
    }

    // If all corresponding pairs match, the array is a palindrome.
    return true;
}

// Counts how many elements in the array are odd.
int OddCount(int arr[], int arrLength) {
    int Counter = 0;  // Initialize the odd number counter to 0.

    // Loop through each element in the array.
    for (int i = 0; i < arrLength; i++) {
        // Check if the element is odd (i.e., its remainder when divided by 2 is not 0).
        if (arr[i] % 2 != 0) {
            Counter++;  // Increment the counter if the element is odd.
        }
    }

    return Counter;  // Return the total count of odd numbers.
}

// Counts how many elements in the array are even.
int EvenCount(int arr[], int arrLength) {
    int Counter = 0;  // Initialize counter for even numbers to 0.

    // Loop through each element of the array.
    for (int i = 0; i < arrLength; i++) {
        // Check if the current element is even.
        if (arr[i] % 2 == 0) {
            Counter++;  // Increment the counter if the element is even.
        }
    }

    return Counter;  // Return the total count of even numbers.
}

// Counts how many elements in the array are zero or positive.
int PositiveCount(int arr[], int arrLength) {
    int Counter = 0;  // Initialize a counter for positive numbers.

    // Loop through each element of the array.
    for (int i = 0; i < arrLength; i++) {
        // Check if the current element is positive (or zero).
        if (arr[i] >= 0) {
            Counter++;  // Increment the counter if the condition is met.
        }
    }

    return Counter;  // Return the total count of positive numbers.
}

// Counts how many elements in the array are strictly negative.
int NegativeCount(int arr[], int arrLength) {
    int Counter = 0;  // Initialize a counter for negative numbers.

    // Loop through each element of the array.
    for (int i = 0; i < arrLength; i++) {
        // Check if the current element is negative.
        if (arr[i] < 0) {
            Counter++;  // Increment the counter if the condition is met.
        }
    }

    return Counter;  // Return the total count of negative numbers.
}

// Counts how many times the value "Number" appears in the array.
int TimesRepeated(int Number, int arr[], int arrLength) {
    int counter = 0;

    for (int i = 0; i < arrLength; i++) {
        if (Number == arr[i]) {
            counter++;
        }
    }

    return counter;
}

// Scans the array and returns the largest value found.
// The running maximum starts at arr[0] so the function still returns
// a correct result for arrays made up entirely of negative numbers.
int MaxNumber(int arr[], int arrLength) {
    int Max = arr[0];

    for (int i = 0; i < arrLength; i++) {
        if (arr[i] > Max) {
            Max = arr[i];
        }
    }

    return Max;
}

// Scans the array and returns the smallest value found, starting the
// comparison from arr[0].
int MinNumber(int arr[], int arrLength) {
    int Min = arr[0];

    for (int i = 0; i < arrLength; i++) {
        if (arr[i] < Min) {
            Min = arr[i];
        }
    }

    return Min;
}

// Adds up every element in the array and returns the total.
int SumArray(int arr[], int arrLength) {
    int Sum = 0;

    for (int i = 0; i < arrLength; i++) {
        Sum += arr[i];
    }

    return Sum;
}

// Computes the arithmetic mean of the array's elements, accumulating
// the sum and the element count in the same loop before dividing.
float AverageArrayNumber(int arr[], int arrLength) {
    int counter = 0, Sum = 0;

    for (int i = 0; i < arrLength; i++) {
        Sum += arr[i];
        counter++;
    }

    return (float)Sum / counter;
}

// Computes the arithmetic mean of the array's elements by reusing
// SumArray for the total and dividing by the element count directly.
float AverageArray(int arr[], int arrLength) {
    return (float)SumArray(arr, arrLength) / arrLength;
}

// Fills an array of strings with freshly generated activation keys,
// one call to GenerateKey() per element.
void FillArrayWithKeys(string arr[], int arrLength) {
    for (int i = 0; i < arrLength; i++) {
        arr[i] = GenerateKey();
    }
}


//=====================================================================
//                          MATH FUNCTIONS
//=====================================================================

// Determines whether "number" is prime by trial division: it checks
// every candidate divisor from 2 up to half of the number, and
// returns NotPrime as soon as an exact divisor is found.
enPrimeNotPrime CheckPrime(int number) {
    int m = number / 2;

    for (int counter = 2; counter <= m; counter++) {
        if (number % counter == 0)
            return enPrimeNotPrime::NotPrime;
    }

    return enPrimeNotPrime::Prime;
}

// Determines whether "number" is a perfect number, meaning it equals
// the sum of its proper divisors (divisors excluding the number
// itself).
bool IsPerfectNumber(int number) {
    int sum = 0;

    for (int i = 1; i < number; i++) {
        if (number % i == 0) {
            sum += i;
        }
    }

    return sum == number;
}

// Prints every prime number found between 1 and "number" (inclusive),
// one per line, using CheckPrime to test each candidate.
void PrintPrimeNumbersFrom1toN(int number) {
    cout << "\nPrime numbers from 1 to " << number << " are:" << endl;

    for (int i = 1; i <= number; i++) {
        if (CheckPrime(i) == enPrimeNotPrime::Prime)
            cout << i << endl;
    }
}

// Prints every perfect number found between 1 and "number" (inclusive),
// one per line, using IsPerfectNumber to test each candidate.
void PrintPerfectNumbersFrom1toN(int number) {
    cout << "\nPerfect numbers from 1 to " << number << " are:" << endl;

    for (int i = 1; i <= number; i++) {
        if (IsPerfectNumber(i))
            cout << i << endl;
    }
}

// Returns the absolute value of a floating-point number: the number
// itself if it is positive, or its negation otherwise.
float MyAbs(float Number) {
    // If the number is positive or zero, return it as is.
    if (Number > 0)
        return Number;
    else
        return Number * -1;  // If negative, multiply by -1 to make it positive.
}

// Returns only the fractional part of a floating-point number by
// subtracting its truncated integer part from the original value
// (e.g. 10.3 -> 0.3).
float GetFractionPart(float Number) {
    // Subtract the integer part of the number from the original number to get the fractional part.
    return Number - int(Number);
}

// Rounds a floating-point number to the nearest whole integer.
// The integer part is extracted first, then the fractional part
// (obtained via GetFractionPart) decides whether to round up or down:
// a fractional part of 0.5 or more rounds away from zero.
int MyRound(float Number) {
    int IntPart;  // Variable to store the integer part of the number.
    IntPart = int(Number);  // Extract the integer part.

    // Compute the fractional part using the GetFractionPart function.
    float FractionsPart = GetFractionPart(Number);

    // If the absolute value of the fractional part is 0.5 or more, round the number accordingly.
    if (MyAbs(FractionsPart) >= 0.5) {
        // If the number is positive, round up.
        if (Number > 0)
            return ++IntPart;
        // If the number is negative, round down.
        else
            return --IntPart;
    }
    else {
        // If the fractional part is less than 0.5, keep the integer part as is.
        return IntPart;
    }
}


//=====================================================================
//                      STRING & PATTERN FUNCTIONS
//=====================================================================

// Prints the title line, the column headers (1 through 10), and the
// separator line that make up the top of the multiplication table.
void PrintHeaderTable() {
    cout << endl;
    cout << "\t\t\t\tMultiplication Table From 1 to 10" << endl << endl;

    for (int i = 1; i <= 10; i++) {
        cout << "\t" << i;
    }

    cout << endl;
    cout << "_____________________________________________________________________________________" << endl;
}

// Returns the padding string to print after a row/column index so
// the multiplication table's columns stay visually aligned, since
// single-digit and two-digit numbers take up different amounts of
// horizontal space.
string ColumnSeparator(int i) {
    if (i < 10)
        return "   |";
    else
        return "  |";
}

// Prints a complete 10x10 multiplication table: the header row
// followed by one row per multiplicand (1 through 10), each showing
// the product with every multiplier from 1 to 10.
void PrintMultiplicationTable() {
    PrintHeaderTable();

    for (int i = 1; i <= 10; i++) {
        cout << "" << i << ColumnSeparator(i) << " \t";

        for (int j = 1; j <= 10; j++) {
            cout << j * i << "\t";
        }

        cout << endl;
    }
}

// Extracts the digits of "number" from right to left and rebuilds
// them in reverse order, then prints the resulting reversed number
// (e.g. 123 becomes 321).
void PrintReversedNumber(int number) {
    int remainder = 0, number2 = 0;

    while (number > 0) {
        remainder = number % 10;
        number /= 10;
        number2 = number2 * 10 + remainder;
    }

    cout << number2;
}

// Extracts each digit of "number" one at a time and prints the total
// of all the digits (the sum is independent of digit order, so no
// reversed number needs to be built here).
void PrintSumReversedNumber(int number) {
    int remainder = 0, sum = 0;

    while (number > 0) {
        remainder = number % 10;
        sum += remainder;
        number /= 10;
    }

    cout << sum;
}

// Compares two integers for equality.
bool AreEqual(int number, int shortNumber) {
    return number == shortNumber;
}

// Scans every digit of "number" and prints how many of them equal
// "shortNumber".
void PrintFrequencyNumber(int number, int shortNumber) {
    int remainder = 0, counter = 0;

    while (number > 0) {
        remainder = number % 10;

        if (AreEqual(remainder, shortNumber)) {
            counter++;
        }

        number /= 10;
    }

    cout << shortNumber << " Frequency is" << counter << endl;
}

// Scans every digit of "number" and returns how many of them equal
// "digit".
int DigitFrequency(int number, int digit) {
    int remainder = 0, counter = 0;

    while (number > 0) {
        remainder = number % 10;
        number /= 10;

        if (remainder == digit) {
            counter++;
        }
    }

    return counter;
}

// Checks each possible digit value (0 through 9) against "number" via
// DigitFrequency, and prints a line for every digit that appears at
// least once, along with how many times it appears.
void PrintAllDigitsFrequency(int number) {
    short frequency = 0;

    for (int i = 0; i < 10; i++) {
        frequency = DigitFrequency(number, i);

        if (frequency > 0) {
            cout << "Digit " << i << " Frequency is "  // Print the digit and its frequency.
                << frequency << " Time(s).\n";
        }
    }
}

// Prints a triangle of numbers that shrinks from "Number" down to 1:
// each row repeats its own row number that many times.
void PrintInvertedNumberPattern(int Number) {
    for (int i = Number; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << i;
        }
        cout << endl;
    }
}

// Prints a triangle of numbers that grows from 1 up to "Number":
// each row repeats its own row number that many times.
void PrintNumberPattern1toN(int Number) {
    for (int i = 1; i <= Number; i++) {
        for (int j = 1; j <= i; j++) {
            cout << i;
        }
        cout << endl;
    }
}

// Prints a triangle of letters starting at 'A' and growing downward
// for "Number" rows, with each row repeating its own letter one more
// time than the row above it.
void PrintLetterPattern(int Number) {
    for (int i = 65; i <= 65 + Number - 1; i++) {
        for (int j = 1; j <= Number - ((65 + Number - 1) - i); j++) {
            cout << char(i);
        }
        cout << endl;
    }
}

// Prints the same letter triangle as PrintLetterPattern, but built
// from the bottom letter upward, so the rows shrink as they go down.
void PrintInvertedLetterPattern(int Number) {
    for (int i = Number + 65 - 1; i >= 65; i--) {
        for (int j = 1; j <= Number - ((65 + Number - 1) - i); j++) {
            cout << char(i);
        }
        cout << endl;
    }
}

// Generates and prints every possible combination of three uppercase
// letters, from "AAA" through "ZZZ", using three nested loops (one
// per letter position). A separator line is printed after each
// completed first-letter group.
void PrintAllFromAAAtoZZZ() {
    cout << "\n";  // Print an empty line for formatting.
    string word = "";  // Initialize an empty string to build each three-letter combination.

    // Outer loop: Iterates over ASCII values for uppercase letters (65 'A' to 90 'Z') for the first letter.
    for (int i = 65; i <= 90; i++) {
        // Middle loop: Iterates over ASCII values for uppercase letters for the second letter.
        for (int j = 65; j <= 90; j++) {
            // Inner loop: Iterates over ASCII values for uppercase letters for the third letter.
            for (int k = 65; k <= 90; k++) {
                // Append the current letter for the first position.
                word.append(1, char(i));
                // Append the current letter for the second position.
                word.append(1, char(j));
                // Append the current letter for the third position.
                word.append(1, char(k));

                // Output the constructed three-letter word.
                cout << word << endl;
                // Reset the word string to empty for the next combination.
                word = "";
            }
        }
        // After completing combinations for the current first letter, print a separator line.
        cout << "\n____________________________\n";
    }
}

// Overload of PrintAllFromAAAtoZZZ that performs the same three-letter
// brute-force generation, printing every attempt along the way, but
// stops and reports success as soon as the generated combination
// matches the target string "str".
void PrintAllFromAAAtoZZZ(string str) {
    cout << "\n";  // Print an empty line for formatting.
    string word = "";  // Initialize an empty string to build each three-letter combination.
    int counter = 0;

    // Outer loop: Iterates over ASCII values for uppercase letters (65 'A' to 90 'Z') for the first letter.
    for (int i = 65; i <= 90; i++) {
        // Middle loop: Iterates over ASCII values for uppercase letters for the second letter.
        for (int j = 65; j <= 90; j++) {
            // Inner loop: Iterates over ASCII values for uppercase letters for the third letter.
            for (int k = 65; k <= 90; k++) {
                word = "";

                counter++;
                // Append the current letter for the first position.
                word.append(1, char(i));
                // Append the current letter for the second position.
                word.append(1, char(j));
                // Append the current letter for the third position.
                word.append(1, char(k));
                cout << "Trial" << "[" << counter << "] :" << word << endl;

                // If the generated word matches the target, report success and stop.
                if (str == word) {
                    cout << "password is" << str << endl;
                    cout << "Found after" << counter << "Trail(s)" << endl;

                    return;
                }
            }
        }
    }
}


//=====================================================================
//                        ENCRYPTION FUNCTIONS
//=====================================================================

// Encrypts "text" using a simple Caesar-cipher style shift: every
// character's ASCII code is increased by "encryptionKey", producing
// a scrambled version of the string that can be reversed with
// DecryptText and the same key.
string EncryptText(string text, short encryptionKey) {
    for (size_t i = 0; i < text.length(); i++) {
        text[i] = char((int)text[i] + encryptionKey);
    }

    return text;
}

// Reverses the effect of EncryptText by shifting every character's
// ASCII code back down by "encryptionKey", restoring the original text.
string DecryptText(string text, short encryptionKey) {
    for (size_t i = 0; i < text.length(); i++) {
        text[i] = char((int)text[i] - encryptionKey);
    }

    return text;
}
