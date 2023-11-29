EXEC = filter 

.PHONY: all
all:
	@clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o $(EXEC) filter.c helpers.c

check:
	@check50 cs50/problems/2023/x/filter/more

clang:
	@clang-format -i helpers.c

clean:
	rm $(EXEC)
