// gcc main.c asm.S -o main32 -no-pie
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <asm/unistd_64.h>
#include <stdint.h>

typedef unsigned long long u64;
extern void _call_64_from_32(void *args);

u64 x64_syscall(u64 syscall, void* arg1, void* arg2, void* arg3)
{
    u64 registers[8];
    registers[0] = syscall;
    registers[1] = arg1;
    registers[2] = arg2;
    registers[3] = arg3;
    registers[4] = registers[5] = registers[6] = registers[7];
    _call_64_from_32(registers);
    return registers[7];
}

int main() {
    printf("[!] Heaven's Gate, calling x64 syscalls on x32 programs\n");

    char *buf = mmap(0, 2048, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
    if (buf == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
    printf("32 bit memory allocated at %p \n", buf);
    strcpy(buf, "Hello from 32-bit world!\n");

    x64_syscall(__NR_write, 1, buf, 26);

}

