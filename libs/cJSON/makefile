CJSON_OBJ = cJSON.o
CJSON_LIBNAME = libcjson

CC = clang -std=c89

PIC_FLAGS = -fPIC
R_CFLAGS = $(PIC_FLAGS) -pedantic -Wall -Werror -Wstrict-prototypes -Wwrite-strings -Wshadow -Winit-self -Wcast-align -Wformat=2 -Wmissing-prototypes -Wstrict-overflow=2 -Wcast-qual -Wc++-compat -Wundef -Wswitch-default -Wconversion

#library file extensions
STATIC = a

CJSON_STATIC = ../lib/$(CJSON_LIBNAME).$(STATIC)

all: static

static: $(CJSON_STATIC)

$(CJSON_STATIC): $(CJSON_OBJ)
	@cp cJSON.h ../inc/
	@$(AR) rcs $@ $<

$(CJSON_OBJ): cJSON.c cJSON.h
	@$(CC) -c $(R_CFLAGS) $<

uninstall: clean
	@rm -rf $(CJSON_STATIC)

clean:
	@rm -rf $(CJSON_OBJ)
	@rm -rf ../inc/cJSON.h

reinstall: uninstall all

.PHONY: all static clean uninstall reinstall