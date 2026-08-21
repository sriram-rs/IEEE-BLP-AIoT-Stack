# Downloads the AIoT gateway course code and runs the one-command setup, so
# a student can go from nothing to a working environment with one line:
#
#   iwr <raw-url-of-this-file> -UseBasicParsing | iex
#
# The piped form above can't pass extra flags through (a limitation of
# "iwr | iex", not of this script). To pass flags (e.g. --with-pptx),
# download this file first, then run it directly:
#
#   .\bootstrap.ps1 --with-pptx
#
# IMPORTANT: everything below runs inside a function and uses "return",
# never "exit". When this file's content is piped into "iex"
# (Invoke-Expression), it runs inline in the CURRENT PowerShell session,
# not as a separate process - so a bare "exit" would close the student's
# entire PowerShell window instantly, wiping out every message (including
# "Setup complete!") before they can read it. "return" only leaves this
# function, leaving the window open either way.
#
# NOTE: $RepoZipUrl below points at a branch. Update it to point at `main`
# once feature/onboarding-scripts merges.

function Invoke-AiotBootstrap {
    param([string[]]$ForwardArgs = @())

    $RepoZipUrl = "https://github.com/sriram-rs/IEEE-BLP-AIoT-Stack/archive/refs/heads/feature/onboarding-scripts.zip"
    $DestDir = Join-Path (Get-Location) "IEEE-BLP-AIoT-Stack"

    Write-Host "== Downloading the AIoT Gateway course code =="

    # The real, careful Python-version check happens later in setup.bat,
    # once it's downloaded - here we just need any Python 3 to run
    # start_installation.py.
    $PyExe = $null
    $PyArgs = @()
    if (Get-Command py -ErrorAction SilentlyContinue) {
        $PyExe = "py"; $PyArgs = @("-3")
    } elseif (Get-Command python -ErrorAction SilentlyContinue) {
        $PyExe = "python"; $PyArgs = @()
    }

    if (-not $PyExe) {
        Write-Host "No Python installation was found on this machine."
        Write-Host "Install Python 3.10 or newer from https://www.python.org/downloads/windows/"
        Write-Host "IMPORTANT: check 'Add python.exe to PATH' during install, then run this command again."
        Write-Host ""
        Write-Host "If this is a school/managed laptop and you cannot install software,"
        Write-Host "ask your instructor for help."
        return 1
    }

    $TmpZip = Join-Path $env:TEMP ("aiot-stack-" + [guid]::NewGuid().ToString() + ".zip")
    try {
        Invoke-WebRequest -Uri $RepoZipUrl -OutFile $TmpZip -UseBasicParsing
    } catch {
        Write-Host "Could not download the code. Check your internet connection and try again."
        return 2
    }

    $ExtractDir = Join-Path $env:TEMP ("aiot-stack-extract-" + [guid]::NewGuid().ToString())
    try {
        Expand-Archive -Path $TmpZip -DestinationPath $ExtractDir -Force
    } catch {
        Write-Host "Downloaded the code but could not extract it. Ask your instructor for help."
        Remove-Item $TmpZip -Force -ErrorAction SilentlyContinue
        return 3
    }
    Remove-Item $TmpZip -Force -ErrorAction SilentlyContinue

    $SrcDir = Get-ChildItem -Path $ExtractDir -Directory | Select-Object -First 1
    if (-not $SrcDir) {
        Write-Host "Downloaded the code but couldn't find it after extracting."
        Write-Host "Ask your instructor for help."
        return 4
    }

    if (Test-Path $DestDir) {
        Write-Host "Folder $DestDir already exists - using it as-is instead of overwriting."
    } else {
        Move-Item $SrcDir.FullName $DestDir
    }
    Remove-Item -Recurse -Force $ExtractDir -ErrorAction SilentlyContinue

    Write-Host "Code is in: $DestDir"
    Set-Location $DestDir
    Write-Host "Running setup..."
    & $PyExe @PyArgs "start_installation.py" @ForwardArgs
    return $LASTEXITCODE
}

$AiotExitCode = Invoke-AiotBootstrap -ForwardArgs $args

Write-Host ""
if ($AiotExitCode -eq 0) {
    Write-Host "== Setup finished successfully. ==" -ForegroundColor Green
    Write-Host "Before you start using the gateway, take a look at PREREQUISITES.md"
    Write-Host "in the IEEE-BLP-AIoT-Stack folder - it covers a couple of one-time,"
    Write-Host "one-per-machine things this script can't do for you (like turning"
    Write-Host "Bluetooth on)."
} else {
    Write-Host "== Setup did NOT finish successfully (exit code $AiotExitCode). ==" -ForegroundColor Red
    Write-Host "Scroll up to read the error message. Copy it and ask your instructor for help."
}
Write-Host ""
Read-Host "Press Enter to close this window"
