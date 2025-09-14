# L-1.2-Process-Monitor-Project
# Process Runner

A simple C program to run multiple commands concurrently and collect their exit codes, with a basic testing framework.

## Project Structure
process-runner/\
│\
├─ src/ \
│ └─ main.c # Main program\
│\
├─ tests/\
│ └─ test.c # Test program\
│\
├─ Makefile # Optional build instructions\
├─ README.md # Project description

## Features

- Run multiple shell commands concurrently.
- Collect exit codes of child processes.
- Basic functionality, error handling, and performance tests.

## Tests

The tests are in `tests/test.c`:

1. **Basic Functionality Test**: Runs a set of valid commands and checks their exit codes.
2. **Error Handling Test**: Runs an invalid command and ensures the program handles it gracefully.
3. **Performance Test**: Measures execution time of multiple commands.

Commands used for testing (examples):

- `ls -l`
- `pwd`
- `whoami`
- `date`
- `ps aux`
- Invalid command: `invalid_command` (to test error handling)

