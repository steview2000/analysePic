O =		obj
S =		src
LIB = 	include

all	: avTiff avPower avflat flatten background tiffTest bnr2tiff

avflat	: $O/avflat.o $O/tiffFunc.o
	cc -o avflat $O/avflat.o $O/tiffFunc.o -ltiff

avPower	: $O/avPower.o $O/tiffFunc.o
	cc -o avPower $O/avPower.o $O/tiffFunc.o -ltiff


avTiff	: $O/avTiff.o $O/tiffFunc.o
	cc -o avTiff $O/avTiff.o $O/tiffFunc.o -ltiff


bnr2tiff: $O/bnr2tiff.o $O/tiffFunc.o
	cc -o bnr2tiff $O/bnr2tiff.o $O/tiffFunc.o -ltiff -lm

fftTest	: $O/fftTest.o $O/fftFunc.o $(LIB)/fftFunc.h $O/tiffFunc.o
	cc -o fftTest $O/fftFunc.o $O/fftTest.o $O/tiffFunc.o -ltiff -lm -lfftw3

flatten : $O/tiffFunc.o $O/flatten.o
	cc -o flatten $O/flatten.o $O/tiffFunc.o -ltiff

background : $O/tiffFunc.o $O/background.o
	cc -o background $O/background.o $O/tiffFunc.o -ltiff

tiffTest : $O/tiffFunc.o $O/tiffTest.o
	cc -o tiffTest $O/tiffTest.o $O/tiffFunc.o -ltiff

$O/avTiff.o : $S/avTiff.c $(LIB)/tiffFunc.h
	cc -c -g $S/avTiff.c
	mv avTiff.o $O/	

$O/avPower.o : $S/avPower.c $(LIB)/tiffFunc.h
	cc -c -g $S/avPower.c
	mv avPower.o $O/

$O/avflat.o : $S/avflat.c $(LIB)/tiffFunc.h
	cc -c -g $S/avflat.c
	mv avflat.o $O/

$O/bnr2tiff.o : $S/bnr2tiff.c $(LIB)/tiffFunc.h
	cc -c -g $S/bnr2tiff.c
	mv bnr2tiff.o $O/

$O/flatten.o : $S/flatten.c $(LIB)/tiffFunc.h
	cc -c $S/flatten.c
	mv flatten.o $O/

$O/background.o : $S/background.c $(LIB)/tiffFunc.h
	cc -c $S/background.c
	mv background.o $O/


$O/tiffFunc.o : $S/tiffFunc.c $(LIB)/tiffFunc.h
	cc -c -g $S/tiffFunc.c
	mv tiffFunc.o $O/


$O/tiffTest.o : $S/tiffTest.c $(LIB)/tiffFunc.h
	cc -c -g $S/tiffTest.c 
	mv tiffTest.o $O/

#fftFunc.o : fftFunc.c fftFunc.h
#	cc -c fftFunc.c

#fftTest.o : fftTest.c fftFunc.c fftFunc.h
#	cc -c fftTest.c
