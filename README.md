# SimpleSmartLoader Readme

## Introduction

This C code represents an ELF (Executable and Linkable Format) file loader, designed to load and execute ELF binary files. ELF is a common format used for executable and shared library files on Unix-like systems.

The code is structured into several functions and performs the following key tasks:

1. Load ELF Header
2. Load Program Headers
3. Handle Segmentation Faults
4. Memory Map the segment causing the fault
5. Close File Descriptor


The loader is designed to read ELF files, map their program segments into memory, and execute them. The code also includes a signal handler for segmentation faults, which allows handling memory mapping and execution issues gracefully.

## Code Structure

The code consists of several functions and a main function:

- loader_cleanup(): Cleans up allocated memory for the ELF header and program headers.

- load_elf_header(int fd): Loads the ELF header from the given file descriptor fd.

- segfault_handler(int signo, siginfo_t *si, void *context): Signal handler to handle segmentation faults during execution.

- load_program_headers(int fd): Loads the program headers from the ELF file using the given file descriptor fd.

- run_entry_point(void *entry_point): Executes the ELF binary at the specified entry point.

- mmap_block(int fd,int prog, int signo, siginfo_t *si) : Maps the segment into memory.

- close_file_descriptor(int fd): Closes the file descriptor.

- load_and_run_elf(char **exe): The main function that opens the ELF file, loads the ELF header and program headers, and executes the binary.

## Usage

To use this ELF loader, you can compile the code and run it with the ELF binary as a command-line argument:

1. make
2. ./loader <file_name>


## Segmentation Fault Handling

The code includes a signal handler for segmentation faults (SIGSEGV). When a segmentation fault occurs, the handler attempts to map the missing memory segment and re-run the ELF binary. The segfault_handler and mmap_block functions are responsible for this behavior.

## Contributions

Namit Jain (2022315)
Load ELF Header Function
Load Program Header Function
Run Entry Point Function
Segmentation Fault Handler
Optimization and Debugging

Pranav Tanwar (2022368)
Cleanup Functions
Memory Mapping Function
Segmentation Fault Handler
Optimization and Debugging

## Github Link

https://github.com/namit22315/OS-ASSIGNMENT-4