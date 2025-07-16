@echo off
REM Windows Deployment Script for Srikok Git
REM This script packages the application for distribution

echo Deploying Srikok Git for Windows...
echo.

REM Check if built executable exists
if not exist "build\Release\SrikokGit.exe" (
    if not exist "build\SrikokGit.exe" (
        echo Error: SrikokGit.exe not found. Please build the application first.
        echo Run build-windows.bat to build the application.
        pause
        exit /b 1
    )
    set "EXECUTABLE_PATH=build\SrikokGit.exe"
) else (
    set "EXECUTABLE_PATH=build\Release\SrikokGit.exe"
)

REM Check if windeployqt is available
where windeployqt >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: windeployqt not found in PATH
    echo Please ensure Qt6 bin directory is in your PATH
    pause
    exit /b 1
)

REM Create deployment directory
set "DEPLOY_DIR=deploy"
if exist "%DEPLOY_DIR%" (
    echo Cleaning existing deployment directory...
    rmdir /s /q "%DEPLOY_DIR%"
)
mkdir "%DEPLOY_DIR%"

REM Copy executable
echo Copying executable...
copy "%EXECUTABLE_PATH%" "%DEPLOY_DIR%\"
if %errorlevel% neq 0 (
    echo Error: Failed to copy executable
    pause
    exit /b 1
)

REM Change to deployment directory
cd "%DEPLOY_DIR%"

REM Run windeployqt to gather dependencies
echo Running windeployqt to gather Qt dependencies...
windeployqt.exe SrikokGit.exe --verbose 2
if %errorlevel% neq 0 (
    echo Warning: windeployqt encountered issues, but continuing...
)

REM Copy additional files
cd ..
echo Copying additional files...
copy "README.md" "%DEPLOY_DIR%\" >nul 2>nul
copy "LICENSE" "%DEPLOY_DIR%\" >nul 2>nul
copy "BUILD_WINDOWS.md" "%DEPLOY_DIR%\" >nul 2>nul

REM Create start script
echo Creating start script...
echo @echo off > "%DEPLOY_DIR%\start.bat"
echo cd /d "%%~dp0" >> "%DEPLOY_DIR%\start.bat"
echo start SrikokGit.exe >> "%DEPLOY_DIR%\start.bat"

REM Create installation script
echo Creating installation script...
echo @echo off > "%DEPLOY_DIR%\install.bat"
echo echo Installing Srikok Git... >> "%DEPLOY_DIR%\install.bat"
echo set "INSTALL_DIR=%%ProgramFiles%%\SrikokGit" >> "%DEPLOY_DIR%\install.bat"
echo if not exist "%%INSTALL_DIR%%" mkdir "%%INSTALL_DIR%%" >> "%DEPLOY_DIR%\install.bat"
echo xcopy * "%%INSTALL_DIR%%" /E /I /Y >> "%DEPLOY_DIR%\install.bat"
echo echo Installation complete! >> "%DEPLOY_DIR%\install.bat"
echo pause >> "%DEPLOY_DIR%\install.bat"

REM Create uninstall script
echo Creating uninstall script...
echo @echo off > "%DEPLOY_DIR%\uninstall.bat"
echo echo Uninstalling Srikok Git... >> "%DEPLOY_DIR%\uninstall.bat"
echo set "INSTALL_DIR=%%ProgramFiles%%\SrikokGit" >> "%DEPLOY_DIR%\uninstall.bat"
echo if exist "%%INSTALL_DIR%%" rmdir /s /q "%%INSTALL_DIR%%" >> "%DEPLOY_DIR%\uninstall.bat"
echo echo Uninstallation complete! >> "%DEPLOY_DIR%\uninstall.bat"
echo pause >> "%DEPLOY_DIR%\uninstall.bat"

REM List deployed files
echo.
echo Deployment complete!
echo.
echo Contents of deployment directory:
dir "%DEPLOY_DIR%" /b
echo.

REM Check if all required files are present
echo Checking deployment integrity...
set "MISSING_FILES="
if not exist "%DEPLOY_DIR%\SrikokGit.exe" set "MISSING_FILES=SrikokGit.exe "
if not exist "%DEPLOY_DIR%\Qt6Core.dll" set "MISSING_FILES=%MISSING_FILES%Qt6Core.dll "
if not exist "%DEPLOY_DIR%\Qt6Gui.dll" set "MISSING_FILES=%MISSING_FILES%Qt6Gui.dll "
if not exist "%DEPLOY_DIR%\Qt6Widgets.dll" set "MISSING_FILES=%MISSING_FILES%Qt6Widgets.dll "
if not exist "%DEPLOY_DIR%\platforms\qwindows.dll" set "MISSING_FILES=%MISSING_FILES%platforms\qwindows.dll "

if not "%MISSING_FILES%"=="" (
    echo Warning: Missing files: %MISSING_FILES%
    echo The deployment may not work correctly.
) else (
    echo All required files are present.
)

echo.
echo Deployment directory: %CD%\%DEPLOY_DIR%
echo You can now distribute the contents of the deploy directory.
echo.
echo To test the deployment:
echo   cd %DEPLOY_DIR%
echo   SrikokGit.exe
echo.
echo To create a zip package:
echo   powershell Compress-Archive -Path %DEPLOY_DIR%\* -DestinationPath SrikokGit-Windows.zip
echo.

pause