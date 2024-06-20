myshell:myshell.c myshell.h
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f myshell
