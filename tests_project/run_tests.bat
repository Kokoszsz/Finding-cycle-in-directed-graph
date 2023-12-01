@echo off
cls

REM Define input and output file names
set input_file=tests_project\test_data_1.txt
set output_file=tests_project\test_output_1.txt
set expected_output_file=tests_project\test_expected_output_1.txt

REM Run your program with command-line arguments
project -g "%input_file%" -c "%output_file%"

REM Compare actual and expected output
fc "%output_file%" "%expected_output_file%" > nul
if %errorlevel% equ 0 (
    echo Tests passed.
    exit /b 0
) else (
    echo Tests failed.
    exit /b 1
)
