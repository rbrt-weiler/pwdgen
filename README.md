# pwdgen

Creates (secure) passwords on the command line.

## Description

pwdgen is a ANSI C program that can be used to create (secure) passwords on the command line. "Secure" means mumbo-jumbo in this case.

It was primarily a small side-project to do some C again. Do not expect rocket science.

## Requirements

Any C compiler should suffice. I only tested GCC on Linux.

## Compiling

`gcc -o pwdgen pwdgen.c`

## Synopsis

After compiling, `pwdgen -h` will show you all possible options. You will be able to set the safety level of the password(s), the password length and the number of passwords that shall be created.

## Source

The main repository for pwdgen is located at GitLab: [https://gitlab.com/rbrt-weiler/pwdgen](https://gitlab.com/rbrt-weiler/pwdgen)

## License

pwdgen is released und the [Zlib License](http://opensource.org/licenses/Zlib).

## Copyright

pwdgen is (c) 2011-2012 Robert Weiler.

