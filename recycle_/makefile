CC=c++ -c
CFLAGS=-c -DSTRICT -G3 -Ow -W3 -Zp -Tp
CFLAGSMT=-std=c++11 -municode 
LINKER=c++
GUILIBS=-lole32 -luuid -mwindows -municode
RC=windres
RCFLAGS=-D WIN32 -D _WIN64 -D NDEBUG -D _UNICODE -D UNICODE -O coff
docks : trail build/recycle_.exe

trail :
ifeq ($(wildcard build/.),)
	@mkdir build
endif
 build/recycle_.exe: build/recycle_.o build/recycle_.res
	$(LINKER) $(GUIFLAGS)  build/recycle_.o build/recycle_.res $(GUILIBS) -o build/recycle_.exe

 build/recycle_.o: recycle_.cpp recycle_.h
	$(CC) $(CFLAGSMT) recycle_.cpp -o build/recycle_.o

build/recycle_.res :recycle_.rc
	$(RC) $(RCFLAGS) -i recycle_.rc -o build/recycle_.res

