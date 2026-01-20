@echo off
setlocal enabledelayedexpansion

set "OUTFILE=sources.inc"
echo # Automatically generated source and object lists > %OUTFILE%

:: Initialize lists
set "SRCS="
set "OBJS="
set "TPSRCS="
set "TPOBJS="
set "TSRCS="
set "TOBJS="

:: Process source\
for %%f in (source\*.cpp) do (
    set "SRCS=!SRCS! %%f"
    set "OBJS=!OBJS! build\obj\%%~nf.obj"
)

:: Process source\third_party\
for %%f in (source\third_party\*.cpp) do (
    set "TPSRCS=!TPSRCS! %%f"
    set "TPOBJS=!TPOBJS! build\obj\%%~nf.obj"
)

:: Process unit_tests\
for %%f in (unit_tests\*.cpp) do (
    set "TSRCS=!TSRCS! %%f"
    set "TOBJS=!TOBJS! build\obj\%%~nf.obj"
)

:: Write to file
echo SRCS = !SRCS! >> %OUTFILE%
echo OBJS = !OBJS! >> %OUTFILE%
echo. >> %OUTFILE%
echo THIRD_PARTY_SRCS = !TPSRCS! >> %OUTFILE%
echo THIRD_PARTY_OBJS = !TPOBJS! >> %OUTFILE%
echo. >> %OUTFILE%
echo TEST_SRCS = !TSRCS! >> %OUTFILE%
echo TEST_OBJS = !TOBJS! >> %OUTFILE%

echo File list generated in %OUTFILE%