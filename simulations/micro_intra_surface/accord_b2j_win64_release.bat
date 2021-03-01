@echo off
set path="%cd%\..\..\bin\AcCoRD2_B2J\x64\Release"
echo Attempting to run AcCoRD [Release Mode, 64bit, Windows] from: %path% 
%path%\AcCoRD2_B2J.exe %cd%
PAUSE