# DNA Sequence Analyzer

## Overview
DNA Sequence Analyzer is a C++-based application designed to streamline the comparison of DNA sequences. It reads DNA data from FASTA files and compares an original, verified sequence against a mutated sequence to identify genetic variations. 

## Features
*   **FASTA File Validation:** Validates input sequences to ensure they only contain standard nucleotide characters (A, C, G, T, N).
*   **Sequence Analysis:** Calculates the Hamming Distance and identifies the exact positions of nucleotide substitutions.
*   **Similarity Metric:** Computes the overall similarity percentage and the total count of matching bases between sequences.
*   **Automated Reporting:** Exports all analysis results and mutation records to a CSV file (`comparison_history.csv`) for persistent storage and easy review.
*   **Interactive TUI:** Features a clean, text-based user interface for navigating datasets and reviewing comparison history.

## Prerequisites
*   A C++17 compatible compiler (e.g., GCC, Clang, or MSVC)
*   CMake (Version 3.10 or higher)

## Build Instructions (Using CMake)
1. Open a terminal and navigate to the project root directory.
2. Create a build directory and navigate into it:
   `mkdir build && cd build`
3. Generate the build files:
   `cmake ..`
4. Compile the project:
   `cmake --build .`

## Usage Instructions
1. Run the compiled executable (`./DNA_Analyzer` on Linux/Mac, or `DNA_Analyzer.exe` on Windows).
2. Ensure that the original and mutated `.fasta` files you want to analyze are in the same directory as the executable.
3. Follow the on-screen prompts to input the filenames and view the analysis results.