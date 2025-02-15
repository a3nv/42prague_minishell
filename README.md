# minishell

## Codecov

When updating codecov.yml do not forget to validate it!

```yaml
curl -X POST --data-binary @codecov.yml https://codecov.io/validate
```

## Criterion test framework
```bash
sudo apt-get update
sudo apt-get install -y libcriterion-dev

brew install criterion
```
## Docker

```bash
docker build -t minishell-image .
docker run -it --rm -v /path/to/your/project:/app minishell-image
docker run -it -v /path/to/your/project:/app --name minishell-container minishell-image
docker start -ai minishell-container
```

## Valgrind
```bash
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./bin/minishell
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

- [ ] rstore signal for a child process. e.g. `grep asd` and then hit ctrl+\ should print quit and return control to the user
- [ ] heredoc do not stop when specified deliliter is encountered
```bash
cat << EOF
Line 1
Line 2
EOF
```
- [ ] '>>' append to a file does not add a new line
- [ ] validation for heredoc. Expected an 'error new unexpected token \n'
```bash
cat <<
```
- [ ] validation. Expected /etc/passwd: Permission denied
```bash
echo asd >> /etc/passwd
```

- [ ] validation. Expected an 'error near unexpected token >'
```bash
> out.txt
```
- [ ] validation. Syntax error
```bash
cat << EOF > output.txt
Hello
EOF
```
