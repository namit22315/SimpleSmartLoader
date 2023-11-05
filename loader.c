#define _GNU_SOURCE
#include "loader.h"
int count;
int k=0;
double size =0;
double pg_all = 0;
int page_allo_2=0;
double frag =0;
Elf32_Ehdr *ehdr;
Elf32_Phdr *phdr;
int fd;
int fd1;
int size1=0;
struct sigaction sa;
void loader_cleanup();
void load_elf_header(int fd);
void load_program_headers(int fd);
void map_and_run_executable(int fd);
void run_entry_point(void *entry_point);
void close_file_descriptor(int fd);
int size_of_file(int mem);
void mmap_block(int fd,int prog, int signo, siginfo_t *si);

void free_elf_header() {
    if (ehdr) {
        free(ehdr);
        ehdr = NULL;
    }
}

void free_program_headers() {
    if (phdr) {
        free(phdr);
        phdr = NULL;
    }
}


void loader_cleanup() {
    free_elf_header();
    free_program_headers();
}

int size_of_file(int mem) {
    while(1){
        size+=4096;
            if(size >= mem){
                break;
            }
        }
    return size;
}

void mmap_block(int fd,int prog, int signo, siginfo_t *si){
    void *mem = mmap(si->si_addr,size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE  | MAP_ANONYMOUS,  0,0);
    lseek(fd, prog, SEEK_SET);
    read(fd, mem, 4096);
}

void load_elf_header(int fd) {
    ehdr = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));
    if (!ehdr) {
        printf("Memory allocation error");
        close(fd);
        exit(1);
    }

    if (read(fd, ehdr, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)) {
        printf("Error reading ELF header");
        close(fd);
        exit(1);
    }
}
void segfault_handler(int signo, siginfo_t *si, void *context){


    // void *mem = mmap(si->si_addr,4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS,  fd,0);
    // lseek(fd, phdr[count].p_offset, SEEK_SET);
    // read(fd, mem, 4096);
    // printf("dfgfegfdgtrgtrtb\n");
    // struct sigaction sa1;
    //  sa1.sa_sigaction = segfault_handler;
    //  sa1.sa_flags = SA_SIGINFO;
    // void *entry_point1;
    // malloc()
    
    printf("Caught segfault at address %p\n",si->si_addr);
    double mem_alloc=0;
    for (int i = 0; i < ehdr->e_phnum; i++) {
        
        if (phdr[i].p_type == PT_LOAD) {
            // printf("mem size%d\n",phdr[i].p_memsz);
            // printf("counter: %d\n",i);
            if ((int)si->si_addr >= (int)phdr[i].p_vaddr) {
                if((int)si->si_addr < (int)(phdr[i].p_vaddr + phdr[i].p_memsz)){
                    size=size_of_file(phdr[i].p_memsz);
                    pg_all += size/4096;
                    page_allo_2 += size/4096;
                    size1+=phdr[i].p_memsz;
                    // printf("virtual add %x\n",phdr[i].p_vaddr);
                    mem_alloc=phdr[i].p_memsz;
                    // printf("mem size allocated  %d\n",phdr[i].p_memsz);
                    mmap_block(fd1,phdr[i].p_offset,signo,si);
                    k++;
                    // perror("namit21");
                    // sigaction(SIGSEGV,&sa,NULL);
                    // int result = _start();
                    // perror("namit2");
                    // printf("output: %d\n", result);
                }
            }
        }
    }

    frag+=(size-mem_alloc);
    //  entry_point1 = mem + ehdr->e_entry-si->si_addr;
    //  struct sigaction sa1;
    // sa1.sa_sigaction = segfault_handler;
    // sa1.sa_flags = SA_SIGINFO;
    
    // sigaction(SIGSEGV,&sa1,NULL);
    // run_entry_point(entry_point1);
    // perror("namit123");
    //  exit(0);
}
void load_program_headers(int fd) {
    phdr = (Elf32_Phdr *)malloc(ehdr->e_phentsize * ehdr->e_phnum);

    lseek(fd, ehdr->e_phoff, SEEK_SET);
    if (read(fd, phdr, ehdr->e_phentsize * ehdr->e_phnum) != ehdr->e_phentsize * ehdr->e_phnum) {
        printf("Error reading program headers");
        close(fd);
        exit(1);
    }
}


//not being used
void map_and_run_executable(int fd) {
        sa.sa_sigaction = segfault_handler;
    sa.sa_flags = SA_SIGINFO;
    void *entry_point;

    // run_entry_point(ehdr->e_entry);
    int (*_start)() = (int (*)())ehdr->e_entry;
    int result = _start();
     perror("namit2");
    printf("output: %d\n", result);




    for (int i = 0; i < ehdr->e_phnum; i++) {
        
        if (phdr[i].p_type == PT_LOAD) {
            if (ehdr->e_entry >= (int)(void *)phdr[i].p_vaddr) {
                if(ehdr->e_entry < (int)(void *)(phdr[i].p_vaddr + phdr[i].p_memsz)){
                    count = i;
                    // void *mem = mmap(si->si_addr,4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_FIXED, fd,phdr[i].p_offset);
                    // void *mem = mmap(si->si_addr,4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS,  fd,phdr[i].p_offset);
                    printf("%x\n",phdr[i].p_vaddr);
                    printf("%x\n",phdr[i].p_offset);
                    printf("%dfd\n",fd);
                    // lseek(fd, phdr[i].p_offset, SEEK_SET);
                    // read(fd, mem, 4096);
                    // printf("segment data not read successfully");
                    // close(fd);
                    // exit(1);
                    int result;
                    while(k==1){
                        sigaction(SIGSEGV,&sa,NULL);
                    
                    perror("namit21");
                    // sigaction(SIGSEGV,&sa,NULL);
                    // sleep(5);
                    int (*_start)() = (int (*)())(ehdr->e_entry);
                    result = _start();
                    printf("\n%d\n",count);
                    }
                    int k=0;
                    perror("namit2");
                    printf("output: %d\n", result);
                }
            }
        }
    }







    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type == PT_LOAD) {
            if (ehdr->e_entry >= (int)(void *)phdr[i].p_vaddr) {
                if(ehdr->e_entry < (int)(void *)(phdr[i].p_vaddr + phdr[i].p_memsz)){
                void *mem = mmap((void *)phdr[i].p_vaddr, phdr[i].p_memsz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_FIXED, fd, phdr[i].p_offset);
                entry_point = mem + ehdr->e_entry - phdr[i].p_vaddr;
                if (mem == MAP_FAILED) {
                    printf("Memory mapping error");
                    close(fd);
                    exit(1);
                }
                lseek(fd, phdr[i].p_offset, SEEK_SET);
                if (read(fd, mem, phdr[i].p_filesz) != phdr[i].p_filesz) {
                    printf("segment data not read successfully");
                    close(fd);
                    exit(1);
                }
                run_entry_point(entry_point);
            }
            }
        }
    }
}

void run_entry_point(void *entry_point) {

    perror("namit987");
    int (*_start)() = (int (*)())entry_point;
        perror("namit1");
    struct sigaction sa1;
    sa1.sa_sigaction = segfault_handler;
    sa1.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV,&sa1,NULL);
    run_entry_point(entry_point);
    struct sigaction sa2;
    sa2.sa_sigaction = segfault_handler;
    sa2.sa_flags = SA_SIGINFO;
    
    sigaction(SIGSEGV,&sa2,NULL);
    int result = _start();
     perror("namit2");
    printf("output: %d\n", result);
}

void close_file_descriptor(int fd) {
    close(fd);
}

void load_and_run_elf(char **exe) {
     fd = open(exe[1], O_RDONLY);
    // printf("%dfd\n",fd);
    if (fd == -1) {
        printf("Error opening file");
        exit(1);
    }

    load_elf_header(fd);
    load_program_headers(fd);
    // map_and_run_executable(fd);
    // close_file_descriptor(fd);
}

int main(int argc, char **argv) {
       
    sa.sa_sigaction = segfault_handler;
    sa.sa_flags = SA_SIGINFO;
    fd1 = open(argv[1], O_RDONLY);
    sigaction(SIGSEGV,&sa,NULL);
    load_and_run_elf(argv);
    int (*_start)() = (int (*)())ehdr->e_entry;
    int result = _start();
    //  perror("namit2");
    printf("output: %d\n", result);
    // loader_cleanup();
    //  printf("size: %d\n",size);
    //  printf("size1: %d\n",size1);
     printf("Number of Page Fault: %d\n",k);
     printf("Number of allocated pages %d\n",page_allo_2);
     printf("Fragmented memory size in KB: %f\n",frag/1024);
     close_file_descriptor(fd);
     close_file_descriptor(fd1);
     loader_cleanup();
    return 0;
}