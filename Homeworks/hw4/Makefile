#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Jun 21 17:00:24 2023
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


CFLAGS = -ggdb -std=c99 -Wall -Wextra -pedantic 


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	EventTime.c tedtalk.c tedtalktest.c
PS_FILES =	
S_FILES =	
H_FILES =	EventTime.h tedtalk.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	EventTime.o tedtalk.o 

#
# Main targets
#

all:	tedtalktest 

tedtalktest:	tedtalktest.o $(OBJFILES)
	$(CC) $(CFLAGS) -o tedtalktest tedtalktest.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

EventTime.o:	EventTime.h
tedtalk.o:	EventTime.h tedtalk.h
tedtalktest.o:	EventTime.h tedtalk.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) tedtalktest.o core

realclean:        clean
	-/bin/rm -f tedtalktest 
