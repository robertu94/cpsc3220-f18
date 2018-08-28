Good afternoon everyone,

Sorry about the various technology problems that we had today.  I wanted to
take a few minutes to summarize the key points from todays lecture that we
would have covered more coherently if I could have demo'ed from the front as
intended.  Generally speaking, classes are organized around a series of
detailed examples. This class is no exception.  For those who asked for a
PowerPoint or slides.  You can think of the source code files as our slides.

#hello_world

The purpose of this file was to look at the concept of a system call.  A
system call is the interface between user programs and the kernel.  Library
functions such as `printf` in turn call system calls such as `write` to do
their jobs.

We talked about `objdump` and linking and looked at the output of `objdump -t ./hello_world`

```
./hello_world:     file format elf64-x86-64

SYMBOL TABLE:
0000000000000238 l    d  .interp	0000000000000000              .interp
0000000000000254 l    d  .note.ABI-tag	0000000000000000              .note.ABI-tag
0000000000000278 l    d  .gnu.hash	0000000000000000              .gnu.hash
0000000000000298 l    d  .dynsym	0000000000000000              .dynsym
0000000000000370 l    d  .dynstr	0000000000000000              .dynstr
000000000000043a l    d  .gnu.version	0000000000000000              .gnu.version
0000000000000450 l    d  .gnu.version_r	0000000000000000              .gnu.version_r
00000000000004a0 l    d  .rela.dyn	0000000000000000              .rela.dyn
0000000000000560 l    d  .rela.plt	0000000000000000              .rela.plt
00000000000005a8 l    d  .init	0000000000000000              .init
00000000000005c0 l    d  .plt	0000000000000000              .plt
0000000000000600 l    d  .plt.got	0000000000000000              .plt.got
0000000000000610 l    d  .text	0000000000000000              .text
00000000000007e4 l    d  .fini	0000000000000000              .fini
00000000000007f0 l    d  .rodata	0000000000000000              .rodata
000000000000080c l    d  .eh_frame_hdr	0000000000000000              .eh_frame_hdr
0000000000000848 l    d  .eh_frame	0000000000000000              .eh_frame
0000000000200de8 l    d  .init_array	0000000000000000              .init_array
0000000000200df0 l    d  .fini_array	0000000000000000              .fini_array
0000000000200df8 l    d  .dynamic	0000000000000000              .dynamic
0000000000200fd8 l    d  .got	0000000000000000              .got
0000000000201000 l    d  .got.plt	0000000000000000              .got.plt
0000000000201030 l    d  .data	0000000000000000              .data
0000000000201040 l    d  .bss	0000000000000000              .bss
0000000000000000 l    d  .comment	0000000000000000              .comment
0000000000000000 l    d  .debug_aranges	0000000000000000              .debug_aranges
0000000000000000 l    d  .debug_info	0000000000000000              .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000              .debug_abbrev
0000000000000000 l    d  .debug_line	0000000000000000              .debug_line
0000000000000000 l    d  .debug_str	0000000000000000              .debug_str
0000000000000000 l    d  .debug_loc	0000000000000000              .debug_loc
0000000000000000 l    df *ABS*	0000000000000000              hello_world.c
0000000000000000 l    df *ABS*	0000000000000000              elf-init.c
0000000000000000 l    df *ABS*	0000000000000000              
0000000000200df0 l       .init_array	0000000000000000              __init_array_end
0000000000200df8 l     O .dynamic	0000000000000000              _DYNAMIC
0000000000200de8 l       .init_array	0000000000000000              __init_array_start
000000000000080c l       .eh_frame_hdr	0000000000000000              __GNU_EH_FRAME_HDR
0000000000201000 l     O .got.plt	0000000000000000              _GLOBAL_OFFSET_TABLE_
00000000000007e0 g     F .text	0000000000000001              __libc_csu_fini
0000000000000000  w      *UND*	0000000000000000              _ITM_deregisterTMCloneTable
0000000000201030  w      .data	0000000000000000              data_start
0000000000201040 g       .data	0000000000000000              _edata
00000000000007e4 g     F .fini	0000000000000000              _fini
0000000000000000       F *UND*	0000000000000000              __stack_chk_fail@@GLIBC_2.4
0000000000000000       F *UND*	0000000000000000              __libc_start_main@@GLIBC_2.2.5
0000000000201030 g       .data	0000000000000000              __data_start
0000000000000000  w      *UND*	0000000000000000              __gmon_start__
0000000000201038 g     O .data	0000000000000000              .hidden __dso_handle
00000000000007f0 g     O .rodata	0000000000000004              _IO_stdin_used
0000000000000780 g     F .text	000000000000005d              __libc_csu_init
0000000000201048 g       .bss	0000000000000000              _end
0000000000000670 g     F .text	000000000000002b              _start
0000000000201040 g       .bss	0000000000000000              __bss_start
0000000000000610 g     F .text	0000000000000060              main
0000000000000000       F *UND*	0000000000000000              __printf_chk@@GLIBC_2.3.4
0000000000000000       F *UND*	0000000000000000              __isoc99_scanf@@GLIBC_2.7
0000000000201040 g     O .data	0000000000000000              .hidden __TMC_END__
0000000000000000  w      *UND*	0000000000000000              _ITM_registerTMCloneTable
0000000000000000  w    F *UND*	0000000000000000              __cxa_finalize@@GLIBC_2.2.5
00000000000005a8 g     F .init	0000000000000000              _init
```

I mentioned that the following sections were important for this class:

1. `.bss` where uninitialized global data is defined.  It is zero initialized at program exec
2. `.text` where the executable code of the program is defined.  `main` is one
	 such important section of `.text`
3. `.rodata` is where readonly data is stored.
4. `.data` is where read/writable data is stored.

We looked at the output of `ltrace ./hello_world <<<"me"`

which looked something like this:

```
__isoc99_scanf(0x55f296ddc7f4, 0x7fff92dad93e, 0x7fff92dada48, 0) = 1
__printf_chk(1, 0x55f296ddc7f9, 0x7fff92dad93e, 0x7fcbbab448b0) = 15
hello world me
+++ exited (status 0) +++
```

We observe that we saw the familiar `scanf` and `printf`  library functions (not system calls) that we are
familiar with.

Then we looked at the output of `strace ./hello_world <<<"me"`

which looked something like this:

```
execve("./hello_world", ["./hello_world"], 0x7ffe79bf6b90 /* 64 vars */) = 0
brk(NULL)                               = 0x55c012e2e000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=263747, ...}) = 0
mmap(NULL, 263747, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f8c1c36c000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000\21\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1832808, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8c1c36a000
mmap(NULL, 3938776, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f8c1bdc7000
mprotect(0x7f8c1bf80000, 2093056, PROT_NONE) = 0
mmap(0x7f8c1c17f000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b8000) = 0x7f8c1c17f000
mmap(0x7f8c1c185000, 14808, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f8c1c185000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7f8c1c36b500) = 0
mprotect(0x7f8c1c17f000, 16384, PROT_READ) = 0
mprotect(0x55c0111cd000, 4096, PROT_READ) = 0
mprotect(0x7f8c1c3ad000, 4096, PROT_READ) = 0
munmap(0x7f8c1c36c000, 263747)          = 0
fstat(0, {st_mode=S_IFREG|0600, st_size=3, ...}) = 0
brk(NULL)                               = 0x55c012e2e000
brk(0x55c012e4f000)                     = 0x55c012e4f000
read(0, "me\n", 4096)                   = 3
fstat(1, {st_mode=S_IFREG|0644, st_size=1602, ...}) = 0
write(1, "hello world me\n", 15hello world me
)        = 15
lseek(0, -1, SEEK_CUR)                  = 2
exit_group(0)                           = ?
+++ exited with 0 +++
```

We observed the following key system calls and talked briefly about their
function:

+	`execve` starts new programs
+	`openat` opens a file
+	`close` closes a file
+	`mmap` maps memory for the program to use
+	`mprotect` sets memory protections
+	`fstat` gets information about files
+	`write` writes to file
+	`read` reads from a file

I remarked that `read`, `write`, and `execve` were the most important ones to
know for the time being and you **should know what they do** and **what their
arguments are**.  You can find more information on these calls by
looking at their man pages on linux like so:

```
man 2 read
man 2 write
man 2 execve
```

Section 2 of the manual has information on system calls.


#hello_world_cpp

We talked about what hello world looks like in c++

First we looked at the output of `ltrace ./hello_world_cpp <<<"me"`


```
_ZNSt8ios_base4InitC1Ev(0x56279cf68299, 0x7ffe52ebf728, 0x7ffe52ebf738, 0) = 0
__cxa_atexit(0x7fa1470f45e0, 0x56279cf68299, 0x56279cf68058, 6) = 0
_ZStrsIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RNSt7__cxx1112basic_stringIS4_S5_T1_EE(0x56279cf68180, 0x7ffe52ebf610, 0x7ffe52ebf738, 0) = 0x56279cf68180
_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(0x56279cf68060, 0x56279cd67bb4, 12, 0) = 0x56279cf68060
_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(0x56279cf68060, 0x7ffe52ebf620, 2, 0) = 0x56279cf68060
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_(0x56279cf68060, 0x7fa146ac68a0, 0, 0hello world me
) = 0x56279cf68060
+++ exited (status 0) +++
```

I was going to make a comment about name mangling which was omitted.
Essentially because of issues with name collisions caused by overloading in
c++ you need to use `ltrace -C` instead to get human readable names:

```
std::ios_base::Init::Init()(0x55af5b34f299, 0x7fffb595b048, 0x7fffb595b058, 0) = 0
__cxa_atexit(0x7fb2321ff5e0, 0x55af5b34f299, 0x55af5b34f058, 6) = 0
std::basic_istream<char, std::char_traits<char> >& std::operator>><char, std::char_traits<char>, std::allocator<char> >(std::basic_istream<char, std::char_traits<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&)(0x55af5b34f180, 0x7fffb595af30, 0x7fffb595b058, 0) = 0x55af5b34f180
std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)(0x55af5b34f060, 0x55af5b14ebb4, 12, 0) = 0x55af5b34f060
std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)(0x55af5b34f060, 0x7fffb595af40, 2, 0) = 0x55af5b34f060
std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)(0x55af5b34f060, 0x7fb231bd18a0, 0, 0hello world me
) = 0x55af5b34f060
+++ exited (status 0) +++
```

The strace looks largely the same: `strace ./hello_world_cpp <<<"me"`

```

execve("./hello_world_cpp", ["./hello_world_cpp"], 0x7ffc2ea0e340 /* 64 vars */) = 0
brk(NULL)                               = 0x557263fd4000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=263747, ...}) = 0
mmap(NULL, 263747, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f19818ca000
close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/8.2.0/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260.\t\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2113520, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f19818c8000
mmap(NULL, 4222016, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f19812e0000
mprotect(0x7f19814d4000, 2093056, PROT_NONE) = 0
mmap(0x7f19816d3000, 69632, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1f3000) = 0x7f19816d3000
mmap(0x7f19816e4000, 11328, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f19816e4000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`w\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1350384, ...}) = 0
mmap(NULL, 3445480, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f1980f96000
mprotect(0x7f19810de000, 2097152, PROT_NONE) = 0
mmap(0x7f19812de000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x148000) = 0x7f19812de000
close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/8.2.0/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`*\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=96400, ...}) = 0
mmap(NULL, 2192432, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f1980d7e000
mprotect(0x7f1980d95000, 2093056, PROT_NONE) = 0
mmap(0x7f1980f94000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x16000) = 0x7f1980f94000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000\21\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1832808, ...}) = 0
mmap(NULL, 3938776, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f19809bc000
mprotect(0x7f1980b75000, 2093056, PROT_NONE) = 0
mmap(0x7f1980d74000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b8000) = 0x7f1980d74000
mmap(0x7f1980d7a000, 14808, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f1980d7a000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f19818c6000
arch_prctl(ARCH_SET_FS, 0x7f19818c6f00) = 0
mprotect(0x7f1980d74000, 16384, PROT_READ) = 0
mprotect(0x7f1980f94000, 4096, PROT_READ) = 0
mprotect(0x7f19812de000, 4096, PROT_READ) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f19818c4000
mprotect(0x7f19816d3000, 53248, PROT_READ) = 0
mprotect(0x557262430000, 4096, PROT_READ) = 0
mprotect(0x7f198190b000, 4096, PROT_READ) = 0
munmap(0x7f19818ca000, 263747)          = 0
brk(NULL)                               = 0x557263fd4000
brk(0x557263ff5000)                     = 0x557263ff5000
fstat(0, {st_mode=S_IFREG|0600, st_size=3, ...}) = 0
read(0, "me\n", 4096)                   = 3
fstat(1, {st_mode=S_IFREG|0644, st_size=3632, ...}) = 0
write(1, "hello world me\n", 15hello world me
)        = 15
lseek(0, -1, SEEK_CUR)                  = 2
exit_group(0)                           = ?
+++ exited with 0 +++
```

The key difference boiling down to some additional share libraries being
loaded.

#hello_world_syscall

Next we looked at the glibc wrapper for the write syscall, the interface that
things like `printf` are implemented in terms of.  We talked about how glibc's
write function is just a thin wrapper around some assembly that we would look
at next.

#hello_world_syscall_asm

After that, we looked at the syntax that actual GCC uses to implement write.

We talked about that the meanings of the various feilds

| field  | purpose                                                                                     |
| ------ | --------------------------------------------------------------------------------------------|
| 1      | instruction template in either att or intel syntax                                          |
| 2      | output registers, this one says use eax/rax                                                 |
| 3      | input registers, explained below                                                            |
| 4      | clobbers, an address is read (memory) and the rcx register which is used for the kernel     |

You won't need to know which clobbers or specific values are passed to the assembly template.

The input registers for system calls for the x86\_64  (read: the only ones I'd consider testing
you on) are:

+	rax -- the number of the system call to be called.
+ rdi -- the 1st argument to the systemcall
+	rsi -- the 2nd argument to the systemcall
+	rdx -- the 3rd argument to the systemcall.

We then talked about how a system call actual occurs:

On x86\_64, system calls are triggered using the `syscall` instruction.  Which
is itself **NOT** an interrupt.  On x86 (32 bit) system calls are triggered by
using the `int` (interrupt) instruction with the value `0x80`.

When a **system call** occurs, the processor preforms a **context switch** into kernel
mode.  This mode has additional access to hardware resources not available
generally to the user mode.  We mentioned that the kernel has a separate stack
and heap that are only accessible in kernel mode and these are switched to and
from when context switching.

We also talked about **interrupts**.  There are 3 major sources of interrupts:

1. IO -- i.e. the user presses a button on the keyboard
2. Timers -- the processor has a timer used to switch between processes -- more on that soon.
3. System calls (on 32 bit machines)

So in short,

+	All system calls involve context switches, but not all context switches are system calls.
+	All interrupts involve a context switch, but not all context switches are interrupts.

We mentioned an exception to hardware only being accessible from kernel mode
from high performance computing called infiniband which you will NOT be tested
on.  Infiniband does kernel bypass networking.


#rawsyscall

In this file we looked at the more accessible way to call system calls.

I mentioned that every program has at least the 3 following file descriptors:

+ 0 -- stdin
+ 1 -- stdout
+ 2 -- stderr

I mentioned that `exit` is system call 60.
I mentioned that `mov` loads a value to a register.
I mentioned that `xor %rdi %rdi` zeros the rdi register.

I made the remark that write is system call 1, and that you should know about
the file `arch/x86/entry/syscalls/syscall_64.tbl` because it will be important
for the 4th project, but you won't need it now.  I also mentioned this file
may be important because it tells you how many system calls exist which will
be helpful on the first project.

We wrapped up this section with a bunch of questions.

#shim_test

We then went on to look at shims and dynamic loading which will be a key part
of project 1.  Shim test is a file that just prints a random value by calling
`rand`.  I mentioned that rand returns an integer between 0 and RAND\_MAX.  I
mentioned that `rand` is provided by dynamic linking with glibc.

#shim

We looked at the shim, and I pointed out 3 things:

1. the `__attribute__((constructor))` syntax is used to define functions that
	 are called **before** `main`.
2. the `__attribute__((destructor))` syntax is used to define functions that
	 are called **after** `main`.
3. the function signature for `rand` in `shim.c` matches exactly the one
	 provied by glibc.

We looked at how if we used LD_PRELOAD like so `LD_PRELOAD=./shim ./shim_test`
we would get the version of `rand` from `shim` rather than the one from
`glibc`.  The output of shim test with shim is as follows:

```
loading
muhaha!
cleanup
13
```

We then talked about how to call the `rand` from glibc by using the `dlsym`
method to create a function pointer to the glibc rand.  We mentioned that
`RTLD_NEXT` was the magic argument to do that.  Since `RTLD_NEXT` is a GNU
extension to POSIX dlsym, you have to define `_GNU_SOURCE` for `RTLD_NEXT` to
be defined.


#shim_cpp

I mentioned a few pitfalls of using C++ in this class.  Since you may complete the
projects and classwork in either, you may skip this section if you intend to
use C.

1.	the streams based IO interface in C++ using g++ (`std::cin`, `std::cout`, etc...)
		requires memory allocations that happen before `main` is called.  This
		means that if you use `std::cin` in a function marked as
		`__attribute__((constructor))` it will segfault.  You can use c style IO
		exactly the same
2.	You must mark functions that are called from C programs as `extern "C"`
3.	We talked about Exceptions and RTTI as features of C++ that effect the
		binary interface of object files compiled with them, and that you should
		disable them for this class with the `-fno-exceptions -fno-rtti` flags to
		the compiler for this class.

#shim_cpp_clang

We also briefly discussed that clang and libc++ has an implementation of that
fixes the segfault issue. That works by calling its init methods before
`__attribute__((constructor))`s get called.  Unfortunately, after class I
discovered that these are not installed on the lab machines.

#shim_test_static

Finally we talked briefly about static linking and how it provides the
function definitions in the binary.  This makes the binary larger, and
prevents the use of `LD_PRELOAD` to shadow a function.

So the command `LD_PRELOAD=./shim ./shim_test_static` produces a random number
because it uses one from the STATICALLY linked glibc rather than the preloaded
shim.

Here is one possible output

```
1351007488
```
