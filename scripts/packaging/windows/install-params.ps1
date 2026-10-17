# Installs the Sapling parameters AMMOcoin needs into %APPDATA%\AMMOcoinParams.
# Uses the copies in .\share next to this script when present, otherwise downloads them
# from download.z.cash. Every file is SHA-256 verified. Run via install-params.bat.
$ErrorActionPreference = 'Stop'
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$dest = Join-Path $env:APPDATA 'AMMOcoinParams'
$url  = 'https://download.z.cash/downloads'
$files = [ordered]@{
  'sapling-spend.params'  = '8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13'
  'sapling-output.params' = '2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4'
}

function Test-Param([string]$path, [string]$sha) {
  (Test-Path -LiteralPath $path) -and ((Get-FileHash -Algorithm SHA256 -LiteralPath $path).Hash.ToLower() -eq $sha)
}

New-Item -ItemType Directory -Force -Path $dest | Out-Null
foreach ($name in $files.Keys) {
  $sha = $files[$name]
  $target = Join-Path $dest $name
  if (Test-Param $target $sha) { Write-Host "ok       $target"; continue }
  $tmp = "$target.part"
  $local = Join-Path (Join-Path $PSScriptRoot 'share') $name
  if (Test-Param $local $sha) {
    Write-Host "copying  $local"
    Copy-Item -LiteralPath $local -Destination $tmp -Force
  } else {
    Write-Host "fetching $url/$name"
    try {
      $ProgressPreference = 'SilentlyContinue'
      Invoke-WebRequest -UseBasicParsing -Uri "$url/$name" -OutFile $tmp
    } catch {
      Write-Host "Could not download $name (offline?). Copy sapling-spend.params and sapling-output.params into $dest by hand, or use the Setup.exe installer, which includes them." -ForegroundColor Red
      exit 1
    }
  }
  if (-not (Test-Param $tmp $sha)) {
    Remove-Item -LiteralPath $tmp -Force -ErrorAction SilentlyContinue
    Write-Host "$name failed its SHA-256 check; not installed." -ForegroundColor Red
    exit 1
  }
  Move-Item -LiteralPath $tmp -Destination $target -Force
  Write-Host "ok       $target"
}
Write-Host "Sapling parameters are ready in $dest. You can now start ammocoin-qt.exe."
