@echo off
echo Compiling Hospital Management System...
gcc main.c admin.c doctor.c feedback.c find_doctor.c lab.c patient.c reception.c utils.c -o hms.exe
if %errorlevel% neq 0 (
    echo Compilation Failed!
    pause
    exit /b
)
echo Compilation Successful!
echo Starting HMS...
hms.exe
