sdcc  -mstm8 -o stm8s_gpio.rel -c stm8s_gpio.c  -L/usr/share/sdcc/lib/stm8/ -lstm8 -I/usr/share/sdcc/include/stm8/  -I ../include/ -I /home/boris/programy/stm8s-sdcc/inc -DSTM8S003 --verbose
sdcc  -mstm8 -o stm8s_flash.rel -c stm8s_flash.c  -L/usr/share/sdcc/lib/stm8/ -lstm8 -I/usr/share/sdcc/include/stm8/  -I ../include/ -I /home/boris/programy/stm8s-sdcc/inc -DSTM8S003 --verbose
sdcc  -mstm8 -o main.rel -c main.c  -L/usr/share/sdcc/lib/stm8/ -lstm8 -I/usr/share/sdcc/include/stm8/  -I ../include/ -I /home/boris/programy/stm8s-sdcc/inc -DSTM8S003 --verbose

sdcc -mstm8  stm8s_gpio.rel stm8s_flash.rel main.rel -o voliera.ihx --out-fmt-ihx -L/usr/share/sdcc/lib/stm8/ -lstm8 -I/usr/share/sdcc/include/stm8 -DSTM8S003 -I../include --verbose
