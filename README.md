# GinNTony
A compiler of the 'Tony' language, developed for the 2020 compilers' class of ECE NTUA.  

# Repo Structure
We structured this repo to contain our progress through each part towards creating the compiler  
so there is of course file repetition between folders like for example both the lexer folder and parser folder contains lexer.l

The creation of the compiler was split into 5 stages which are:
- Lexer
- Parser
- Abstract Syntax Tree(AST)
- Semantic Analysis
- Machine code generation using LLVM

# Lexer
The lexer uses C++ Flex to generate a scanner for Tony and to tokenize it for the next stages.

# Parser
We use Bison to generate the parser for Tony based on the syntax grammar below:

![Screenshot_2](https://user-images.githubusercontent.com/16371483/126863011-46ed0536-3b3b-4f73-830f-ea6a01de76f2.png)

# Abstract Syntax Tree(AST)
For the AST we used class polymorphism to achieve a tree in which each node would have a class that describes it's behavior best.

# Semantic Analysis
For the semantic analysis we impleneted the sem method for all the node subclasses that needed it so as to be able to achieve  
semantic anaylsis and give proper errors on any semantic mistakes.

# Machine Code Generation
For the last part we used LLVM as the backend of our compiler.  
Each class had the codegen function implemented to best describe it's machine code behavior by using the LLVM C++ API to create
LLVM IR(Low-level Virtual Machine Intermediate Representation) which would subsequently be translate into machine code by using LLVM's llc tool.  
The advantage of using LLVM was that our compiler could be architecture agnostic(since LLVM IR works for all architectures by passing the difficulty of translation for different achitectures to the llc) and also our compiler could use the built in optimization passes of LLVM to optimize the code.  
Lastly we also implemented garbage collection by using the Boehm Garbage Collector and using gc_malloc for any memory allocations instead of malloc.  

# Requirements
- c++ 11.1.1
- flex 2.6.4
- bison 3.7.4
- llvm 12.0.0
- clang 12.0.0
- Boehm Garbage Collector (libgc-devel-7.6.4)

# Build
```bash
  # To build the final compiler go to the llvm folder and run make
  cd llvm
  make
```
# Run Tests
```bash
  cd llvm
  make
  make test
```
# Run
```bash
  # To generate LLVM IR simply run 
  ./GinNTony <filename> 
  # If you want to run the optimization passes then also use the -O flag
  ./GinNTony -O <filename>
  # If you want to simply compile into machine code then the easiest way is to use do.sh
  # It runs GinNTony to get the LLVM IR and then it uses llc to compile into machine code 
  # and clang to link the machine code with the 
  # built in functions and the garbage collector
  ./do.sh <filename>
  # Also the script takes the flags -O -f -i
  # -O is for optimization -f is to print to stdout the final machine code and -i is to print LLVM IR to stdout
  ./do.sh -O -f -i <filename>
```



