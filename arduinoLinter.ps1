$tempDir = Join-Path $env:TEMP "lib_lint_test"
if (Test-Path $tempDir) { Remove-Item -Recurse -Force $tempDir }
New-Item -ItemType Directory -Force -Path $tempDir | Out-Null

# 1. Copia i metadati radice
Copy-Item library.properties $tempDir -ErrorAction SilentlyContinue
Copy-Item README* $tempDir -ErrorAction SilentlyContinue
Copy-Item LICENSE* $tempDir -ErrorAction SilentlyContinue

# 2. Copia solo sorgenti puliti (esclude build)
if (Test-Path src) {
    Copy-Item -Recurse src $tempDir
}

# 3. Copia examples escludendo ricorsioni di build (.pio, .git)
if (Test-Path examples) {
    $destExamples = Join-Path $tempDir "examples"
    New-Item -ItemType Directory -Force -Path $destExamples | Out-Null

    Get-ChildItem -Path examples -Directory | ForEach-Object {
        $exampleFolder = $_.Name
        $targetFolder = Join-Path $destExamples $exampleFolder
        New-Item -ItemType Directory -Force -Path $targetFolder | Out-Null

        # Copia solo file sorgente dello sketch (.ino, .cpp, .h)
        Get-ChildItem -Path $_.FullName -File | Where-Object {
            $_.Extension -in @(".ino", ".cpp", ".h", ".c") -or $_.Name -like "README*"
        } | Copy-Item -Destination $targetFolder
    }
}

Write-Host "Avvio analisi su cartella pulita..." -ForegroundColor Cyan
& .\arduino-lint.exe $tempDir --compliance specification

Remove-Item -Recurse -Force $tempDir
