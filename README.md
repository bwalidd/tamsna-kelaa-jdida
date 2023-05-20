# 42-minishell

![Alt Text](https://cdn.outdoorhub.com/wp-content/uploads/sites/2/2015/12/outdoorhub--2015-12-02_00-01-38.jpg)

Minishell is a project developed as part of the 42 curriculum. It aims to create a simplified shell that can interpret and execute basic commands, handle environment variables, and implement some built-in functionalities.

Installation
To install and run the Minishell project, follow these steps:

Clone the repository:
'git clone https://github.com/your-username/minishell.git'

Navigate to the project directory:
'cd minishell'

Compile the source code:
'make'

Run Minishell:
'./minishell'

Usage
Once you have started Minishell, you can enter commands and execute them. The shell supports various features and built-in commands, including but not limited to:

Running external commands by specifying the command's name.
Handling environment variables using the syntax $VAR_NAME.
Redirecting input/output using the < and > symbols.
Implementing pipes using the | symbol.
Managing the exit status of previously executed commands with the $? variable.
Implementing built-in commands like echo, cd, env, export, unset, exit, etc.
Here's an example of using Minishell:

shell
Copy code
$ ./minishell
minishell$ echo Hello, World!
Hello, World!
minishell$ ls -l
total 8
-rwxr-xr-x  1 user  staff  16376 May 20 12:00 minishell
minishell$ cd ..
minishell$ pwd
/Users/user
minishell$ exit
$
Contributing
Contributions to the Minishell project are welcome. If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.
