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
 * Handle I/O redirects.

## Soft todo:
 * Handle environemnt variables

## Long todo:
 * tab completition for commands
 * Add basic scripting stuff: If/for/while

## Very long todo:
 * Run script file. myshell batch.msh
 * Source command

## LONG LONG todo:
 * - Load configuration files: `~/.myshrc`


## Wanted:

 * personalized prompt: add username, hostname ecc.
 * STDIN STDOUT redirect: using `<`` and `>`, later maybe add `>>` for append, `>` to overwrite and `&>` support ecc.
 * support for background processes: & to background, fg and bg commands. Don't exit if there are background processes.
 * history: history command, up and down keys, record commands in a history file. Maybe one day add ctrl+r/ctrl+s to find ecc.
 * Some nice-to-have commands: jobs, cd, history, exit, kill.
 * if-then-else: basic scripting support.


----

Trying to being a bit formal here. Mysh is based on this EBNF language:

```
program := statement+ [&];
statement := command [connector]
connector := { || or && or | } statement | ; statement |
redirection := < filename or > filename
command := command_list var_args [redirection]
command_list := "echo" | "exit" | "clear" | "help" | "sleep" ..... | anyCharacterNoSapces
var_arg := term | var_arg | e
term = anyCharacterNoSpaces+ | "anyCharacterWithSpaces+"
```

cat file.txt | cat | cat | cat
cat file > out.txt
cat file > out.txt && cat out.txt | out.txt
cat 1.txt | cat < 2.txt

In future (maybe):
```
program := statement+ [&];
statement := command [connector]
connector := { || or && or | } statement | ; statement |
redirection := < filename | > filename | < filename > filename
assingment := id '=' expr
var_arg := lit | var_arg | e
term :=  [0-9]+ | \"[any char]\"
command := "echo" | "exit" | "clear" | "help" | "sleep"
var_arg
```

1. leggo il comando



cat file > out.txt && cat out.txt | out.txt

`cat file > out.txt`
lo aggiungo alla lista di comandi da eseguire

Leggo connector. Mi salvo qual è. Il comando AND, wrappa un comando normale, che viene eseguito solo se il codice del precedente è 0
Leggo cat out.txt. Lo salvo nella lista di comandi da eseguire

Leggo Pipe. Mi salvo l'informazione, e wrappo out.txt. Il problema è che out.txt dovrebbe essere eseguito contemporaneamente con out.txt
nella esecuzione, se il comando successivo è di tipo pipe, allora lo avvio ed eseguo la redirezione del stdout.
Prima eseguo la pipe, poi attivo il redirect dell'output.


Pseudocode for parsing the command name:
while isspace(line[i]) and line[i] != \0; # trim
    line[i] = \0;
    i++
while line[i] != " " && line[i] != "\0": # command name
    i++;
strncpy(line, arg->command_name, i-last_index);
break;

Pseudocode for parsing the arguments:
while line[i] == " " and line[i] != \0 and line[i] != connector:
   line[i] = \0;

   if line[i] == '\"':
    while line[i] != "\\\"":
        i++;
   else:
       while isspace(line[i]) && line[i] |= \0:
         i++;
   arg =malloc();
   strncpy(line+i, arg, last -i);
   command->args.append(arg);














