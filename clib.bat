@echo off
setlocal

rem Source directory containing .cpp files
set SOURCE_DIR=%1

rem Output directory for object files
set OUTPUT_DIR=%2
set STATIC_LIB=%3

echo -----------------------------------------
rem Create the output directory if it doesn't exist
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

rem Compile all .cpp files in the source directory into .o files
for %%f in ("%SOURCE_DIR%\*.cpp") do (
    set /p =Compiling [3m[34m%%~nxf[0m...<nul
    g++ -c "%%f" -o "%OUTPUT_DIR%\%%~nf.o" -Isrc\include -Icode\sourcecode\plainengine 
    if errorlevel 1 (
        set /p = [31merror[0m <nul
        echo.
        echo [31mCompilation of %%~nxf failed.[0m
        set COMPILATION_SUCCESSFUL=false
    ) else (
        set /p = [32mcompiled[0m <nul
        echo.
    )
)

rem Check compilation status
if "%COMPILATION_SUCCESSFUL%"=="false" (
    echo Compilation encountered errors.
    pause
) else (
    echo Compilation successful. Creating static library...

    rem Add all .o files to the static library using ar
    for %%f in ("%OUTPUT_DIR%\*.o") do (
    set /p =Adding [3m[35m%%~nxf[0m to library...<nul
    ar r "%OUTPUT_DIR%\%STATIC_LIB%" "%%f"
    if errorlevel 1 (
        set /p = [31error[0m <nul
        echo.
        echo [31mBuilding of %STATIC_LIB% failed.[0m
        pause
    ) else (
        del "%%f"
        set /p = [32madded[0m <nul
        echo.
    )
)
    echo Static library [33m%STATIC_LIB%[0m created successfully.
)

exit /b 0