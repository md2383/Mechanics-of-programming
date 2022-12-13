#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Oct  5 21:37:10 2022
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

CC = gcc
CFLAGS = -ggdb -std=c99 -Wall -Wextra -pedantic

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	cave.c explore.c traverse.c
PS_FILES =	
S_FILES =	
H_FILES =	cave.h traverse.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	cave.o traverse.o 

#
# Main targets
#

all:	explore 

explore:	explore.o $(OBJFILES)
	$(CC) $(CFLAGS) -o explore explore.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

cave.o:	cave.h
explore.o:	cave.h traverse.h
traverse.o:	cave.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) explore.o core

realclean:        clean
	-/bin/rm -f explore 
