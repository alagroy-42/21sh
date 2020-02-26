# 21sh

21sh is a project that makes you create a basic but functionnal shell with line editing, signal handling, pipes and redirections.

## Install
```bash
make && ./21sh
```

## Keyboard shortcuts

| KEY | ACTION |
| --- | ------ |
| Left arrow | Go one character left |
| Right arrow | Go one character right |
| Home | Go to the beginning of the line |
| End | Go to the end of the line |
| Backspace | Delete one character |
| Up arrow | Go up on the history list |
| Down arrow | Go down in the history list |
| Ctrl-D | Delete one character or quit the shell if the line is empty |
| Ctrl-L | Clear the screen |
| Alt-Left | Go one word backward |
| Alt-Right | Go one word forward |
| Alt-Up | Go one line up if the command is longer than a line |
| Alt-Down | Go down a line if the command is longer than a line |
| Tab | Autocomplete |
| Ctrl-R | Incremental search in history |
| Ctrl-B | Turn on/off visual mode |
| Alt-X | Cut text selection in visual mode |
| Alt-C | Copy text selection iin visual mode |
| Alt-V | Paste text selection in visual mode |

## Features

- Pipes: |
- Redirections: >, <, >>, <<
- Semicolon separator: ;
- Logical operators: &&, ||
- Environnement management
- Builtins (POSIX compliant)
  - cd
  - env
  - exit
  - setenv
  - unsetenv
  - echo

