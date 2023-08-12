parser_src=./parser/parser.c
variable_src=./variable/variable.c
command_src=./builtin_commands/command_managment.c
main_src=./main/main.c

myshell: $(main_src) $(parser_src) $(variable_src) $(command_src) 
	@gcc $(main_src) $(parser_src) $(variable_src) $(command_src) -o myshell
	@echo "*********** myshell is generated ***********"

remove:
	rm myshell
