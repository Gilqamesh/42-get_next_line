BUFFER = BUFFER_SIZE=10

a.out : driver.c get_next_line.h get_next_line.o get_next_line_utils.o
	gcc -o a.out driver.c get_next_line.o get_next_line_utils.o
get_next_line.o : get_next_line.c get_next_line.h
	gcc -Wall -Wextra -Werror -c -D $(BUFFER) get_next_line.c
get_next_line_utils.o : get_next_line_utils.c get_next_line.h
	gcc -Wall -Wextra -Werror -c get_next_line_utils.c

.PHONY: f
f :
	gcc -Wall -Wextra -Werror -c get_next_line_utils.c
	gcc -Wall -Wextra -Werror -c -D $(BUFFER) get_next_line.c
	gcc -o a.out driver.c get_next_line.o get_next_line_utils.o