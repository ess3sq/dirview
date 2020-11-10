# dirview
**view directory tree structure**

## About

This program provides an utility to visualise tree structures on a POSIX-compliant system.
It was mainly tested with files and directories. As such, support for other kinds of devices
is experimental.

## Compilation

The only requirements are a C Compiler and the `clz/color.h` header (more about the latter later).
The installation script uses `gcc`, but since it contains a single line command it can be replaced
with any other compiler.

The header file `color.h` needs to be located inside the `cl/z` directory, which itself must be placed
in a path where the compiler looks for header files (typically `/usr/include` if you wish to make it
available to all users on your system, otherwise on a more personal path). In case it is necessary,
you can use the `-I/path/to/clz` compiler option to indicate such a location.

After having compiled the program, you might want to move the executable to a location that
can be found when accessing the command on the shell (ie. `/usr/bin` for system-wide installation,
or any other directory which lies in the `$PATH` variable.

## Use

To get started, type the command

`dirview --help`

This will yield the following output, which serves as main reference:

```
dirview: view directory tree structure
Usage:
        dirview [OPTIONS ...] [PATHS ...]
Options:
        Some options require an argument.
        -n, --max-depth <arg>   Specify max recursion depth
                                (arg must be a positive integer)
        -e, --exclude <arg>     Specify a substring of the path as a
                                case-sensitive exclusion pattern

        -p, --no-parent         Hide parent prefix
        -f, --files             Hide empty directories
        -d, --dirs              Show only directories, hide files
        -h, --show-hidden       Show hidden files and directories
                                (name starts with .)

        -c, --color             Color devices (everything except directories)
        -i, --no-indent         Omit indentation of tree structure

            --help              Show current view
            --version           Show program version
Notes:
        - The path(s) need(s) to be provided after the options,
          otherwise the options will not apply.
        - The options '-f' and '-d' do not apply to the 'root' devices
          and directories passed to the program.
        - If the path points to a deeper tree structure, the use of
          the option '-f' may cause a significant additional overhead.

```

## Credits and License

The program is licensed under the MIT License ([Lorenzo Calza](https://www.calza.xyz))

````
MIT License

Copyright (c) 2020 Lorenzo Calza

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```