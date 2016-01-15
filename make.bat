@echo off
cls
echo Removing previous binary
del bin.exe >> compile.log
echo Started build...
echo ################
cd "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin"
g++ -std=c++11 "C:\Users\Misterkat\Documents\GitHub\Tree\main.cpp" -o "C:\Users\Misterkat\Documents\GitHub\Tree\bin.exe"
echo Executing...
echo ################
cd "C:\Users\Misterkat\Documents\GitHub\Tree\"
bin.exe
