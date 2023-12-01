@echo off
cls

REM Define array for test case folder names
set "test_case_folders=test_case_1 test_case_2 test_case_3"

REM Loop over test case folders
for %%i in (%test_case_folders%) do (
    set "current_folder=tests_project\%%i"

    set "input_file=!current_folder!\test_data.txt"
    set "output_file=!current_folder!\test_output.txt"
    set "expected_output_file=!current_folder!\test_expected_output.txt"

    x64\Debug\project.exe -g "!input_file!" -c "!output_file!"

    fc "!output_file!" "!expected_output_file!" > nul
    if errorlevel 1 (
        echo Tests for !current_folder! failed.
        pause
        exit 1
    ) else (
        echo Tests for !current_folder! passed.
    )
)

pause
exit 0
