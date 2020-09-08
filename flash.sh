echo "00" | xxd -r -p > option_bytes.bin
stm8flash -c stlinkv2 -p stm8l152x4 -s opt -w option_bytes.bin
stm8flash -c stlinkv2 -p stm8l152x4 -s flash -w LIGHT.ihx
