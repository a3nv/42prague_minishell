# minishell

## Codecov

When updating codecov.yml do not forget to validate it!

```yaml
curl -X POST --data-binary @codecov.yml https://codecov.io/validate
```

## Generate coverage locally

```bash
make                                                            # Compile with coverage flags
make test                                                       # Compile tests
make run_test                                                   # Run test to generate .gcda files
#./my_program                                                   # Run program or tests
# gcov parser.c                                                 # View line coverage in terminal
lcov --capture --directory . --output-file coverage.info        # Capture coverage data
genhtml coverage.info --output-directory coverage_report        # Generate HTML report
xdg-open coverage_report/index.html                             # Open report
open coverage_report/index.html                                 # Open report (macos)
make clean                                                      # Clean up
```
## Todo

### Structure
- [x] move gnl files into libft;
- [x] add hash map files into libft;
- [x] update libft to build those files;

### Lexer

### Parser
- [x] ~parse tokens into a strucutre called smth like command~;
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

- [ ] this example gives different result after parsing
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
cat file.txt | grep foo | wc -l > output.txt
Expected tree
```yaml
REDIRECT OUT Node
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
            ├── Argument: output.txt
```
Expected tree traversal
```bash
Executing command: cat file.txt
Executing command: grep foo
Executing pipe
Executing command: wc -l
Executing command: output.txt
Executing redir
Executing pipe
```

## Notes

### Output and actions

- Probably it would be better to use write function as it directly writes into the output.

