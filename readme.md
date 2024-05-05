# MMFILE I/O Project
## Project to explore Multi-Processsing and Memory Mapped Files
The following diagram shows the process flow of the program:

```
   root_process
      /\
     /  \
    /\   \
mm_r  \   screenfetch
      mm_w
```
Where mm_r is the memory_map read process, mm_w is the memory map write process and screenfetch is the screenfetch program from the system.

The program first constructs the global memory map and then starts to fork.

Notes:
  - mm_r and mm_w can read and write to the memory mapped file simultainiously due to `MAP_SHARED` flag.

### Output
```bash
                          ./+o+-       matt@edison
                  yyyyy- -yyyyyy+      OS: Ubuntu 24.04 noble
               ://+//////-yyyyyyo      Kernel: x86_64 Linux 6.8.0-31-generic
           .++ .:/++++++/-.+sss/`      Uptime: 4h 18m
         .:++o:  /++++++++/:--:/-      Packages: 1630
        o:+o+:++.`..```.-/oo+++++/     Shell: mmfile
       .:+o:+o/.          `+sssoo+/    Resolution: 1920x1200
  .++/+:+oo+o:`             /sssooo.   DE: GNOME 46.0.1
 /+++//+:`oo+o               /::--:.   WM: Mutter
 \+/+o+++`o++o               ++////.   WM Theme: Adwaita
  .++.o+++oo+:`             /dddhhh.   GTK Theme: Adwaita [GTK2/3]
       .+.o+oo:.          `oddhhhh+    Icon Theme: Adwaita
        \+.++o+o``-````.:ohdhhhhh+     Font: Cantarell 11
         `:o+++ `ohhhhhhhhyo++os:      Disk: 14G / 469G (4%)
           .o:`.syhhhhhhh/.oo++o`      CPU: 11th Gen Intel Core i7-1185G7 @ 8x 4.8GHz [51.0°C]
               /osyyyyyyo++ooo+++/     GPU: Iris Xe Graphics
                   ````` +oo+++o\:     RAM: 6444MiB / 15701MiB
                          `oo++.      
Parent PID: 41146
Child PID: 41146
Sat May  4 23:10:23 2024

Reading Map Values:
0xDEADC0DE
0xBEEFFEED
0xDEADF0DF
0xBEEFBEAD

Child PID: 41146
Sat May  4 23:10:24 2024

Reading Map Values:
0xDEADC0DE
0xBEEFFEED
0xDEADF0DF
0xBEEFBEAD

Child PID: 41146
Sat May  4 23:10:25 2024

Reading Map Values:
0xDEADC0DE
0xBEEFFEED
0xDEADF0DF
0xBEEFBEAD

Parent PID: 41146 Update buf[1]:
Sat May  4 23:10:26 2024

Child PID: 41146
Sat May  4 23:10:26 2024

0xBAAAAAAD

Reading Map Values:
0xDEADC0DE
0xBAAAAAAD  **CHANGED** 
0xDEADF0DF
0xBEEFBEAD

Child PID: 41146
Sat May  4 23:10:27 2024

Reading Map Values:
0xDEADC0DE
0xBAAAAAAD
0xDEADF0DF
0xBEEFBEAD
```
# Conclusion
The code provides an effective example for:
  1. Writing binary files.
  1. Using Memory mapped files.
  1. Multi-processing in linux using `fork()` and `execl()`.