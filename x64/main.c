// gcc main.c -o heaven64 -no-pie
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <asm/unistd_32.h>

static int _x86_32_on_x64(int syscall, void* arg1, void* arg2, void* arg3) {
    int returnval;
    asm ( "int $0x80"
        : "=a" (returnval)
        : "a"(syscall), "b"(arg1), "c"(arg2), "d"(arg3));
    return returnval;
}

int main() {
    printf("[!] Heaven's Gate, calling x32 syscalls on x64 programs\n");

    char *buf = mmap(0, 2048, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0 );
    if (buf == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
    printf("32 bit memory allocated at %p \n", buf);
    strcpy(buf, "Hello from 32-bit world!\n");

    _x86_32_on_x64(__NR_write, 1, buf, 26);

}

