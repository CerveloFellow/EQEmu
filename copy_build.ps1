# Copy EQEmu build outputs to server directory
$source = "C:\Frobozz\EQEmu\build\bin\Release"
$dest = "C:\Frobozz\Server\bin"

# Ensure destination exists
if (!(Test-Path $dest)) {
    New-Item -ItemType Directory -Path $dest -Force
}

# Copy exe, dll, and pdb files
Write-Host "Copying files from $source to $dest..."
Write-Host ""

$extensions = @("*.exe", "*.dll", "*.pdb")
$totalCount = 0

foreach ($ext in $extensions) {
    $files = Get-ChildItem -Path "$source\$ext" -ErrorAction SilentlyContinue
    foreach ($file in $files) {
        Copy-Item -Path $file.FullName -Destination $dest -Force
        Write-Host "Copied: $($file.Name)"
        $totalCount++
    }
}

Write-Host ""
Write-Host "Copied $totalCount files to $dest"