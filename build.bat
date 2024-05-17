@echo off
setlocal

set MODE= %1%
set CC= cl

set CFLAGS_R= /std:c17 /O2
set CFLAGS_D= /std:c17 /Od /Zi /W4

if "%MODE%"==" d" (
  pushd debug
  %CC% %CFLAGS_D% ..\src\_target.c /Feshadertoh.exe
  popd
) else (
  %CC% %CFLAGS_R% /O2 src\_target.c /Feshadertoh.exe
  del _target.obj
)
