# Smart Glasses Release Script
# Usage: .\scripts\create_release.ps1 -Version "1.2.3" [-Message "Release message"]

param (
    [Parameter(Mandatory=$true)]
    [string]$Version,
    
    [Parameter(Mandatory=$false)]
    [string]$Message = "Release $Version"
)

# Ensure we're in the project root directory
$ProjectRoot = $PSScriptRoot | Split-Path -Parent
Set-Location $ProjectRoot
Write-Host "Working directory: $ProjectRoot" -ForegroundColor Cyan

# Ensure version format
if (!($Version -match "^\d+\.\d+\.\d+$")) {
    Write-Host "Error: Version must be in format X.Y.Z (e.g. 1.2.3)" -ForegroundColor Red
    exit 1
}

# Git operations
$TagName = "v$Version"

# Check if tag already exists
$TagExists = git tag -l $TagName
if ($TagExists) {
    Write-Host "Error: Tag $TagName already exists!" -ForegroundColor Red
    exit 1
}

# Check for uncommitted changes
$Status = git status --porcelain
if ($Status) {
    Write-Host "Warning: You have uncommitted changes in your working directory." -ForegroundColor Yellow
    Write-Host $Status
    $Confirm = Read-Host "Do you want to continue anyway? (y/N)"
    if ($Confirm -ne "y") {
        Write-Host "Release creation canceled." -ForegroundColor Yellow
        exit 0
    }
}

# Update version.h file for local testing
$VersionFile = Join-Path -Path $ProjectRoot -ChildPath "include\version.h"
if (Test-Path $VersionFile) {
    $VersionContent = Get-Content $VersionFile -Raw
    $UpdatedContent = $VersionContent -replace 'FIRMWARE_VERSION ".*"', "FIRMWARE_VERSION ""v$Version"""
    Set-Content -Path $VersionFile -Value $UpdatedContent
    Write-Host "Updated $VersionFile with version v$Version" -ForegroundColor Green
}

# Create and push the tag
Write-Host "Creating release $TagName..." -ForegroundColor Cyan

git tag -a $TagName -m $Message

Write-Host "Tag created locally. Push it to the remote repository?" -ForegroundColor Yellow
$PushConfirm = Read-Host "Push tag $TagName to origin? (y/N)"

if ($PushConfirm -eq "y") {
    git push origin $TagName
    Write-Host "Tag pushed to origin. GitHub Actions will now build and create the release." -ForegroundColor Green
    
    # Extract repository name from git remote
    $RemoteUrl = git config --get remote.origin.url
    $RepoPath = $RemoteUrl -replace '.*github\.com[:/](.*)\.git', '$1'
    Write-Host "You can monitor the process at: https://github.com/$RepoPath/actions" -ForegroundColor Cyan
} else {
    Write-Host "Tag not pushed. You can push it later with: git push origin $TagName" -ForegroundColor Yellow
}

Write-Host "Done!" -ForegroundColor Green 