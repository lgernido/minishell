# MiniShell

## Overview
**MiniShell** is a custom UNIX-like shell that supports basic command execution, redirections, pipes, signal handling, variable expansion, and a subset of shell built-in commands. It replicates much of Bash's behavior while adhering to strict coding and structural constraints.

---

## Features

### **Prompt & Command Execution**
- Displays a prompt while waiting for user input.
- Maintains a working command history.
- Locates and executes binaries using the `PATH` variable, absolute paths, or relative paths.
- Supports only **one** global variable (used to handle signals safely).
- No interpretation of:
  - Unclosed quotes
  - Unsupported special characters (`\`, `;`)

---

### **Quoting Rules**
- **Single quotes `'`**: Prevent all meta-character interpretation.
- **Double quotes `"`**: Prevent all meta-character interpretation **except** `$` for variable expansion.

---

### **Redirections**
- `<` : Redirect input.
- `>` : Redirect output (overwrite).
- `>>` : Redirect output (append mode).
- `<<` : Here-document, reads until a given delimiter (not stored in history).

---

### **Pipes**
- `|` : Chain commands by connecting the output of one to the input of the next.

---

### **Variables**
- `$VAR` : Expands to environment variable value.
- `$?` : Expands to the exit status of the last executed foreground pipeline.

---

### **Signal Handling (Interactive Mode)**
- **CTRL-C** : Prints a new prompt on a new line.
- **CTRL-D** : Exits the shell.
- **CTRL-\\** : Does nothing.

---

### **Built-in Commands**
| Command   | Description |
|-----------|-------------|
| `echo [-n]` | Prints arguments to standard output, `-n` disables newline. |
| `cd [path]` | Changes the current directory (absolute or relative path only). |
| `pwd` | Prints the current working directory. |
| `export` | Sets environment variables (no options). |
| `unset` | Removes environment variables (no options). |
| `env` | Prints the environment variables (no args). |
| `exit` | Exits the shell. |

---

### **Logical Operators & Priorities**
- `&&` : Execute next command only if previous succeeded.
- `||` : Execute next command only if previous failed.
- Parentheses `()` : Group commands to enforce execution priority.

---

### **Wildcards**
- `*` : Expands to matching filenames in the current working directory.

---

## Example Usage
```bash
minishell$ echo "Hello $USER"
Hello val

minishell$ ls *.c | grep main
main.c

minishell$ cat <<EOF
> Line 1
> Line 2
> EOF
Line 1
Line 2
```

## Build & Run
**Requirements:**
- `readline` library

**Steps (Unix/Linux):**
```bash
git clone git@github.com:lgernido/minishell.git
cd minishell
make
./minishell
```

**Notes:**
- On **macOS**, you may need to tweak the `Makefile` to set the correct `readline` include and library paths.
- Not tested on Windows.
- Thoroughly tested under **Ubuntu**.

