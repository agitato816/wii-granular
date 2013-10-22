current:
	echo make pd_linux, pd_nt, or pd_darwin

clean: ; rm -f *.pd_linux *.o

# ----------------------- NT -----------------------

pd_nt: square~.dll

.SUFFIXES: .obj .dll

PDNTCFLAGS = /W3 /WX /DNT /DPD /nologo
VC="D:\Program Files\Microsoft Visual Studio\Vc98"

PDNTINCLUDE = /I. /I\tcl\include /I..\..\src /I$(VC)\include

PDNTLDIR = $(VC)\lib
PDNTLIB = $(PDNTLDIR)\libc.lib \
	$(PDNTLDIR)\oldnames.lib \
	$(PDNTLDIR)\kernel32.lib \
	..\..\bin\pd.lib 

.c.dll:
	cl $(PDNTCFLAGS) $(PDNTINCLUDE) /c $*.c
	link /dll /export:$*_setup $*.obj $(PDNTLIB)

# override explicitly for tilde objects like this:
dspobj~.dll: dspobj~.c; 
	cl $(PDNTCFLAGS) $(PDNTINCLUDE) /c $*.c
	link /dll /export:dspobj_tilde_setup $*.obj $(PDNTLIB)



# ----------------------- Mac OSX -----------------------

pd_darwin: square~.pd_darwin

.SUFFIXES: .pd_darwin

DARWINCFLAGS = -DPD -O2 -Wall -W -Wshadow -Wstrict-prototypes \
    -Wno-unused -Wno-parentheses -Wno-switch -arch i386 

DARWININCLUDE =  -I./src

.c.pd_darwin:
	cc $(DARWINCFLAGS) $(DARWININCLUDE) -o $*.o -c $*.c
	cc -bundle -arch i386 -undefined suppress -flat_namespace -o $*.pd_darwin $*.o 
	rm -f $*.o

