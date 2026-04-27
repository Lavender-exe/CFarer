// CFarer - Linux Internals Exercise 09
// TOPIC: ELF Binary Parsing - headers, segments, sections
// DIFFICULTY: Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / binary analysis
//
// ELF (Executable and Linkable Format) is the binary format on Linux/Unix.
// Structure:
//   Elf64_Ehdr   - file header (magic, type, machine, entry point, phoff, shoff)
//   Elf64_Phdr[] - program headers (segments for loader: LOAD, INTERP, DYNAMIC)
//   Elf64_Shdr[] - section headers (for linker/debugger: .text, .data, .symtab)
//
// Task (parse /proc/self/exe - the running executable):
//   1. open("/proc/self/exe", O_RDONLY) -> fd
//   2. read(fd, &ehdr, sizeof(ehdr)) - read ELF header.
//   3. Verify magic: ehdr.e_ident[0..3] == "\x7fELF"
//   4. Print: e_type, e_machine, e_entry, e_phnum, e_shnum.
//   5. lseek to e_phoff, read all e_phnum program headers.
//   6. For each PT_LOAD segment: print p_vaddr, p_filesz, p_flags (RWX bits).
//   7. close(fd).

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <string.h>

int main(void) {
    // TODO 1: open("/proc/self/exe", O_RDONLY)
    int fd = -1; // replace
    if (fd < 0) {
        perror("open /proc/self/exe");
        return 1;
    }

    Elf64_Ehdr ehdr;
    // TODO 2: read(fd, &ehdr, sizeof(ehdr))
    // ssize_t n = read(fd, &ehdr, sizeof(ehdr));

    // TODO 3: verify ELF magic
    // if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
    //     fprintf(stderr, "not an ELF file\n");
    //     close(fd);
    //     return 1;
    // }

    // TODO 4: print header info
    printf("e_type:   %u  (ET_EXEC=2, ET_DYN=3)\n", ehdr.e_type);
    printf("e_machine:%u  (EM_X86_64=62)\n",         ehdr.e_machine);
    printf("e_entry:  0x%llx\n", (unsigned long long)ehdr.e_entry);
    printf("e_phnum:  %u program headers\n",          ehdr.e_phnum);
    printf("e_shnum:  %u section headers\n",          ehdr.e_shnum);

    // TODO 5: lseek to program headers and read them
    // lseek(fd, ehdr.e_phoff, SEEK_SET);
    Elf64_Phdr phdr;
    printf("\nPT_LOAD segments:\n");
    for (int i = 0; i < ehdr.e_phnum; i++) {
        // read(fd, &phdr, sizeof(phdr));
        // TODO 6: if PT_LOAD, print vaddr, filesz, flags
        // if (phdr.p_type == PT_LOAD) {
        //     printf("  vaddr=0x%llx filesz=0x%llx flags=%c%c%c\n",
        //            (unsigned long long)phdr.p_vaddr,
        //            (unsigned long long)phdr.p_filesz,
        //            (phdr.p_flags & PF_R) ? 'R' : '-',
        //            (phdr.p_flags & PF_W) ? 'W' : '-',
        //            (phdr.p_flags & PF_X) ? 'X' : '-');
        // }
        (void)phdr;
    }

    // TODO 7: close(fd)
    return 0;
}

// I AM NOT DONE
