@echo off
cls

REM Define input and output file names
set input_file=tests_project\test_data_1.txt
set output_file=tests_project\test_output_1.txt
set expected_output_file=tests_project\test_expected_output_1.txt

REM Run your program with command-line arguments
x64\Debug\project.exe -g %input_file% -c %output_file%

REM Compare actual and expected output
fc %output_file% %expected_output_file% > nul
if errorlevel 1 (
    echo Tests failed.
    pause
    exit 1
) else (
    echo Tests padsadsadassed.
    pause
    exit 0
)
