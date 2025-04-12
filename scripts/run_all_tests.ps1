# PowerShell script to run all tests sequentially
# Usage: .\scripts\run_all_tests.ps1

# Create the directory if it doesn't exist
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
if (!(Test-Path $scriptDir)) {
    New-Item -ItemType Directory -Path $scriptDir
}

function Run-Test {
    param (
        [string]$TestName,
        [string]$Description
    )
    
    Write-Host "`n=============================================" -ForegroundColor Cyan
    Write-Host "Running test: $TestName" -ForegroundColor Cyan
    Write-Host "$Description" -ForegroundColor Cyan
    Write-Host "=============================================`n" -ForegroundColor Cyan
    
    # Run the test
    platformio run -e $TestName -t upload
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "`nTest uploaded successfully. Check Serial Monitor for results.`n" -ForegroundColor Green
        
        # Prompt user to continue to next test
        $continue = Read-Host "Press Enter when you're ready to continue to the next test (or type 'skip' to skip remaining tests)"
        
        if ($continue -eq "skip") {
            return $false
        }
    } else {
        Write-Host "`nTest upload failed.`n" -ForegroundColor Red
        
        $retry = Read-Host "Would you like to retry? (y/n)"
        if ($retry -eq "y") {
            Run-Test -TestName $TestName -Description $Description
        }
    }
    
    return $true
}

# Define our tests
$tests = @(
    @{
        Name = "basic_test"
        Description = "Basic serial communication test"
    },
    @{
        Name = "i2c_test"
        Description = "I2C scanner for pins GPIO8/9"
    },
    @{
        Name = "status_led_blink"
        Description = "Status LED test for GPIO48"
    }
)

# Run each test in sequence
foreach ($test in $tests) {
    $continue = Run-Test -TestName $test.Name -Description $test.Description
    
    if (-not $continue) {
        Write-Host "Tests aborted by user." -ForegroundColor Yellow
        break
    }
}

Write-Host "`nAll tests completed!`n" -ForegroundColor Green 