# Minishell

Minishell is a simple shell implementation written in C. It provides basic shell functionalities, allowing users to execute commands, handle input/output redirection, and manage processes.

## Features

- Execute basic shell commands.
- Input and output redirection (`>`, `<`, `>>`).
- Pipe (`|`) support for chaining commands.
- Environment variable handling.
- Built-in commands like `cd`, `echo`, `exit`, etc.
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`).

## Requirements

- GCC or any C compiler.
- Make utility.

## Installation

1. Clone the repository:
	```
	git clone <repository_url>
	cd minishell
	```

2. Build the project:
	```
	make
	```

## Usage

Run the shell:
```
./minishell
```

Type commands as you would in a regular shell. For example:
```
ls -l | grep minishell > output.txt
```
