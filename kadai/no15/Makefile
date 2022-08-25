CC	=	gcc
CFLAGS	=	-g -Wall -O2

TARGET	=	main

EXEDIR	=	.
OBJDIR	=	../obj
INCDIR	=	../inc
PARTSDIR	=	../parts

EXES	=	$(TARGET)
OBJS	=	$(wildcard $(OBJDIR)/*)
INCS	=	$(wildcard $(INCDIR)/*)

all:	$(TARGET)

$(TARGET):	$(OBJS) $(OBJDIR)/main.o $(OBJDIR)/binarization.o
	$(CC) $(CFLAGS) $^ -o $(EXEDIR)/$@ -lm

$(OBJDIR)/%.o:	%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $^ -o $@

$(OBJDIR)%.o:	$(PARTSDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $^ -o $@

.PHONY:	clean
clean:
	$(RM) $(EXES) $(filter-out $(OBJDIR)/bmpfile.o,$(OBJS))
