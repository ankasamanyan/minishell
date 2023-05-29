# Minishell

Minishell is a project that focuses on developing a shell program. It aims to deepen the understanding of Unix systems, processes, provids a basic command-line interface.

## Project Overview

This project is a shell program that allows users to interact with their operating system through a command-line interface. The shell should be capable of executing various commands, handling I/O redirection, supporting environment variables, and managing processes.

## Key Features

- Command execution: The shell should execute commands entered by the user, including both built-in commands and external programs.
- I/O redirection: Support for redirecting input and output streams using symbols such as `>`, `<`, and `>>`.
- Environment variables: Ability to handle environment variables, including variable expansion and substitution.
- Signal handling: Handling of signals such as Ctrl+C (SIGINT) and Ctrl+D (EOF).
- Process management: Managing child processes, including process creation and termination.
- Error handling: Appropriate error handling for various scenarios, providing informative error messages to the user.

## Getting Started

Dependencies:
	The readline library is necessary please find out how to install readline library on your system!

• Run the following code in your terminal to install the library `[ For MacOS ]`: 
```
if ! [ -r $HOME/goinfre/.brew/Cellar/readline ]; then
	rm -rf $HOME/goinfre/.brew

	git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew

	echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc

	source $HOME/.zshrc && brew update

	brew install readline
fi
```

To get started with Minishell, follow these steps:

1. Clone the repository:				
```
git clone https://github.com/ankasamanyan/minishell.git
```
2. Navigate to the project directory:	
```
cd minishell
```
3. Build the project:					
```
make
```
4. Run Minishell:						
```
./minishell
```

## Usage

Once you have Minishell up and running, you can start using it to execute shell commands. Here are some examples of how you can interact with the shell:

```
$ ls -l              			# Execute the 'ls' command with the '-l' option
$ echo "Hello!"      			# Print the string "Hello!"
$ pwd                			# Print the current working directory
$ cat file.txt       			# Display the contents of a file
$ ls > files.txt     			# Redirect the output of 'ls' to a file
$ grep "pattern" < input.txt    # Redirect a file as input for 'grep'
$ command1 | command2           # Pipe the output of 'command1' to 'command2'
$ export VAR=value              # Set an environment variable
$ echo $VAR                     # Access the value of an environment variable
$ cd /path/to/directory         # Change the current directory
$ exit                          # Exit Minishell
```

<img width="730" alt="image" src="https://user-images.githubusercontent.com/89840461/205446900-ba137aab-9ce3-487b-998c-c36f306957fc.png">

