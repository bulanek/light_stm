echo "00 00 ff 02 fd 00 ff 00 ff 00 ff" | xxd -r -p > option_bytes.bin
stm8flash -c stlinkv2 -p stm8s003f3 -s opt -w option_bytes.bin
stm8flash -c stlinkv2 -p stm8s003f3 -s flash -w voliera.ihx
