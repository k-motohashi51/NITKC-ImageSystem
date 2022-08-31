CC		=	gcc
CFLAGS	=	-g -Wall -O2

TARGET	=	main

SRCDIR	=	./src
INCDIR	=	./inc
OBJDIR	=	./obj
EXEDIR	=	./bin

SRCS	=	$(wildcard $(SRCDIR)/*.c)
INCS	=	$(wildcard $(INCDIR)/*.h)
OBJS	=	$(wildcard $(OBJDIR)/*.o) $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
EXES	=	$(TARGET)

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEDIR)/$@ -lm

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

.PHONY:	clean
clean:
	$(RM) $(EXES) $(filter-out $(OBJDIR)/bmpfile.o,$(OBJS))
