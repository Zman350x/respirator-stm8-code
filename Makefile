.PHONY: all setup run reset clean

SRCDIR=src
OBJDIR=$(SRCDIR)/obj
INCDIR=include
OUTDIR=output

CC=sdcc
COMMON_CCFLAGS=-I$(INCDIR) --Werror -lstm8 -mstm8 --std-sdcc11 --verbose --fverbose-asm
DEBUG_CCFLAGS=--out-fmt-elf --debug
RELEASE_CCFLAGS=--out-fmt-ihx

DEPS:=$(wildcard $(INCDIR)/*.h)
SRC:=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.rel)

EXE_BASE=respirator

ifeq ($(DEBUG), 1)
	EXE:=$(EXE_BASE).elf
	CCFLAGS:=$(COMMON_CCFLAGS) $(DEBUG_CCFLAGS)
else
	EXE:=$(EXE_BASE).ihx
	CCFLAGS:=$(COMMON_CCFLAGS) $(RELEASE_CCFLAGS)
endif

all: $(EXE)

$(OBJDIR)/%.rel: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CCFLAGS)

setup:
	mkdir -p $(SRCDIR) $(OBJDIR) $(INCDIR) $(OUTDIR)

run:
	stm8flash -c stlinkv2 -p stm8s003f3 -w $(OUTDIR)/$(EXE)

reset:
	stm8flash -c stlinkv2 -p stm8s003f3 -R

clean:
	rm -f ./$(OBJDIR)/* ./$(OUTDIR)/*
