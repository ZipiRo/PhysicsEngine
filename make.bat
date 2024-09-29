@echo off
setlocal

set BUILD_TYPE = %1
cls
echo.
if %1 == -r (
    echo [33mBUILDING RELEASE VERSION[0m
    mingw32-make -f makefile DEBUG=0
    start build/release/PhysicsEngine.exe 
) else if %1 == -d (
    echo [33mBUILDING DEBUG VERSION[0m
    mingw32-make -f makefile DEBUG=1
    start build/debug/PhysicsEngine.exe 
)
 