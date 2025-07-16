# Windows PowerShell Deployment Script for Srikok Git
# This script packages the application for distribution

Write-Host "Deploying Srikok Git for Windows..." -ForegroundColor Green
Write-Host ""

# Function to check if a file exists
function Test-FileExists {
    param($FilePath)
    return Test-Path $FilePath
}

# Check if built executable exists
$executablePath = ""
if (Test-FileExists "build\Release\SrikokGit.exe") {
    $executablePath = "build\Release\SrikokGit.exe"
} elseif (Test-FileExists "build\SrikokGit.exe") {
    $executablePath = "build\SrikokGit.exe"
} else {
    Write-Host "Error: SrikokGit.exe not found. Please build the application first." -ForegroundColor Red
    Write-Host "Run build-windows.bat or build-windows.ps1 to build the application." -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

# Check if windeployqt is available
try {
    Get-Command "windeployqt" -ErrorAction Stop | Out-Null
} catch {
    Write-Host "Error: windeployqt not found in PATH" -ForegroundColor Red
    Write-Host "Please ensure Qt6 bin directory is in your PATH" -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

# Create deployment directory
$deployDir = "deploy"
if (Test-Path $deployDir) {
    Write-Host "Cleaning existing deployment directory..." -ForegroundColor Yellow
    Remove-Item -Path $deployDir -Recurse -Force
}
New-Item -ItemType Directory -Path $deployDir | Out-Null

# Copy executable
Write-Host "Copying executable..." -ForegroundColor Yellow
Copy-Item -Path $executablePath -Destination "$deployDir\" -Force
if (-not $?) {
    Write-Host "Error: Failed to copy executable" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}

# Change to deployment directory
Set-Location $deployDir

# Run windeployqt to gather dependencies
Write-Host "Running windeployqt to gather Qt dependencies..." -ForegroundColor Yellow
$deployResult = Start-Process -FilePath "windeployqt.exe" -ArgumentList "SrikokGit.exe", "--verbose", "2" -Wait -PassThru -NoNewWindow

if ($deployResult.ExitCode -ne 0) {
    Write-Host "Warning: windeployqt encountered issues, but continuing..." -ForegroundColor Yellow
}

# Change back to original directory
Set-Location ".."

# Copy additional files
Write-Host "Copying additional files..." -ForegroundColor Yellow
$additionalFiles = @("README.md", "LICENSE", "BUILD_WINDOWS.md")
foreach ($file in $additionalFiles) {
    if (Test-Path $file) {
        Copy-Item -Path $file -Destination "$deployDir\" -Force
    }
}

# Create start script
Write-Host "Creating start script..." -ForegroundColor Yellow
$startScript = @"
@echo off
cd /d "%~dp0"
start SrikokGit.exe
"@
$startScript | Out-File -FilePath "$deployDir\start.bat" -Encoding ASCII

# Create installation script
Write-Host "Creating installation script..." -ForegroundColor Yellow
$installScript = @"
@echo off
echo Installing Srikok Git...
set "INSTALL_DIR=%ProgramFiles%\SrikokGit"
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
xcopy * "%INSTALL_DIR%" /E /I /Y
echo Installation complete!
pause
"@
$installScript | Out-File -FilePath "$deployDir\install.bat" -Encoding ASCII

# Create uninstall script
Write-Host "Creating uninstall script..." -ForegroundColor Yellow
$uninstallScript = @"
@echo off
echo Uninstalling Srikok Git...
set "INSTALL_DIR=%ProgramFiles%\SrikokGit"
if exist "%INSTALL_DIR%" rmdir /s /q "%INSTALL_DIR%"
echo Uninstallation complete!
pause
"@
$uninstallScript | Out-File -FilePath "$deployDir\uninstall.bat" -Encoding ASCII

# List deployed files
Write-Host ""
Write-Host "Deployment complete!" -ForegroundColor Green
Write-Host ""
Write-Host "Contents of deployment directory:" -ForegroundColor Cyan
Get-ChildItem -Path $deployDir -Name | Sort-Object
Write-Host ""

# Check if all required files are present
Write-Host "Checking deployment integrity..." -ForegroundColor Yellow
$requiredFiles = @(
    "SrikokGit.exe",
    "Qt6Core.dll",
    "Qt6Gui.dll",
    "Qt6Widgets.dll",
    "platforms\qwindows.dll"
)

$missingFiles = @()
foreach ($file in $requiredFiles) {
    if (-not (Test-Path "$deployDir\$file")) {
        $missingFiles += $file
    }
}

if ($missingFiles.Count -gt 0) {
    Write-Host "Warning: Missing files: $($missingFiles -join ', ')" -ForegroundColor Yellow
    Write-Host "The deployment may not work correctly." -ForegroundColor Yellow
} else {
    Write-Host "All required files are present." -ForegroundColor Green
}

Write-Host ""
Write-Host "Deployment directory: $(Get-Location)\$deployDir" -ForegroundColor Cyan
Write-Host "You can now distribute the contents of the deploy directory." -ForegroundColor Green
Write-Host ""
Write-Host "To test the deployment:" -ForegroundColor Cyan
Write-Host "  cd $deployDir" -ForegroundColor White
Write-Host "  .\SrikokGit.exe" -ForegroundColor White
Write-Host ""
Write-Host "To create a zip package:" -ForegroundColor Cyan
Write-Host "  Compress-Archive -Path $deployDir\* -DestinationPath SrikokGit-Windows.zip" -ForegroundColor White
Write-Host ""

# Optionally create zip package
$createZip = Read-Host "Would you like to create a zip package now? (y/n)"
if ($createZip -eq 'y' -or $createZip -eq 'Y') {
    Write-Host "Creating zip package..." -ForegroundColor Yellow
    $zipPath = "SrikokGit-Windows.zip"
    if (Test-Path $zipPath) {
        Remove-Item $zipPath -Force
    }
    
    try {
        Compress-Archive -Path "$deployDir\*" -DestinationPath $zipPath -Force
        Write-Host "Zip package created: $zipPath" -ForegroundColor Green
    } catch {
        Write-Host "Error creating zip package: $_" -ForegroundColor Red
    }
}

Read-Host "Press Enter to exit"