@echo off
set path="%cd%\..\..\bin\AcCoRD2\x64\Release"
echo Attempting to run AcCoRD [Release Mode, 64bit, Windows] from: %path% 
%path%\AcCoRD2.exe config.json
PAUSE