# Copilot Instructions for transliterate

## Project Overview

This is a simple C-based transliteration utility project. The main program is a command-line application written in C.

## Build and Run

- **Build and run**: Use `make run` to compile and execute the program
- **Compiler**: GCC is used for compilation
- **Output binary**: `main` (generated in the project root)

## Code Style and Conventions

### C Programming Standards

- Follow standard C conventions
- Use proper indentation (tabs are used in the makefile)
- Include proper header files
- Use descriptive variable and function names
- Always include return statements in functions
- Add proper error handling where applicable

### File Organization

- `main.c`: Main program source file
- `makefile`: Build configuration
- Keep the codebase simple and maintainable

## Development Guidelines

1. **Testing**: Compile and run the program after making changes to verify functionality
2. **Makefile**: The makefile uses `@` prefix to suppress command echoing
3. **Binary Output**: The compiled binary is named `main` and should be excluded from version control
4. **Incremental Changes**: Make small, focused changes and test frequently

## Best Practices

- Write clean, readable C code
- Ensure proper memory management (allocate and free memory appropriately)
- Handle edge cases and potential errors
- Document complex logic with comments when necessary
- Test compilation after code changes using `make run`
