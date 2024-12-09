# minishell

## Todo

### Structure
- [ ] move gnl files into libft;
- [ ] add hash map files into libft;
- [ ] update libft to build those files;

### Lexer
### Parser
- [ ] parse tokens into a strucutre called smth like command;
- [ ] handle validation while parsing;

#### Examples

`cat file.txt | grep foo | wc -l > output.txt`

```yaml
PIPE Node
    ├── Left:
        PIPE Node
            ├── Left:
                COMMAND Node:
                    ├── Argument: cat
                    ├── Argument: file.txt
            └── Right:
                COMMAND Node:
                    ├── Argument: grep
                    ├── Argument: foo
    └── Right:
        REDIRECT OUT Node
            ├── Left:
                COMMAND Node:
                    ├── Argument: wc
                    ├── Argument: -l
            └── Right:
                COMMAND Node:
                    ├── Argument: output.txt
```

`ls -l | grep foo > output.txt`
```yaml
PIPE Node
    ├── Left:
        COMMAND Node:
            ├── Argument: ls
            ├── Argument: -l
    └── Right:
        REDIRECT OUT Node
            ├── Left:
                COMMAND Node:
                    ├── Argument: grep
                    ├── Argument: foo
            └── Right:
                COMMAND Node:
                    ├── Argument: output.txt

```

`cat file | grep foo | wc`
```yaml
PIPE Node
    ├── Left:
        PIPE Node
            ├── Left:
                COMMAND Node:
                    ├── Argument: cat
            └── Right:
                COMMAND Node:
                    ├── Argument: grep
                    ├── Argument: foo
    └── Right:
        COMMAND Node:
            ├── Argument: wc
```

`cat file.txt`
```yaml
COMMAND Node:
    ├── Argument: cat
    ├── Argument: file.txt

```

-[ ] this example gives different result after parsing
`cat file.txt | grep foo | wc -l | sort | uniq -c > output.txt`
```yaml
REDIRECT OUT Node
    ├── Left:
        PIPE Node
            ├── Left:
                PIPE Node
                    ├── Left:
                        PIPE Node
                            ├── Left:
                                COMMAND Node:
                                    ├── Argument: cat
                                    ├── Argument: file.txt
                            └── Right:
                                COMMAND Node:
                                    ├── Argument: grep
                                    ├── Argument: foo
                    └── Right:
                        COMMAND Node:
                            ├── Argument: wc
                            ├── Argument: -l
            └── Right:
                COMMAND Node:
                    ├── Argument: sort
    └── Right:
        COMMAND Node:
            ├── Argument: uniq
            ├── Argument: -c
    └── Right:
        COMMAND Node:
            ├── Argument: output.txt

```
### Expander
### Executor

## Notes

### Output and actions

- Probably it would be better to use write function as it directly writes into the output.

