@echo off
cd /d %~dp0
devtools\bin\vpc.exe +shaderapi /mksln shaderapivk.sln /f
PAUSE