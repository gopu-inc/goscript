$ErrorActionPreference = 'Stop'

$Version = if ($env:GOSCRIPT_VERSION) { $env:GOSCRIPT_VERSION } else { 'latest' }
$InstallRoot = if ($env:GOSCRIPT_PREFIX) {
    $env:GOSCRIPT_PREFIX
} else {
    Join-Path $env:LOCALAPPDATA 'Programs\Goscript'
}
$Asset = 'goscript-windows-x86_64.zip'
if ($Version -eq 'latest') {
    $ReleaseUrl = 'https://github.com/gopu-inc/goscript/releases/latest/download'
} else {
    $ReleaseUrl = "https://github.com/gopu-inc/goscript/releases/download/$Version"
}

$WorkDir = Join-Path ([System.IO.Path]::GetTempPath()) ([System.Guid]::NewGuid().ToString())
New-Item -ItemType Directory -Path $WorkDir | Out-Null
try {
    $Archive = Join-Path $WorkDir $Asset
    $ChecksumFile = "$Archive.sha256"
    Invoke-WebRequest -Uri "$ReleaseUrl/$Asset" -OutFile $Archive
    Invoke-WebRequest -Uri "$ReleaseUrl/$Asset.sha256" -OutFile $ChecksumFile

    $Expected = ((Get-Content $ChecksumFile -Raw).Trim() -split '\s+')[0].ToLowerInvariant()
    $Actual = (Get-FileHash -Path $Archive -Algorithm SHA256).Hash.ToLowerInvariant()
    if (!$Expected -or $Actual -ne $Expected) {
        throw 'Goscript release checksum verification failed.'
    }

    $Extracted = Join-Path $WorkDir 'package'
    Expand-Archive -Path $Archive -DestinationPath $Extracted
    New-Item -ItemType Directory -Force -Path $InstallRoot | Out-Null
    Copy-Item -Path (Join-Path $Extracted 'bin'), (Join-Path $Extracted 'share') `
        -Destination $InstallRoot -Recurse -Force

    $BinDir = Join-Path $InstallRoot 'bin'
    $CurrentPath = [Environment]::GetEnvironmentVariable('Path', 'User')
    $PathItems = @($CurrentPath -split ';' | Where-Object { $_ })
    if ($PathItems -notcontains $BinDir) {
        [Environment]::SetEnvironmentVariable('Path', (($PathItems + $BinDir) -join ';'), 'User')
    }

    Write-Output "Goscript and Golem installed under $InstallRoot."
    Write-Output 'Open a new terminal, then install standard packages with: golem install base'
} finally {
    Remove-Item -Path $WorkDir -Recurse -Force -ErrorAction SilentlyContinue
}
