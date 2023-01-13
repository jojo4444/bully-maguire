function go-exit{
    exit
}

function Build-Project {
    param ([string] $cmake, [string] $msbuilder)
    &"$cmake" -G "Visual Studio 17 2022" ..
    &"$msbuilder" .\bully-maguire.sln -m -p:Configuration=Release
}

function Prepare-Build-Dir{
    New-Item .\release -type directory -force
    cd .\release
}

function Test{
    param([string] $gen, [string] $sol, [int] $n)
    for ($i = 0; $i -lt $n; $i++){
        echo "10 random" | &"$gen" > test; if ($LASTEXITCODE -ne 0) { go-exit }
        $res = (Get-Content test -last 1).Split(" ")
        Get-Content test | &"$sol" > ans; if ($LASTEXITCODE -ne 0) { go-exit }
        $res2 = (Get-Content ans -last 1).Split(" ")
        for ($j = 0; $j -lt 3; $j++){
            if ([Math]::abs($res[$j] - $res2[$j]) -gt 0.0001){
                echo "Error\nres1: $res\nres2: $res2"
                go-exit
            }
        }
    }
}

function find-MSbuilder{
    $msbuilder = &"${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe
    if (($LASTEXITCODE -eq 0) -and $msbuilder){
        return $msbuilder
    }
    echo "Can't find Microsoft Visual Studio MSBuilder.exe"
    go-exit
}


Prepare-Build-Dir
$msbuilder = find-MSbuilder
Build-Project -cmake cmake -msbuilder "$msbuilder" 
Test -gen .\generator\Release\generator.exe -sol .\solution\Release\solution.exe -n 1000