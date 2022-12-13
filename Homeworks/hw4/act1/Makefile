#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat Sep  3 07:56:49 2022
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak


CFLAGS =	-ggdb -std=c99 -Wall -Wextra -pedantic
CLIBFLAGS =	-lm

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	word_tree.c
PS_FILES =	
S_FILES =	
H_FILES =	word_tree.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES) $(OBJFILES)
OBJFILES = build_tree.o query_tree.o

#
# Main targets
#

all:	word_tree 

word_tree:	word_tree.o $(OBJFILES)
	$(CC) $(CFLAGS) -o word_tree word_tree.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

word_tree.o:	word_tree.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f word_tree.o core

realclean:        clean
	-/bin/rm -f word_tree 
