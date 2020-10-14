CPP=g++#compilers being used
H5=h5c++

#directories
IDIR=include
ODIR=bin
SRC_DIR=src
#HDIR=lib/h5
#OPDIR=output

H5FLAGS = -g -Wall -Werror -fopenmp -Iinclude -MMD -MP -lm#Compiler flags for h5c++
CPPFLAGS= -g  -Wall -std=c++11 -Werror -fopenmp -MMD -MP -lm #compiler flags for g++
PYINC = -I/usr/include/python3.8 -lpython3.8
CUDAINC = -I/usr/local/cuda-11.1/include

MPIInc =   -I/usr/include/x86_64-linux-gnu/mpi -L/usr/lib/x86_64-linux-gnu/openmpi/lib
INC = -Iinclude  -I/src/include

LIBS = 	$(INC) $(MPIInc) $(PYINC) $(CUDAINC) #Library Dependecies
HLIBS =  -I/usr/include/hdf5/serial #hdf5 libraries
#CUDALIBS =
_COBJ = Ray.o main.o launchRays.o #Core C++ files being used
COBJ = $(patsubst %,$(ODIR)/%,$(_COBJ))

#_HOBJ = hdf5writer.o #HDF5 related files
#HOBJ = $(patsubst %,$(ODIR)/%,$(_HOBJ))

$(ODIR)/%.o:  $(SRC_DIR)/%.cpp#Compile instructions for individual C++ source files
	$(CPP) -c -fopenmp -g -o $@ $^ $(LIBS)

#$(ODIR)/%.o:  $(HDIR)/%.cpp#Compile instructions for HDF5 I/O files
#	$(H5) -c -fopenmp -g -o $@ $^ $(LIBS)



implSim: $(COBJ) $(HOBJ) #Program compile
	$(CPP) $(CPPFLAGS) -o $@ $^  $(LIBS)

.phony: clean

#removes all object and dependency files, must be run when a change is made to .h files
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(ODIR)/*.d *~ core $(INCDIR)/*~

.phony: reset

reset:
	make clean
	make


.phony: install

install:
	apt-get install libhdf5-serial-dev
	apt-get install hdf5-helpers
	apt-get install python3
	apt-get install python3-matplotlib
	apt-get install python3-numpy
	apt-get install python3-pip
	pip3 install h5py
	apt-get install python3-tk
	apt-get install libomp-dev
