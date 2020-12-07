# to add audio:
# 1. you need to install some packages. on my machine this worked:
#    sudo apt-get install phonon-backend-gstreamer libphonon-dev
# 2. run 'make fresh audio=y' and use audio=y every time you run make
# 3. see if ./earth works
# 4. if you get error about .mid files, more packages needed. I used:
#    sudo apt-get install ubuntu-restricted-extras vlc-plugin-fluidsynth
#    (use tab and space to navigate the weird dialogs)
#    or just don't use .mid files

CXX = g++
# if needed, install from http://bits.usc.edu/cs103/compile/ or use g++ or clang++

# tries later to check if it's the course VM, and changes CXX to 'compile'

all: draw.o turtle.o threestep shape vanish x

clean:
	rm -f draw.o turtle.o threestep shape vanish x

fresh: clean all

#INCL = -I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui
OFLAGS = $(INCL) -Wall -Wno-unreachable-code -Wno-return-type
FLAGS = -g -Wall -lpng -lz



draw.o: draw.cpp draw.h
	$(CXX) $(OFLAGS) $(FLAGS)  draw.cpp -c

turtle.o: turtle.cpp turtle.h
	$(CXX) turtle.cpp $(OFLAGS) -c -o turtle.o

threestep: threestep.cpp draw.o turtle.o draw.h
	$(CXX) $@.cpp draw.o turtle.o $(FLAGS) -o $@

shape: shape.cpp draw.o turtle.o draw.h
	$(CXX) $@.cpp draw.o turtle.o $(FLAGS) -o $@

vanish: vanish.cpp draw.o turtle.o draw.h
	$(CXX) $@.cpp draw.o turtle.o $(FLAGS) -o $@

art: art.cpp draw.o turtle.o draw.h
	$(CXX) $@.cpp draw.o turtle.o $(FLAGS) -o $@

x: x.cpp draw.o turtle.o draw.h
	$(CXX) $@.cpp draw.o turtle.o $(FLAGS) -o $@
