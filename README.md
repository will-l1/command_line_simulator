# command_line_simulator

## Overview

This project is a simple command line simulator written in C. It mimics basic shell functionalities such as executing commands, maintaining a history of executed commands, and recalling commands from history.

## Files

- main.c: The main program that implements the command line simulator.

## Compilation

To compile the project, use the following command:
gcc -o command_line_simulator main.c

## Usage

After compiling, you can run the simulator as follows:
./command_line_simulator

### Features

1. Basic Command Execution: 
   - The simulator reads input commands from the user and executes them.
   - If the command is invalid, it prints "Invalid command!".

2. Command History:
   - The simulator maintains a history of the last 10 executed commands.
   - The command history can be viewed by typing `history`.

3. Recall Commands:
   - To recall the most recent command, type `!!`.
   - To recall a specific command from the history, type `!n` where `n` is the command number in the history.
   - If there is no command in history or the specified command is not found, appropriate messages are displayed.

### Example

Input:

ls 
history 
!1 
!! 
exit


Output:
CSCI3120>ls <output of ls> 
CSCI3120>history ID PID Command 0 1234 ls 
CSCI3120>!1 ls <output of ls> 
CSCI3120>!! ls <output of ls> 
CSCI3120>exit


## Code Structure

### main.c

- `main()`: The main function that initializes the command line interface, processes input commands, and handles command execution.
- `fgets(input, MAX_LINE, stdin)`: Reads the user input.
- `strtok(input, " ")`: Tokenizes the input command.
- `fork()`: Creates a new process to execute the command.
- `execvp(args[0], args)`: Executes the command in the child process.
- `wait(NULL)`: The parent process waits for the child process to complete.
- Command history is managed using arrays `id_hist` and `command_hist`.

## License

This project is licensed under the MIT License.

