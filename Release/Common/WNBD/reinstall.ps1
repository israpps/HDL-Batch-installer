$scriptLocation = [System.IO.Path]::GetDirectoryName(
    $myInvocation.MyCommand.Definition)

$wnbdBin = "$scriptLocation\wnbd-client.exe"
$wnbdInf = "$scriptLocation\wnbd.inf"
$wnbdCat = "$scriptLocation\wnbd.cat"
$wnbdSys = "$scriptLocation\wnbd.sys"
$wnbdEvents = "$scriptLocation\wnbdevents.xml"

$requiredFiles = @($wnbdBin, $wnbdInf, $wnbdCat, $wnbdSys)
foreach ($path in $requiredFiles) {
    if (!(Test-Path -Path $path -PathType leaf)) {
        Write-Warning "Could not find file: $path"
    }
}

wevtutil um $wnbdEvents
& $wnbdBin uninstall-driver

& $wnbdBin install-driver $wnbdInf
wevtutil im $wnbdEvents
