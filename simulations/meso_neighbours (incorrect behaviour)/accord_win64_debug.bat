@echo off
set path="%cd%\..\bin\AcCoRD2\x64\Debug"
echo Attempting to run AcCoRD [Debug Mode, 64bit, Windows] from: %path% 
%path%\AcCoRD2.exe micro_sphere_cylinder.json
PAUSE