# minishell_42

This project is a collaboration with [@thedreamJK7](https://github.com/thedreamJK7).

A minimal shell implementation in C, developed as part of the 42 School curriculum. This project demonstrates core concepts of Unix shell programming, including parsing, command execution, environment variable management, and basic job control.

## Features

- **Command Parsing:** Supports simple and complex command lines with quoting, redirection, and pipes.
- **Built-in Commands:** Implements core built-ins such as `cd`, `echo`, `pwd`, `env`, `export`, `unset`, and `exit`.
- **Environment Variables:** Handles environment variable expansion and manipulation.
- **Redirections & Pipes:** Supports standard input/output redirections and piping between commands.
- **Error Handling:** Provides informative error messages for invalid commands and syntax.
- **Signal Handling:** Manages signals such as `Ctrl+C` and `Ctrl+D`.

## Getting Started

### Prerequisites

- GCC or Clang (C compiler)
- Make
- Unix-like operating system (Linux, macOS)

### Build

Clone the repository and run:

```sh
make
```

### Usage

Run the shell:

```sh
./minishell
```

You'll be greeted with a prompt where you can enter standard shell commands.

## Project Structure

- `src/` : Source code files
- `include/` : Header files
- `Makefile` : Build configuration

## Example

```sh
minishell$ echo Hello, World!
Hello, World!
minishell$ ls -l | grep minishell
minishell$ export MYVAR=test
minishell$ echo $MYVAR
test
minishell$ cd ..
minishell$ pwd
```

