################################################################################
### CUSTOMIZE BELOW HERE #######################################################

CC=g++ # define the compiler to use
TARGET=project_neurogenesis # define the name of the executable
CFLAGS= -c -std=c++14 -g
LFLAGS= -lm -lsfml-graphics -lsfml-window -lsfml-system -pthread -fopenmp
SRCDIR = src
OBJDIR = obj
NEURODIR = src/neuro
VIEWDIR = src/viewer
SIMDIR = src/sim
INCLUDE = -I./include -I./$(NEURODIR) -I./$(VIEWDIR) -I./$(SIMDIR)
SOURCES = $(foreach d,$(SRCDIR),$(wildcard $(d)/*.cpp))
OBJECTS = $(foreach d,$(SRCDIR),$(subst $(d),$(OBJDIR),$(wildcard $(d)/*.cpp)))

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################


################################################################################
################################################################################

sim: neuro MainSim
	$(CC) \
		$(filter-out $(OBJDIR)/MainView.o, $(wildcard $(OBJDIR)/*.o)) \
		-o sim \
		$(LFLAGS)

viewer: neuro MainViewer
	$(CC) \
		$(filter-out $(OBJDIR)/MainSim.o, $(wildcard $(OBJDIR)/*.o)) \
		-o viewer \
		$(LFLAGS)

neuro: neuro_src

clean:
	rm -f $(OBJDIR)/*
	rm -f viewer sim

clean_viewer:
	rm -f $(OBJDIR)/MainViewer.o
	rm -f viewer

clean_sim:
	rm -f $(OBJDIR)/MainSim.o
	rm -f sim

################################################################################

neuro_src: Config \
	DataSet \
	DataWriter \
	DTree \
	ID \
	InputVector \
	Layer \
	Model \
	ModelBuilder \
	Neuron \
	NTemplate \
	Sim \
	Synapse \


Config: $(OBJDIR)/Config.o

$(OBJDIR)/Config.o: $(NEURODIR)/Config.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/Config.cpp -o $(OBJDIR)/Config.o

DataSet: $(OBJDIR)/DataSet.o

$(OBJDIR)/DataSet.o: $(NEURODIR)/DataSet.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/DataSet.cpp -o $(OBJDIR)/DataSet.o

DataWriter: $(OBJDIR)/DataWriter.o

$(OBJDIR)/DataWriter.o: $(NEURODIR)/DataWriter.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/DataWriter.cpp -o $(OBJDIR)/DataWriter.o

DTree: $(OBJDIR)/DTree.o

$(OBJDIR)/DTree.o: $(NEURODIR)/DTree.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/DTree.cpp -o $(OBJDIR)/DTree.o

ID: $(OBJDIR)/ID.o

$(OBJDIR)/ID.o: $(NEURODIR)/ID.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/ID.cpp -o $(OBJDIR)/ID.o

InputVector: $(OBJDIR)/InputVector.o

$(OBJDIR)/InputVector.o: $(NEURODIR)/InputVector.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/InputVector.cpp -o $(OBJDIR)/InputVector.o

Layer: $(OBJDIR)/Layer.o

$(OBJDIR)/Layer.o: $(NEURODIR)/Layer.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/Layer.cpp -o $(OBJDIR)/Layer.o

MainSim: $(OBJDIR)/MainSim.o

$(OBJDIR)/MainSim.o: $(SIMDIR)/MainSim.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(SIMDIR)/MainSim.cpp -o $(OBJDIR)/MainSim.o

MainViewer: $(OBJDIR)/MainViewer.o

$(OBJDIR)/MainViewer.o: $(VIEWDIR)/MainViewer.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(VIEWDIR)/MainViewer.cpp -o $(OBJDIR)/MainViewer.o

Model: $(OBJDIR)/Model.o

$(OBJDIR)/Model.o: $(NEURODIR)/Model.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/Model.cpp -o $(OBJDIR)/Model.o

ModelBuilder: $(OBJDIR)/ModelBuilder.o

$(OBJDIR)/ModelBuilder.o: $(NEURODIR)/ModelBuilder.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/ModelBuilder.cpp -o $(OBJDIR)/ModelBuilder.o

Neuron: $(OBJDIR)/Neuron.o

$(OBJDIR)/Neuron.o: $(NEURODIR)/Neuron.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/Neuron.cpp -o $(OBJDIR)/Neuron.o

NTemplate: $(OBJDIR)/NTemplate.o

$(OBJDIR)/NTemplate.o: $(NEURODIR)/NTemplate.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/NTemplate.cpp -o $(OBJDIR)/NTemplate.o

Sim: $(OBJDIR)/Sim.o

$(OBJDIR)/Sim.o: $(NEURODIR)/Sim.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/Sim.cpp -o $(OBJDIR)/Sim.o

Synapse: $(OBJDIR)/Synapse.o

$(OBJDIR)/Synapse.o: $(NEURODIR)/Synapse.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(NEURODIR)/Synapse.cpp -o $(OBJDIR)/Synapse.o
