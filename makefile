

CC := tcc # tcc, gcc, clang

INCLUDE_ALL = -I.

# FLAGS_ERROR := -Wall -pedantic-errors
FLAGS_ERROR :=


# FLAGS_BUILD_TYPE = -O3 -DNDEBUG #Release
FLAGS_BUILD_TYPE = -O0 -g #Debug

CFLAGS := ${INCLUDE_ALL} ${FLAGS_BUILD_TYPE}  ${FLAGS_ERROR}


SOURCES_TEST := test.c
EXEC := test.exe
HEADERS := $(wildcard *.h)

.PHONY: all  
all: astyle $(EXEC)

.PHONY : astyle
astyle: $(HEADERS) $(SOURCES_TEST); astyle --style=java --indent=spaces=4 --indent-switches --pad-oper --pad-comma --pad-header --unpad-paren  --align-pointer=middle --align-reference=middle --add-braces --add-one-line-braces --attach-return-type --convert-tabs --suffix=none *.h *.c

$(EXEC): $(SOURCES_TEST) 
	$(CC) $^ -o  $@  $(CFLAGS)

.PHONY: wclean
wclean: ; del /q /s *.o *.a *.exe build\\*.txt
.PHONY: clean
clean: ; rm -frv $(TARGETS_TEST) $(EXEC)
