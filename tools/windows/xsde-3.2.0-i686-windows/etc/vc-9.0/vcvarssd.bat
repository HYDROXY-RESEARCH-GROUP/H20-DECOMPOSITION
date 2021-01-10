@echo off
REM 
REM This .bat file sets the environment variables for Visual Studio
REM 2008 Smart Devices toolchain to allow compilation from the command
REM line or with nmake. Make sure the following four variables are
REM set to the correct values.
REM 

REM 
REM Make sure VSINSTALLDIR points to the Visual Studio 2008 installation
REM directory.
REM 
SET VSINSTALLDIR=C:\Program Files\Microsoft Visual Studio 9.0

REM 
REM Set the toolchain to use. See VSINSTALLDIR\VC\ce\bin for possible
REM values.
REM 
SET TOOLCHAIN=x86_arm

REM 
REM C/C++ runtime to use. See VSINSTALLDIR\VC\ce\lib for possible
REM values.
REM 
SET RUNTIME=armv4

REM 
REM Platform SDK to use. See VSINSTALLDIR\SmartDevices\SDK for 
REM what's available (normally PocketPC2003 and Smartphone2003).
REM 
SET SDK=PocketPC2003

title Visual Studio 2008 Smart Devices Environment for %SDK% on %RUNTIME% 
echo Setting environment for Visual Studio 2008 Smart Devices.

SET VCINSTALLDIR=%VSINSTALLDIR%\VC
SET PATH=%VCINSTALLDIR%\ce\BIN\%TOOLCHAIN%;%VCINSTALLDIR%\BIN;%VSINSTALLDIR%\Common7\IDE;%VSINSTALLDIR%\Common7\Tools;%VSINSTALLDIR%\Common7\Tools\bin;%PATH%
SET INCLUDE=%VCINSTALLDIR%\CE\ATLMFC\INCLUDE;%VCINSTALLDIR%\CE\INCLUDE;%VSINSTALLDIR%\SmartDevices\SDK\%SDK%\include;%INCLUDE%
SET LIB=%VCINSTALLDIR%\CE\ATLMFC\LIB\%RUNTIME%;%VCINSTALLDIR%\CE\LIB\%RUNTIME%;%VSINSTALLDIR%\SmartDevices\SDK\%SDK%\lib\%RUNTIME%;%LIB%
