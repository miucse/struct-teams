CC ?= clang
CFLAGS ?= -Og -Wall -Wpedantic -Wextra
PREFIX ?= /usr/local
BINDIR ?= bin
DESTDIR ?=
TESTS ?=

ifneq ($(CURDIR),$(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST))))))
all:
	@$(MAKE) --no-print-directory -C .. $(filter-out all,$(MAKECMDGOALS))
test:
clean:
clean-objs:
clean-tests:
$(filter-out all,$(MAKECMDGOALS)): all
	@:
else
<< := @echo

ifneq ($(shell eval 'echo -e'),-e)
	<< += -e
endif

<<sources>> := $(wildcard src/*.c)
<<objects>> := $(<<sources>>:src/%.c=obj/%.o)
ifneq ($(TESTS),)
<<tests>>   :=  $(foreach <<test>>,$(TESTS:tests/cases/%.txt=%),tests/cases/$(<<test>>).txt)
else
<<tests>>   :=  $(wildcard tests/cases/*.txt)
endif
<<results>> := $(<<tests>>:tests/cases/%.txt=tests/+results/%.txt)

NAME := $(shell uname -s)
ifeq ($(NAME),)
	BINARY := struct-test.exe
else
	BINARY := struct-test
endif

# format functions
ifneq ($(TERM),)
<<bold>>:= $(shell tput bold)
<<ok>>  := $(<<bold>>)$(shell tput setaf 2)
<<fail>>:= $(<<bold>>)$(shell tput setaf 1)
<<stop>>:= $(shell tput sgr0)
endif

all: obj/$(BINARY)
obj/$(BINARY): $(<<objects>>)
	$(<<) "LINK\t" $(^:obj/%=%)
	@$(CC) $(^) -o $(@) $(LDFLAGS)

clean: clean-objs clean-tests
clean-tests:
	$(<<) "  RM results\t" $(<<results>>:tests/+results/%.txt=case-%)
	@$(RM) -rf tests/+results

clean-objs:
	$(<<) "  RM objects\t" $(<<objects>>:obj/%=%) $(BINARY)
	@$(RM) -rf obj

test: $(<<results>>)

obj/%.o: src/%.c
	$(<<) "  CC\t" $(<:src/%=%)
	@mkdir -p $(shell dirname $(@))
	@$(CC) -c $(<) -o $(@) $(CFLAGS)

tests/+results/%.txt: tests/cases/%.txt obj/$(BINARY)
	$(<<) "$(<<bold>>)TEST\t" $(<:tests/cases/%.txt=case-%)"$(<<stop>>)"
	@mkdir -p tests/+results
	# $(<<bold>>)============ output =============$(<<stop>>)
	@obj/$(BINARY) < $(<) | tee $(@)
	# $(<<bold>>)=========== expected ============$(<<stop>>)
	@EXPECTED=$(subst cases,expected,$(<)); \
		if [ -f "$$EXPECTED" ]; \
		then cat "$$EXPECTED"; \
		else \
			rm -f $(@); \
			echo "None defined"; \
		fi
	# $(<<bold>>)============ result =============$(<<stop>>)
	@EXPECTED=$(subst cases,expected,$(<)); RESULT=$(@); \
		if diff --color -du "$$RESULT" "$$EXPECTED"; \
		then echo "$(<<bold>>)# $(<<ok>>)========== successful ===========$(<<stop>>)"; \
		else echo "$(<<bold>>)# $(<<fail>>)============ failed =============$(<<stop>>)"; rm -f $(@); fi

obj/teams.o: src/teams.h
endif

.PHONY: all clean test clean-objs clean-tests
