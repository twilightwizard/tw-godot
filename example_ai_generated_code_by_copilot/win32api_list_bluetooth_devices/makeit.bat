@echo off
REM - I installed msys2 into the c:\kpdev\msys2 folder.
REM - Then, I added c:\kpdev\msys2\ucrt64\bin to my windows path
REM - Then, I located where the c header files (*.h) were located and added a -I option below
REM - Then, I located where the library files (*.a) were located and added a -L to them.   That did not work for me because
REM -       the gcc compiler did not like the *.a files on any of it's libraries.   i moved the one library that I needed
REM         to the local directory I am compiling and running from and added a -L.\obj to the line below.  Then I added the
REM         name of the library to link to without the *.a on it and I renamed the *.a file to *.lib.
REM  
REM   After doing all of this, msys2's gcc compiler generated a statically linked, native windows program that I can move
REM   anywhere including to a different computer and it will run.
REM 
mkdir obj
del /Q obj\*.*
copy c:\kpdev\msys2\ucrt64\lib\libbthprops.a .\obj\libbthprops.lib
x86_64-w64-mingw32-gcc.exe -g -o run_me.exe -Ic:\kpdev\msys2\ucrt64\include -L.\obj list_bluetooth_devices.c -llibbthprops
dir run_me.exe

