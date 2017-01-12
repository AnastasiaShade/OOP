set PROGRAM="%~1" 

rem ����������� ������� ����� 0
%PROGRAM% input/matrix1.txt > output/out1.txt
if %ERRORLEVEL% NEQ 1 goto err

rem ������� ��������� ��������� � �������������� ������������ ����� ����������
%PROGRAM% > output/out2.txt
if %ERRORLEVEL% NEQ 1 goto err

rem ������� ��������� ������� �� ��������������� �����
%PROGRAM% input/matrix.txt > output/out3.txt
if %ERRORLEVEL% NEQ 1 goto err

rem ������� ����� �� �������� �������
%PROGRAM% input/matrix3.txt > output/out4.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% input/matrix4.txt > output/out5.txt
if %ERRORLEVEL% EQU 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1