@echo off
del Makefile*
cd %cd%\release\
del *.*
cd ../
rd /s /q  debug
rd /s /q  release
@echo on
CALL "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" amd64_x86
echo vcvarsall finished
qmake
jom.exe -f Makefile.Release
