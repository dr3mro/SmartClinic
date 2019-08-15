set month=%date:~4,2%
set day=%date:~7,2%
set year=%date:~10,4%
set var=%year%%month%%day%
echo %var%
echo #ifndef BUILD > ../../SmartClinic/qtemr/build.h
echo #define BUILD %var% >> ../../SmartClinic/qtemr/build.h
echo #endif >> ../../SmartClinic/qtemr/build.h
echo %var%
