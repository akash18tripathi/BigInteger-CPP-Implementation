# BigInteger-CPP-Implementation

# BigInteger Library for C++

This repository contains a BigInteger library implemented in C++, which provides support for various arithmetic operations and functions for working with large integers.

## Features

The BigInteger library supports the following operations:

1. Addition, Subtraction & Multiplication
2. Exponentiation
3. GCD
4. Factorial

## Input Format

The input format for each type of operation is as follows:

1. Addition, Subtraction & Multiplication:
   - First line: `1`
   - Second line: A single string representing the mathematical expression.

   Example:

```shell
1
32789123+99893271223x9203232392-4874223
```

2. Exponentiation:
- First line: `2`
- Second line: Two space-separated strings representing the base and exponent, respectively.

Example:
```shell
2
32789123 2
```


3. GCD:
- First line: `3`
- Second line: Two space-separated strings representing the numbers for which GCD is to be calculated.

Example:

```shell
3
32789123 99893271223
```


4. Factorial:
- First line: `4`
- Second line: A single string representing the number for which factorial is to be calculated.

Example:
```shell
4
32789123
```
## Limitations

The library assumes that the number of digits in the output won't exceed 3000 digits. Negative numbers are not present in the intermediate or final output, so there's no need to handle cases like subtraction resulting in negative values.

## Contributions

Contributions to the BigInteger library are welcome! If you encounter any issues or have suggestions for improvements, please open an issue or submit a pull request.
