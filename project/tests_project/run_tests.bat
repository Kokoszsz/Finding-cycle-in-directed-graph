@echo off
cls

setlocal enabledelayedexpansion
echo Current directory: %cd%
dir
for /l %%i in (1,1,8) do (

	
    set input_file=project\tests_project\test_case_%%i\test_data.txt
    set expected_output_file=project\tests_project\test_case_%%i\test_expected_output.txt

	type nul > tests_project\test_case_%%i\test_output.txt

    x64\Debug\project.exe -g !input_file! -c !output_file!


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
