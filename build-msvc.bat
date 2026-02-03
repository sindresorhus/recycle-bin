@echo off

setlocal EnableExtensions

set "architecture=%~1"
if "%architecture%"=="" (
	echo Usage: build-msvc.bat ^<i686^|x86_64^|arm64^>
	exit /b 1
)

set "vcvars="
if /i "%architecture%"=="i686" (
	set "vcvars=x64_x86"
)
if /i "%architecture%"=="x86_64" (
	set "vcvars=x64"
)
if /i "%architecture%"=="arm64" (
	set "vcvars=x64_arm64"
)
if "%vcvars%"=="" (
	echo Unsupported architecture: %architecture%
	exit /b 1
)

set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%vswhere%" (
	echo Visual Studio installer not found.
	exit /b 1
)

for /f "usebackq delims=" %%I in (`"%vswhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "visualStudioPath=%%I"
if not defined visualStudioPath (
	echo Visual Studio with C++ tools not found.
	exit /b 1
)

call "%visualStudioPath%\VC\Auxiliary\Build\vcvarsall.bat" %vcvars% || exit /b 1
cl /nologo /O2 /std:c17 /DUNICODE /D_UNICODE recycle-bin.c ole32.lib uuid.lib shell32.lib /Fe:recycle-bin.exe
if %errorlevel% neq 0 exit /b 1
