@echo off
set /p var= < ../../SmartClinic/qtemr/build.txt
set /a var= %var%+1
echo %var% > ../../SmartClinic/qtemr/build.txt
echo #ifndef BUILD > ../../SmartClinic/qtemr/build.h
echo #define BUILD %var% >> ../../SmartClinic/qtemr/build.h
echo #endif >> ../../SmartClinic/qtemr/build.h
echo %var%
