# Buffer Overflow Exploit Demo
OSES 2022-23 Group Project: Buffer Overflow Exploit (Priviledge Escalation)

# Main Steps
- Disable **ASLR** (Address Space Layout Randomization) and **DEP** (Data Execution Prevention):
```
$> echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
$> gcc -fno-stack-protector -z execstack vulnerable.c -o vulnerable
```
- **Fuzz** the input of the vulnerable program to know the buffer size **BUFSIZE**.
- Build the **input** (containing the _NOP Sled_, _shell payload_ and return address) to execute the exploit.
- Run the vulnerable program using the previously built input.
- Repeat the test changing the **return address** (adding an offset of BUFSIZE byte each time) inside the payload until the function returns inside the _NOP Sled_, eventually running the _shell payload_.

# Credits
Group n.03:
- Lorenzo Ruotolo, s313207
- [...]
- [...]
- [...]