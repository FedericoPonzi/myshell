Myshell
========
A shell created for fun and study.

## Supported commands:

 * echo <text>
 * clear
 * exit
 * clear
 * external command

---

This shell is still a working progress! It can do basic things, but there is still a lot I wish to do!

### Todo:
 * Use more complex parsing (EBNF in progress) to parse
 * Handle movement keys
 * Handle I/O redirects.

## Soft todo:
 * Handle environemnt variables

## Long todo:
 * Add basic scripting stuff: If/for/while

## Very long todo:
 * Run script file. myshell batch.msh

## LONG LONG todo:
 * -

----

The EBNF of the language is:

program := statement+;
statment := assignemnt | command var_args |
assingment := id '=' expr
var_arg := lit | var_arg | e
term :=  [0-9]+ | \""[a-zA-Z\ ]+"\"
statment := command var_arg | pipe | output_redirection
command := "echo" | "exit" | "clear" | "help" | "sleep"
var_arg

