@echo off
set path="%cd%\..\..\bin\AcCoRD2\x64\Release"
echo Attempting to run AcCoRD [Release Mode, 64bit, Windows] with seed %1 from: 
echo %path% 
%path%\AcCoRD2.exe config.json %1