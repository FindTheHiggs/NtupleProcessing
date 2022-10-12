CXX     = g++
LD      = g++

# ana skel. dirs here
OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = NtupAnaSkeleton
INC_DIR = NtupAnaSkeleton

ROOTCINT     = rootcint
ROOTCONFIG   = root-config
ROOTCXXFLAGS = $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS     = $(shell $(ROOTCONFIG) --libs)
#ROOFITLIBS = -lRooFitCore
SOFLAGS      = -shared
 
LIBS = $(ROOTLIBS)
#$(ROOFITLIBS)
INC = -I$(INC_DIR) 

DEBUG        = false
ifeq ($(DEBUG),true)
	CXXFLAGS     = -O0 -Wall -ggdb -fPIC $(INC) $(ROOTCXXFLAGS)
	LDFLAGS      = -O0 -Wall -ggdb $(INC) $(ROOTCXXFLAGS)
else
	CXXFLAGS     = -O2 -Wall -fPIC $(INC) $(ROOTCXXFLAGS)
	LDFLAGS      = -O2 -Wall $(INC) $(ROOTCXXFLAGS)
endif

$(SRC_DIR)/%.cxx : $(INC_DIR)/%.h

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# file targets
OBJECT_AS = $(OBJ_DIR)/NtupAnaSkeleton.o
OBJECT_RUNANA=$(OBJ_DIR)/RunNtupAna.o

# main targets
MAIN_RUNANA = $(BIN_DIR)/RunNtupAna

# rules
all:  $(MAIN_RUNANA)

runana: $(MAIN_RUNANA)

# deps
$(MAIN_RUNANA): $(OBJECT_RUNANA) $(OBJECT_AS)
	$(CXX) $(CXXFLAGS) -o $@ -g $^ $(LIBS)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/[^C]*
