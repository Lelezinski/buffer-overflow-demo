# Buffer Overflow Exploit Demo
OSES 2022-23 Group Project: Buffer Overflow Exploit (Priviledge Escalation)

# Main Steps
- Disable **ASLR** (Address Space Layout Randomization) and **DEP** (Data Execution Prevention):
```
$> echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
$> gcc -fno-stack-protector -z execstack program.c -o program
```
- **Fuzz** the input to know the offset for the buffer overflow within this input.
- Build the input **payload** to execute the exploit.
- Insert the malicius payload as input of the vulnerable program to check its correctness.
