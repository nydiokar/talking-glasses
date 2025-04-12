# PowerShell script to set up development environment
# Usage: .\scripts\setup_dev_environment.ps1

# Create a colorful header
function Show-Header {
    param (
        [string]$Title
    )
    
    $width = 60
    $padding = [math]::Floor(($width - $Title.Length) / 2)
    
    Write-Host "`n"
    Write-Host ("=" * $width) -ForegroundColor Blue
    Write-Host (" " * $padding + $Title + " " * $padding) -ForegroundColor Cyan
    Write-Host ("=" * $width) -ForegroundColor Blue
    Write-Host "`n"
}

Show-Header "Smart Glasses Development Environment Setup"

# Check for git
$git = Get-Command git -ErrorAction SilentlyContinue
if (-not $git) {
    Write-Host "Git is not installed. Please install Git from https://git-scm.com/" -ForegroundColor Red
    exit 1
}

# Check for VSCode/Cursor
$vscode = Get-Command code -ErrorAction SilentlyContinue
if (-not $vscode) {
    Write-Host "VSCode is not detected. Please ensure VSCode or Cursor is installed." -ForegroundColor Yellow
    Write-Host "Download from: https://code.visualstudio.com/ or https://cursor.sh/" -ForegroundColor Yellow
}

# Check for PlatformIO CLI
$platformio = Get-Command platformio -ErrorAction SilentlyContinue
if (-not $platformio) {
    Write-Host "PlatformIO CLI not found. Attempting to install..." -ForegroundColor Yellow
    
    # Check for Python
    $python = Get-Command python -ErrorAction SilentlyContinue
    if (-not $python) {
        Write-Host "Python is not installed. Please install Python from https://www.python.org/" -ForegroundColor Red
        exit 1
    }
    
    # Install PlatformIO
    Write-Host "Installing PlatformIO..." -ForegroundColor Cyan
    python -m pip install --upgrade pip
    pip install platformio
    
    # Verify installation
    $platformio = Get-Command platformio -ErrorAction SilentlyContinue
    if (-not $platformio) {
        Write-Host "Failed to install PlatformIO. Please install it manually." -ForegroundColor Red
        exit 1
    }
}

# Set up git hooks
Write-Host "Setting up git hooks..." -ForegroundColor Cyan

# Create hooks directory if it doesn't exist
if (!(Test-Path ".git\hooks")) {
    New-Item -ItemType Directory -Path ".git\hooks" -Force | Out-Null
}

# Create symlink for pre-commit hook
if (Test-Path ".github\hooks\pre-commit.ps1") {
    $sourcePath = (Resolve-Path ".github\hooks\pre-commit.ps1").Path
    $targetPath = (Resolve-Path ".git\hooks").Path + "\pre-commit"
    
    # Check if running with admin privileges
    $isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
    
    if ($isAdmin) {
        # Create symlink if running as admin
        New-Item -ItemType SymbolicLink -Path $targetPath -Target $sourcePath -Force | Out-Null
        Write-Host "Git pre-commit hook symlink created." -ForegroundColor Green
    } else {
        # Fallback to copy if not running as admin
        Copy-Item -Path $sourcePath -Destination $targetPath -Force | Out-Null
        Write-Host "Git pre-commit hook copied (not symlinked - requires admin)." -ForegroundColor Yellow
    }
} else {
    Write-Host "Pre-commit hook file not found." -ForegroundColor Red
}

# Install VSCode/Cursor extensions if VSCode is available
if ($vscode) {
    Write-Host "Installing recommended VSCode extensions..." -ForegroundColor Cyan
    code --install-extension platformio.platformio-ide
    code --install-extension ms-vscode.cpptools
}

# Initialize PlatformIO project libraries
Write-Host "Initializing PlatformIO libraries..." -ForegroundColor Cyan
platformio pkg install

# Setup complete
Show-Header "Setup Complete!"

Write-Host "Development environment setup complete. You're ready to develop!" -ForegroundColor Green
Write-Host "`nTo run all tests sequentially:" -ForegroundColor Yellow
Write-Host ".\scripts\run_all_tests.ps1" -ForegroundColor White
Write-Host "`nTo build the project:" -ForegroundColor Yellow
Write-Host "platformio run" -ForegroundColor White
Write-Host "`nHappy coding!" -ForegroundColor Cyan 