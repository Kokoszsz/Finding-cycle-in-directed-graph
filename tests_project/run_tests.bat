@echo off
cls


set input_file=tests_project\test_case_1\test_data.txt
set output_file=tests_project\test_case_1\test_output.txt
set expected_output_file=tests_project\test_case_1\test_expected_output.txt

x64\Debug\project.exe -g %input_file% -c %output_file%

echo Test 1 failed.

set input_file=tests_project\test_case_2\test_data.txt
set output_file=tests_project\test_case_2\test_output.txt
set expected_output_file=tests_project\test_case_2\test_expected_output.txt

x64\Debug\project.exe -g %input_file% -c %output_file%

echo Test 2 failed.

set input_file=tests_project\test_case_3\test_data.txt
set output_file=tests_project\test_case_3\test_output.txt
set expected_output_file=tests_project\test_case_3\test_expected_output.txt

x64\Debug\project.exe -g %input_file% -c %output_file%

echo Test 3 failed.

fc %output_file% %expected_output_file% > nul
if errorlevel 1 (
    echo Tests failed.
    pause
    exit 1
) else (
    echo Tests passed.
    pause
    exit 0
)
