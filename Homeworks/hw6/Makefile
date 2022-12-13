#
# Created by gmakemake (Ubuntu Jul 25 2014) on Thu Oct 27 12:38:10 2022
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

CFLAGS = -std=c99 -ggdb -Wall -Wextra -pedantic

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	Matrix.c mtest1.c mtest2.c mtest3.c mtest4.c mtest5.c mtest6.c mtest7.c
PS_FILES =	
S_FILES =	
H_FILES =	Matrix.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Matrix.o 

#
# Main targets
#

all:	mtest1 mtest2 mtest3 mtest4 mtest5 mtest6 mtest7 

mtest1:	mtest1.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest1 mtest1.o $(OBJFILES) $(CLIBFLAGS)

mtest2:	mtest2.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest2 mtest2.o $(OBJFILES) $(CLIBFLAGS)

mtest3:	mtest3.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest3 mtest3.o $(OBJFILES) $(CLIBFLAGS)

mtest4:	mtest4.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest4 mtest4.o $(OBJFILES) $(CLIBFLAGS)

mtest5:	mtest5.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest5 mtest5.o $(OBJFILES) $(CLIBFLAGS)

mtest6:	mtest6.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest6 mtest6.o $(OBJFILES) $(CLIBFLAGS)

mtest7:	mtest7.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mtest7 mtest7.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

Matrix.o:	
mtest1.o:	Matrix.h
mtest2.o:	Matrix.h
mtest3.o:	Matrix.h
mtest4.o:	Matrix.h
mtest5.o:	Matrix.h
mtest6.o:	Matrix.h
mtest7.o:	Matrix.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mtest1.o mtest2.o mtest3.o mtest4.o mtest5.o mtest6.o mtest7.o core

realclean:        clean
	-/bin/rm -f mtest1 mtest2 mtest3 mtest4 mtest5 mtest6 mtest7 
