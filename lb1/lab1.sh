@ECHO OFF
CLS
IF -%1==- GOTO NoParam
IF -%2==- GOTO NoParam
IF -%3==- GOTO NoParam
ECHO Iz kataloga %1 faili rashireniem %2 v katalog %3
XCOPY %1\*.%2 %3\ /Y /S /Q
GOTO :eof
:NoParam
ECHO ne vse peremen est 
PAUSE 