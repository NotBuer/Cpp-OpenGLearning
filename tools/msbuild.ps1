param(
    [ValidateSet("Build", "Rebuild", "Clean")]
    [string]$Target = "Build",

    [string]$Configuration = "Debug",
    [string]$Platform = "x64",
    [string]$PlatformToolset = "v143"
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$solutionPath = Join-Path $repoRoot "OpenGLearning\OpenGLearning.sln"

if (-not (Test-Path -LiteralPath $solutionPath)) {
    throw "Solution file not found at '$solutionPath'."
}

$msbuildCandidates = @(
    "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe",
    "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe",
    "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe",
    "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
)

$msbuildPath = $msbuildCandidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1

if (-not $msbuildPath) {
    throw @"
MSBuild.exe was not found in the expected Visual Studio 2022 locations.
Install Visual Studio Build Tools 2022 or update tools\msbuild.ps1 with your MSBuild path.
"@
}

$arguments = @(
    $solutionPath,
    "/t:$Target",
    "/p:Configuration=$Configuration",
    "/p:Platform=$Platform",
    "/p:PlatformToolset=$PlatformToolset",
    "/m"
)

Write-Host "Using MSBuild: $msbuildPath"
Write-Host "Target: $Target | Configuration: $Configuration | Platform: $Platform | Toolset: $PlatformToolset"

& $msbuildPath @arguments
$exitCode = $LASTEXITCODE

if ($exitCode -ne 0) {
    exit $exitCode
}
