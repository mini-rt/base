.DEFAULT_GOAL := all
.PHONY: all


CC := clang
CFLAGS += -Wall -Wextra -Werror -Wmissing-prototypes
CPPFLAGS += -Iinclude

include include.mk

SRCS := src/minirt_f.c src/minirt_vector.c src/minirt_matrix.c
OBJS_A := $(patsubst src/%.c,obj/%$(SUFFIX).a.o,$(SRCS))
OBJS_SO := $(patsubst src/%.c,obj/%$(SUFFIX).so.o,$(SRCS))
SO_OR_DYLIB := $(if $(filter Darwin,$(shell uname -s)),dylib,so)
TARGET_A := libminirt_base$(SUFFIX).a
TARGET_SO := libminirt_base$(SUFFIX).$(SO_OR_DYLIB)

obj/%$(SUFFIX).a.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

obj/%$(SUFFIX).so.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ -fPIC $<

all: libminirt_base.a
libminirt_base.a: $(TARGET_A)
	cp $< $@
$(TARGET_A): $(OBJS_A)
	ar cr $@ $^

all: libminirt_base.$(SO_OR_DYLIB)
libminirt_base.$(SO_OR_DYLIB): $(TARGET_SO)
	cp $< $@
$(TARGET_SO): $(OBJS_SO)
	ar cr $@ $^

.PHONY: dev

dev: compile_commands.json
compile_commands.json: $(patsubst src/%.c,obj/%$(SUFFIX).json.part,$(SRCS))
	(echo [ && cat $^ && echo ]) > $@
obj/%$(SUFFIX).json.part: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o /dev/null -MJ $@ $<

.PHONY: clean
clean:
	rm obj/*
