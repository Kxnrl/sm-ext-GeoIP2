echo "Set environment"
set EXT_DIR=%cd%
set DEP_DIR=%EXT_DIR%\build-windows
set VCVARSALL="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"

git fetch --unshallow
git rev-list --count HEAD > gitcommit.txt
set /p GITCOMMIT=<gitcommit.txt
mkdir "%DEP_DIR%"

cd %DEP_DIR%

if "%VSCMD_VER%"=="" (
	set MAKE=
	set CC=
	set CXX=
	call %VCVARSALL% x86 8.1
)

:: Install ambuild
echo "Install ambuild"
git clone https://github.com/alliedmodders/ambuild
pushd ambuild
python setup.py install
popd

:: Getting sourcemod

echo "Download sourcemod"
git clone https://github.com/alliedmodders/sourcemod --recursive --branch %SMBRANCH% --single-branch sourcemod

pushd sourcemod
set SOURCEMOD=%cd%
popd

:: Start build

echo "Build"
cd %EXT_DIR%

mkdir build
pushd build
python "%EXT_DIR%/configure.py" --enable-optimize --sm-path "%SOURCEMOD%"
ambuild
popd
