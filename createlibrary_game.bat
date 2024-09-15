@echo off
setlocal

rem Source directory containing .cpp files
set SOURCE_DIR=code\sourcecode\game

rem Output directory for object files
set OUTPUT_DIR=lib\game
set STATIC_LIB=libgame.a

rem Create the output directory if it doesn't exist
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

rem Compile all .cpp files in the source directory into .o files
for %%f in ("%SOURCE_DIR%\*.cpp") do (
    echo Compiling %%~nxf...
    g++ -c "%%f" -o "%OUTPUT_DIR%\%%~nf.o" -Isrc\include -Icode\sourcecode\plain
    if errorlevel 1 (
        echo Compilation of %%~nxf failed.
        set COMPILATION_SUCCESSFUL=false
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
    echo Adding %%~nxf to library...
    ar r "%OUTPUT_DIR%\%STATIC_LIB%" "%%f"
    if errorlevel 1 (
        echo Building of %STATIC_LIB% failed.
        pause
    )
)

    echo Static library %STATIC_LIB% created successfully.
)

echo Done.

exit /b 0