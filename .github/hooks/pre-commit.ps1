# Pre-commit hook for the Smart Glasses project
# Put this in .git/hooks/pre-commit or use the setup script to link it

$ErrorColor = "Red"
$SuccessColor = "Green"
$InfoColor = "Cyan"

# Get list of changed files
$changed_files = git diff --cached --name-only --diff-filter=ACM | Where-Object { $_ -match '\.cpp$|\.h$|\.ino$' }

if (!$changed_files) {
    Write-Host "No C/C++ files to check." -ForegroundColor $InfoColor
    exit 0
}

# Banner
Write-Host "`n----------------------" -ForegroundColor $InfoColor
Write-Host "Smart Glasses Pre-Commit Checks" -ForegroundColor $InfoColor
Write-Host "----------------------`n" -ForegroundColor $InfoColor

# Check for debug print statements
$found_debug = $false
foreach ($file in $changed_files) {
    $content = Get-Content $file -ErrorAction SilentlyContinue
    if ($content -match "Serial\.print.*debug" -or $content -match "printf.*debug") {
        Write-Host "WARNING: Debug print statement found in $file" -ForegroundColor $ErrorColor
        $found_debug = $true
    }
}

if ($found_debug) {
    Write-Host "Remove or comment out debug print statements before committing." -ForegroundColor $ErrorColor
}

# Check for large files
foreach ($file in $changed_files) {
    $size = (Get-Item $file -ErrorAction SilentlyContinue).Length
    if ($size -gt 500KB) {
        Write-Host "WARNING: File $file is very large ($($size/1KB) KB). Consider breaking it into smaller modules." -ForegroundColor $ErrorColor
    }
}

# Run clang-format if available
$clang_format = Get-Command clang-format -ErrorAction SilentlyContinue
if ($clang_format) {
    Write-Host "Running clang-format..." -ForegroundColor $InfoColor
    
    foreach ($file in $changed_files) {
        clang-format -i $file
        git add $file
    }
    
    Write-Host "Code formatting completed." -ForegroundColor $SuccessColor
} else {
    Write-Host "clang-format not found. Skipping code formatting." -ForegroundColor $InfoColor
    Write-Host "Consider installing clang-format for automatic code formatting." -ForegroundColor $InfoColor
}

# Check for memory safety issues
$patterns = @(
    'malloc\s*\(.+\)'
    'free\s*\(.+\)'
    'new\s+\w+\s*\['
    'delete\s*\[\]'
)

foreach ($file in $changed_files) {
    $content = Get-Content $file -ErrorAction SilentlyContinue -Raw
    
    foreach ($pattern in $patterns) {
        if ($content -match $pattern) {
            Write-Host "NOTE: Manual memory management found in $file" -ForegroundColor $InfoColor
            Write-Host "Consider using smart pointers or RAII techniques instead." -ForegroundColor $InfoColor
            break
        }
    }
}

Write-Host "`nPre-commit checks completed." -ForegroundColor $SuccessColor
Write-Host "You can bypass these checks with 'git commit --no-verify'" -ForegroundColor $InfoColor
Write-Host "----------------------`n" -ForegroundColor $InfoColor

exit 0 