@echo off
cls

setlocal enabledelayedexpansion
echo Current directory: %cd%
for /l %%i in (1,1,8) do (

	
    set input_file=tests_project\test_case_%%i\test_data.txt
    set output_file=tests_project\test_case_%%i\test_output.txt
    set expected_output_file=tests_project\test_case_%%i\test_expected_output.txt

	type nul > !output_file!

    x64\Debug\project.exe -g !input_file! -c !output_file!

    echo Test %%i failed.

    fc !output_file! !expected_output_file! > nul
    if errorlevel 1 (
        echo Tests failed.
        pause
        exit 1
    ) else (
        echo Test %%i passed.
    )
)

echo All tests passed.
pause
exit 0
