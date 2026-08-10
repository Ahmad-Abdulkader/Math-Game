#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
using namespace std;

//=====================================================================
//                              ENUMS
//=====================================================================

// Used to represent the result of a prime-number check (see CheckPrime).
enum enPrimeNotPrime { Prime = 1, NotPrime = 2 };

// Used to specify which category of character to generate randomly
// (see GetRandomCharacter / GenerateWord).
enum enCharType {
    SmallLetter = 1,
    CapitalLetter = 2,
    SpecialCharacter = 3,
    Digit = 4
};


//=====================================================================
//                          INPUT FUNCTIONS
//=====================================================================

// Reads an integer from the user and keeps asking until a value > 0
// is entered.
// Note: merged with the duplicate "ReadNumber" function, which had
// the exact same body under a different name.
// @param message  Prompt shown to the user.
// @return         The positive integer entered by the user.
int ReadPositiveNumber(string message);

// Reads a single word (no spaces) from the user.
// @param message  Prompt shown to the user.
// @return         The word entered by the user.
string ReadString(string message);

// Reads a full line of text from the user (spaces allowed).
// @return  The text entered by the user.
string ReadText();


//=====================================================================
//                          RANDOM FUNCTIONS
//=====================================================================

// Generates a random integer between two bounds (inclusive).
// @param From  Lower bound.
// @param To    Upper bound.
// @return      A random integer in the range [From, To].
int RandomNumber(int From, int To);

// Generates a single random character of the requested type
// (small letter, capital letter, special character, or digit).
// @param CharType  The category of character to generate.
// @return          A random character of that category.
char GetRandomCharacter(enCharType CharType);

// Generates a random word made of characters of a single type.
// @param CharType  The category of character to use.
// @param Length    The number of characters to generate.
// @return          The generated word.
string GenerateWord(enCharType CharType, short Length);

// Generates a random activation-style key in the form
// XXXX-XXXX-XXXX-XXXX (capital letters only).
// @return  The generated key.
string GenerateKey();

// Generates and prints a given number of random activation keys.
// @param Number  How many keys to generate and print.
void GenerateKeys(short Number);


//=====================================================================
//                          ARRAY FUNCTIONS
//=====================================================================

// Prints all elements of an array on a single line.
// Note: merged the two duplicate versions of this function that only
// differed in the printed label text; kept a single consistent label.
// @param arr        The array to print.
// @param arrLength  Number of elements in the array.
void PrintArray(int arr[], int arrLength);

// Asks the user for the number of elements, then fills the array
// with random integers between 1 and 100.
// @param arr        The array to fill.
// @param arrLength  [out] Set to the number of elements entered by the user.
void FillArrayWithRandomNumbers(int arr[], int& arrLength);

// Fills the array with consecutive integers starting at 1
// (arr[0] = 1, arr[1] = 2, ...).
// Note: this function was originally (incorrectly) named
// "FillArrayWithRandomNumbers" even though it does not generate random
// values at all -- renamed to reflect what it actually does.
// @param arr        The array to fill.
// @param arrLength  Number of elements to fill.
void FillArraySequential(int arr[], int arrLength);

// Fills the array with a fixed, hard-coded set of values
// (10, 20, 30, 30, 20, 10) and sets the length to 6.
// @param arr        The array to fill.
// @param arrLength  [out] Set to 6.
void FillArray(int arr[], int& arrLength);

// Reads array elements one by one from the user.
// @param arr        The array to fill.
// @param arrLength  [out] Set to the number of elements entered by the user.
void ReadArray(int arr[], int& arrLength);

// Appends a single value to the end of the array and updates its length.
// @param Number     Value to append.
// @param arr        The array to modify.
// @param arrLength  [in/out] Current length; incremented by 1.
void AddArrayElement(int Number, int arr[], int& arrLength);

// Repeatedly appends a value to the array while asking the user whether
// to add more.
// Note: fixed a bug where arrLength was passed by value, so the
// updated length was never visible to the caller. It is now passed
// by reference.
// @param arr        The array to modify.
// @param arrLength  [in/out] Updated to reflect how many values were added.
// @param Number     The value to insert on each iteration.
void AddNumberToArray(int arr[], int& arrLength, int Number);

// Repeatedly reads numbers from the user and appends them to the array,
// asking after each entry whether to continue.
// @param arr        The array to fill.
// @param arrLength  [out] Number of elements entered.
void InputUserNumberInArray(int arr[], int& arrLength);

// Swaps the values of two integers.
// @param a  [in/out] First value.
// @param b  [in/out] Second value.
void Swap(int& a, int& b);

// Randomly shuffles the elements of an array in place.
// @param arr        The array to shuffle.
// @param arrLength  Number of elements in the array.
void ShuffleArray(int arr[], int arrLength);

// Copies an array into another array in reverse order.
// @param arrSource       The source array.
// @param arrDestination  The destination array (will hold the reversed copy).
// @param arrLength       Number of elements to copy.
void CopyArrayInReverseOrder(int arrSource[], int arrDestination[], int arrLength);

// Searches for a number inside an array and returns its index.
// @param Number     The value to search for.
// @param arr        The array to search in.
// @param arrLength  Number of elements in the array.
// @return           Index of the first match, or -1 if not found.
short FindNumberPositionInArray(int Number, int arr[], int arrLength);

// Checks whether a number exists inside an array.
// Note: fixed the parameter to take arrLength by value instead of by
// reference, since the function only reads the length and never
// modifies it -- this also makes it consistent with
// FindNumberPositionInArray.
// @param Number     The value to search for.
// @param arr        The array to search in.
// @param arrLength  Number of elements in the array.
// @return           true if the number exists in the array, false otherwise.
bool IsNumberInArray(int Number, int arr[], int arrLength);

// Copies every element of one array into another, using AddArrayElement.
// @param arrSource            The source array.
// @param arrDestination       The destination array.
// @param arrLength            Number of elements in the source array.
// @param arrDestinationLength [in/out] Updated destination length.
void CopyArrayUsingAddArrayElement(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength);

// Copies only the odd numbers from one array into another.
// @param arrSource            The source array.
// @param arrDestination       The destination array.
// @param arrLength            Number of elements in the source array.
// @param arrDestinationLength [in/out] Updated destination length.
void CopyOddNumbersToArray(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength);

// Copies only the prime numbers from one array into another
// (implementation based on AddArrayElement).
// @param arrSource            The source array.
// @param arrDestination       The destination array.
// @param arrLength            Number of elements in the source array.
// @param arrDestinationLength [in/out] Updated destination length.
void CopyPrimeNumbersToArray(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength);

// Alternate/legacy implementation that also copies only the prime
// numbers from one array into another, using a manual counter instead
// of AddArrayElement. Kept alongside CopyPrimeNumbersToArray as a
// second, independent implementation of the same idea.
// @param arrSource            The source array.
// @param arrDestination       The destination array.
// @param arrLength            Number of elements in the source array.
// @param arrDestinationLength [out] Updated destination length.
void CopyArray(int arrSource[], int arrDestination[], int arrLength, int& arrDestinationLength);

// Copies only the distinct (non-duplicate) numbers from one array
// into another.
// @param arrSource            The source array.
// @param arrDestination       The destination array.
// @param SourceLength         Number of elements in the source array.
// @param DestinationLength    [in/out] Updated destination length.
void CopyDistinctNumbersToArray(int arrSource[], int arrDestination[], int SourceLength, int& DestinationLength);

// Checks whether an array reads the same forwards and backwards.
// @param arr        The array to check.
// @param arrLength  Number of elements in the array.
// @return           true if the array is a palindrome, false otherwise.
bool IsPalindromeArray(int arr[], int arrLength);

// Counts how many odd numbers are in the array.
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           The count of odd numbers.
int OddCount(int arr[], int arrLength);

// Counts how many even numbers are in the array.
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           The count of even numbers.
int EvenCount(int arr[], int arrLength);

// Counts how many non-negative numbers are in the array.
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           The count of positive (or zero) numbers.
int PositiveCount(int arr[], int arrLength);

// Counts how many negative numbers are in the array.
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           The count of negative numbers.
int NegativeCount(int arr[], int arrLength);

// Counts how many times a specific value appears in the array.
// @param Number     The value to count.
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           Number of occurrences of Number in the array.
int TimesRepeated(int Number, int arr[], int arrLength);

// Finds the largest value in the array.
// Note: fixed a bug where the running maximum was initialized to 0,
// which produced a wrong result for arrays containing only negative
// numbers. It is now initialized to arr[0].
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           The largest value in the array.
int MaxNumber(int arr[], int arrLength);

// Finds the smallest value in the array.
// @param arr        The array to inspect.
// @param arrLength  Number of elements in the array.
// @return           The smallest value in the array.
int MinNumber(int arr[], int arrLength);

// Computes the sum of all elements in the array.
// @param arr        The array to sum.
// @param arrLength  Number of elements in the array.
// @return           The sum of all elements.
int SumArray(int arr[], int arrLength);

// Computes the average of all elements in the array using an explicit
// running counter (alternate implementation, kept alongside
// AverageArray).
// @param arr        The array to average.
// @param arrLength  Number of elements in the array.
// @return           The average value.
float AverageArrayNumber(int arr[], int arrLength);

// Computes the average of all elements in the array by reusing SumArray.
// @param arr        The array to average.
// @param arrLength  Number of elements in the array.
// @return           The average value.
float AverageArray(int arr[], int arrLength);

// Fills an array of strings with freshly generated activation keys.
// @param arr        The array of strings to fill.
// @param arrLength  Number of elements to generate/fill.
void FillArrayWithKeys(string arr[], int arrLength);


//=====================================================================
//                          MATH FUNCTIONS
//=====================================================================

// Checks whether a number is prime.
// @param number  The number to check.
// @return        Prime if the number is prime, NotPrime otherwise.
enPrimeNotPrime CheckPrime(int number);

// Checks whether a number is a "perfect number" (equal to the sum of
// its proper divisors).
// @param number  The number to check.
// @return        true if the number is perfect, false otherwise.
bool IsPerfectNumber(int number);

// Prints every prime number from 1 up to a given number.
// @param number  The upper bound (inclusive).
void PrintPrimeNumbersFrom1toN(int number);

// Prints every perfect number from 1 up to a given number.
// @param number  The upper bound (inclusive).
void PrintPerfectNumbersFrom1toN(int number);

// Returns the absolute value of a floating-point number.
// @param Number  The number to evaluate.
// @return        The absolute (non-negative) value.
float MyAbs(float Number);

// Returns the fractional part of a floating-point number
// (e.g. 10.3 -> 0.3).
// @param Number  The number to evaluate.
// @return        The fractional part.
float GetFractionPart(float Number);

// Rounds a floating-point number to the nearest integer.
// @param Number  The number to round.
// @return        The rounded integer value.
int MyRound(float Number);


//=====================================================================
//                      STRING & PATTERN FUNCTIONS
//=====================================================================

// Prints the header row (numbers 1 to 10) and separator line used by
// PrintMultiplicationTable.
void PrintHeaderTable();

// Returns the column separator string to use based on the number of
// digits in i (keeps the multiplication table aligned).
// @param i  The row/column index being printed.
// @return   The separator string to print after i.
string ColumnSeparator(int i);

// Prints a full 10x10 multiplication table.
void PrintMultiplicationTable();

// Prints a number with its digits reversed (e.g. 123 -> 321).
// @param number  The number to reverse and print.
void PrintReversedNumber(int number);

// Prints the sum of the digits of a number after reversing it
// (the sum is the same either way; the reversal reflects the
// original algorithm's approach of reading digit by digit).
// @param number  The number whose digit sum will be printed.
void PrintSumReversedNumber(int number);

// Simple equality check between two integers.
// Note: renamed from the misspelled "equl".
// @param number       First value.
// @param shortNumber  Second value.
// @return             true if both values are equal.
bool AreEqual(int number, int shortNumber);

// Prints how many times a specific single digit appears inside a number.
// @param number       The number to scan.
// @param shortNumber  The digit to count.
void PrintFrequencyNumber(int number, int shortNumber);

// Counts how many times a specific digit appears inside a number.
// @param number  The number to scan.
// @param digit   The digit to count (0-9).
// @return        The number of occurrences of digit inside number.
int DigitFrequency(int number, int digit);

// Prints the frequency of every digit (0-9) that appears inside a number.
// @param number  The number to analyze.
void PrintAllDigitsFrequency(int number);

// Prints a descending numeric triangle pattern (from Number down to 1).
// @param Number  The starting (largest) row value.
void PrintInvertedNumberPattern(int Number);

// Prints an ascending numeric triangle pattern (from 1 up to Number).
// @param Number  The largest row value.
void PrintNumberPattern1toN(int Number);

// Prints an ascending letter triangle pattern starting at 'A'.
// @param Number  Number of rows to print.
void PrintLetterPattern(int Number);

// Prints a descending letter triangle pattern.
// @param Number  Number of rows to print.
void PrintInvertedLetterPattern(int Number);

// Prints every possible 3-letter combination from "AAA" to "ZZZ".
void PrintAllFromAAAtoZZZ();

// Overload: tries every possible 3-letter combination from "AAA" to
// "ZZZ" (printing each attempt) until it matches the given string,
// simulating a brute-force password search.
// @param str  The target 3-letter string to search for.
void PrintAllFromAAAtoZZZ(string str);


//=====================================================================
//                        ENCRYPTION FUNCTIONS
//=====================================================================

// Encrypts a string using a simple Caesar-cipher style shift.
// Note: fixed an off-by-one bug in the original loop
// (`i <= text.length()`), which read/wrote one character past the
// end of the string. The loop now correctly stops at `i < text.length()`.
// @param text          The text to encrypt.
// @param encryptionKey The shift value to apply to each character.
// @return              The encrypted text.
string EncryptText(string text, short encryptionKey);

// Decrypts a string that was encrypted with EncryptText, using the
// same key.
// Note: fixed the same off-by-one bug as EncryptText.
// @param text          The text to decrypt.
// @param encryptionKey The shift value used during encryption.
// @return              The decrypted (original) text.
string DecryptText(string text, short encryptionKey);


#endif // FUNCTIONS_H
