.PHONY: clean

ASM_FLAGS := -msyntax=intel -mnaked-reg

output: a.o coroutine.o coroutine_amd64_sysv.o
	gcc -o $@ $^

%.o: %.c
	gcc -o $@ $< -c

%_amd64_sysv.o: %_amd64_sysv.s
	as -o $@ $< $(ASM_FLAGS)

clean:
	rm -fr *.o
	rm -fr output

