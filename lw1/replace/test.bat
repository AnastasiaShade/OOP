set PROGRAM="%~1"

rem empty file test
%PROGRAM% empty.txt %TEMP%\empty-out.txt "first string" "second string string"
if %ERRORLEVEL% NEQ 1 goto err

rem one line test
%PROGRAM% one-line.txt %TEMP%\one-line-out.txt "the" "a"
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\one-line-out.txt one-line.txt
if %ERRORLEVEL% EQU 0 goto err

rem one line test with empty input string
%PROGRAM% one-line.txt %TEMP%\one-line-out.txt "" "a"
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\one-line-out.txt one-line.txt
if %ERRORLEVEL% EQU 0 goto err

rem 1231234 test
%PROGRAM% 1231234.txt %TEMP%\1231234.txt "1231234" "6"
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\one-line-multiword.txt one-line-multiword.txt
if %ERRORLEVEL% EQU 0 goto err

rem multiline multiword test
%PROGRAM% multiline-multiword.txt %TEMP%\multiline-multiword-out.txt "one" "two"
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\multiline-multiword.txt multiline-multiword-out.txt
if %ERRORLEVEL% EQU 0 goto err

rem mama test
%PROGRAM% ma.txt %TEMP%/ma-out.txt "ma" "mama"
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\ma.txt ma-out.txt
if %ERRORLEVEL% EQU 0 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1