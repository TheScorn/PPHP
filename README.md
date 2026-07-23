# PPHP
PePeHypertextPreprocessor - library for preprocessing C strings with given args

Library contains functions for modifying C strings in the style of PHP. 

The special string that all functions will look for is called a field and looks like: <<{var}>>.

## Dependencies

Required:

- GCC with C11 support
- POSIX-compatible operating system
- POSIX regex library {`regex.h`}

For running tests:
 - GoogleTest