@echo off
echo Updating submodules...
git submodule update --init --remote --jobs=16
echo Generating project files...
call "tools/premake5.exe" --file="lua/windows.lua" vs2022