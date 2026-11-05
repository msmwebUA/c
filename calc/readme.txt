--- Integer Calculation Program for Pico ---

### Acceptable calculation actions

  add (+), 
  subtract (-), 
  multiply (*), 
  divide (/), 
  modulo (%).

### Usage example 

  Type x+y and press enter ('x' and 'y' must be positive integers, '+' can be replaced with supported operators).
  Program ignores whitespaces in input.

### Limits

	- max supported argument is a 32 bit unsigned integer (2^32 - 1),
	- max supported result is a 64 bit signed integer (from -2^63 to 2^63 - 1),
	- user input max length is 21 chars.

### Commands

  "i" - print info and list of commands
  "q" - exit
  "h" - show history
  "c" - clear history
  "!x" - recalculate history row x (x is row number 1..10)

### Compilation

  Use attached CMakeLists.txt file for compilation.
  Add -DBUILD_FOR_PICO=ON flag if you build for Raspberry Pico  
  Example:
    cmake -S . -B build-pico -DBUILD_FOR_PICO=ON -DPICO_BOARD=pico2_w
    cmake --build build-pico