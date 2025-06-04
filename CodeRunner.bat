@echo off
echo Compiling project...
g++ new_project.cpp instructor.cpp student.cpp -o merged_project

if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b
)

echo Compilation successful. Running project...
.\merged_project
pause
