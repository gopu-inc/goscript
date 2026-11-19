$ErrorActionPreference = 'Stop'
$ScriptUrl = if ($env:GOSCRIPT_INSTALL_SCRIPT) {
    $env:GOSCRIPT_INSTALL_SCRIPT
} else {
    'https://raw.githubusercontent.com/gopu-inc/goscript/refs/heads/main/install.ps1'
}
$Installer = Join-Path ([System.IO.Path]::GetTempPath()) 'goscript-install.ps1'
try {
    Invoke-WebRequest -Uri $ScriptUrl -OutFile $Installer
    & powershell.exe -NoProfile -ExecutionPolicy Bypass -File $Installer
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
} finally {
    Remove-Item -Path $Installer -Force -ErrorAction SilentlyContinue
}
