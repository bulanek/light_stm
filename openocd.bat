set OPENOCD_DIR=C:\UserData\z003tecs\Documents\Documents\programs\OpenOCD-20200530-0.10.0
%OPENOCD_DIR%\bin\openocd.exe -s %OPENOCD_DIR%\share\openocd\scripts\ -f interface\stlink.cfg -f target\stm32f1x.cfg -c "init" -c "reset halt" -d
