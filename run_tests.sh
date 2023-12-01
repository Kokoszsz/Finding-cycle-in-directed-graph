#!/bin/bash
clear

# Define input and output file names
input_file=tests_project/test_data_1.txt
output_file=tests_project/test_output_1.txt
expected_output_file=tests_project/test_expected_output_1.txt



# Compare actual and expected output
if cmp -s "$output_file" "$expected_output_file"; then
    echo "Tests passed."
    exit 0
else
    echo "Tests failed."
    exit 1
fi
