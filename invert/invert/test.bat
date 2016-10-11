set PROGRAM="%~1" 

rem Детерминант матрицы равен 0
%PROGRAM% input/matrix1.txt > output/out1.txt
if %ERRORLEVEL% NEQ 1 goto err

rem Попытка запустить программу с использованием неожидаемого числа параметров
%PROGRAM% > output/out2.txt
if %ERRORLEVEL% NEQ 1 goto err

rem Попытка прочитать матрицу из несуществующего файла
%PROGRAM% input/matrix.txt > output/out3.txt
if %ERRORLEVEL% NEQ 1 goto err

rem Матрица равна ее обратной матрице
%PROGRAM% input/matrix3.txt > output/out4.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% input/matrix4.txt > output/out5.txt
if %ERRORLEVEL% EQU 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1