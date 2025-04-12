# PowerShell pre-commit hook for Windows users
#
# To install, run in PowerShell:
# New-Item -ItemType SymbolicLink -Path ".git\hooks\pre-commit" -Target ".github\hooks\pre-commit.ps1"

Write-Host "Running pre-commit checks..."

# Run PlatformIO to verify build
Write-Host "Building project..."
$build = Start-Process -FilePath "platformio" -ArgumentList "run -e basic_test" -Wait -PassThru

# Check if build succeeded
if ($build.ExitCode -ne 0) {
    Write-Host "❌ Build failed. Please fix the errors before committing." -ForegroundColor Red
    exit 1
}

Write-Host "✅ Pre-commit checks passed!" -ForegroundColor Green
exit 0 