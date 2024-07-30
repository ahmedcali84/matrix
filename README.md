# Matrix Operations

This repository contains a collection of matrix operations implemented in C. The project demonstrates fundamental matrix operations such as addition, subtraction, multiplication, and transposition.

## Table of Contents

- [Matrix Operations](#matrix-operations)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Files](#files)
  - [Contributing](#contributing)
  - [License](#license)
  - [Contact](#contact)

## Installation

To compile and run the matrix operations program, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/ahmedcali84/matrix.git
    cd matrix
    ```

## Usage

The program performs various matrix operations. You can specify the maximum value for matrix elements using a command-line argument. Here is how you use the program:

1. **Compile the Program**:
    ```bash
    make
    ```

2. **Run the Program with Command-Line Arguments**:
    ```bash
    ./main <max_value> <nrows> <ncols> <nrows1> <nrows2>
    ```

   - `<max value>`: This argument specifies the maximum value that each matrix element can take. For example, if you run `./main 10 4 4 `, the program will generate matrices with values ranging from 0 to 9 with 4 columns and 4 rows.
   - `<nrows>`: No. of matrix Rows for the First Matrix.
   - `<ncols>`: No. of matrix Columns for the First Matrix.
   - `<nrows1>`: No. of matrix Rows for the Second Matrix.
   - `<ncols1>`: No. of matrix Columns for the Second Matrix.

3. **Example Usage**:
    ```bash
    ./main 10 4 4 4 4
    ```

   This will generate matrices with random values between 0 and 9, with 4 rows and columns , perform matrix operations (addition, subtraction, multiplication and transposition), and display the results.

You can also modify the `src/main.c` file to include your own matrix data and operations. Here is a brief overview of the files and their purposes:

- `src/main.c`: Contains the main function and example usage of matrix operations.
- `src/matrix.c`: Contains the implementation of matrix operations.
- `src/matrix.h`: Header file declaring the functions for matrix operations.

## Files

- `Makefile`: Used to compile the project.
- `main.c`: The entry point of the program.
- `matrix.c`: Implementation of matrix operations.
- `matrix.h`: Header file with function declarations.
- `.gitignore`: Specifies files to ignore in the repository.
- `matrix.aux`, `matrix.log`: Generated files that should be ignored.

## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

If you have any questions or feedback, feel free to contact me at ahmedcali1984@gmail.com or via [LinkedIn](https://www.linkedin.com/in/ahmed-ali-99055728b/).
