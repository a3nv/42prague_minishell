# minishell

## Codecov

When updating codecov.yml do not forget to validate it!

```yaml
curl -X POST --data-binary @codecov.yml https://codecov.io/validate
```

## Criterion test framework
```bash
sudo apt-get update
sudo apt-get install -y criterion-dev

brew install criterion
```
## Docker

```bash
docker build -t minishell-image .
docker run -it --rm -v /path/to/your/project:/app minishell-image
docker run -it -v /path/to/your/project:/app --name minishell-container minishell-image
docker start -ai minishell-container
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

### Expander
### Executor

## Notes

### Output and actions

- Probably it would be better to use write function as it directly writes into the output.

