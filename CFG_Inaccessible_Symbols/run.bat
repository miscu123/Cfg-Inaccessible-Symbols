@echo off
REM Compile the program
g++ main.cpp symbols.cpp -o main.exe

REM Check if compilation succeeded
if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    pause >nul
    exit /b %ERRORLEVEL%
)

REM 
cls

REM 
main.exe

REM 
pause >nul 