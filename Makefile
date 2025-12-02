.PHONY: all setup run reset clean

SRCDIR=src
OBJDIR=$(SRCDIR)/obj
INCDIR=include
OUTDIR=output

CC=sdcc
CCFLAGS=-I$(INCDIR) --Werror -lstm8 -mstm8 --out-fmt-ihx --std-sdcc23 --debug

DEPS:=$(wildcard $(INCDIR)/*.h)
SRC:=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.rel)

EXE=respirator.ihx

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
