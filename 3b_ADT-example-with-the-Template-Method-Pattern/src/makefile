#Sets GCC as the C compiler
CC = gcc
CFLAGS = -I$(IDIR)

#Identifies the include directory
IDIR = ../include

#Identifies the object directory
ODIR = ../obj

#Dependencies (include files)
_DEPS = CaffeinatedBeverage.h CaffeinatedBeverage_Private.h Coffee.h Tea.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#Object files
_OBJ = Test.o CaffeinatedBeverage.o Coffee.o Tea.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#Macro that tells make each object file depends on
#the source file of the same name and on the
#dependencies list. 
#The second part of the macro tells make that if either
#the source file or the dependencies change, regenerate
#the object file (-c) using GCC ($(CC)), place the
#output into the file name on the left side of the ":"
#(-o $@) and include any of the dependencies ($<)
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#Macro that tells make to generate an executable with
#the name given on the left side of the ":" (-o $@)
#if any of the object files change.
Test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
