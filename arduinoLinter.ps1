$ErrorActionPreference = "Stop"

$tempDir = Join-Path $env:TEMP "lib_lint_test"

if (Test-Path $tempDir) {
    Remove-Item -Recurse -Force $tempDir
}
New-Item -ItemType Directory -Force -Path $tempDir | Out-Null

try {
    Copy-Item library.properties $tempDir -ErrorAction SilentlyContinue
    Copy-Item README* $tempDir -ErrorAction SilentlyContinue
    Copy-Item LICENSE* $tempDir -ErrorAction SilentlyContinue

    if (Test-Path src) {
        Copy-Item -Recurse src $tempDir
    }

    if (Test-Path examples) {
        $destExamples = Join-Path $tempDir "examples"
        New-Item -ItemType Directory -Force -Path $destExamples | Out-Null

        Get-ChildItem -Path examples -Directory | ForEach-Object {
            $exampleFolder = $_.Name
            $targetFolder = Join-Path $destExamples $exampleFolder
            New-Item -ItemType Directory -Force -Path $targetFolder | Out-Null

            Get-ChildItem -Path $_.FullName -File | Where-Object {
                $_.Extension -in @(".ino", ".cpp", ".h", ".c") -or $_.Name -like "README*"
            } | Copy-Item -Destination $targetFolder
        }
    }

    Write-Host "`n--- [1/2] SPECIFICATION ---" -ForegroundColor Cyan
    & .\arduino-lint.exe $tempDir --compliance specification --verbose

    Write-Host "`n--- [2/2] LIBRARY MANAGER SUBMIT ---" -ForegroundColor Yellow
    & .\arduino-lint.exe $tempDir --library-manager submit --verbose

}
finally {
    if (Test-Path $tempDir) {
        Remove-Item -Recurse -Force $tempDir
    }
}