
CROSS_COMPILE := arm-hisiv300-linux-
RM  := rm -f
AR  := $(CROSS_COMPILE)ar
CC  := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
SRTIP := $(CROSS_COMPILE)strip

DEFINES  :=
INCLUDES := ../include ../include/hi3531a
LIBRARYS := ../lib
LDLIBS   := pthread mpi jpeg6b upvqe dnvqe VoiceEngine

CFLAGS	 += $(strip $(addprefix -D,$(DEFINES)) $(addprefix -I,$(INCLUDES)) $(addprefix -L,$(LIBRARYS)) $(addprefix -l,$(LDLIBS)))
CXXFLAGS += $(strip $(addprefix -D,$(DEFINES)) $(addprefix -I,$(INCLUDES)) $(addprefix -L,$(LIBRARYS)) $(addprefix -l,$(LDLIBS)))

CFLAGS   += -std=c11 -fPIC -g -Wall -Wno-deprecated-declarations -pedantic -pedantic-error -Werror
CXXFLAGS += -std=c++11 -fPIC -g -Wno-deprecated-declarations

PREFIX :=

DIRS := 3rdparty base channel device media misc platform platform/hisilicon server stream utils

SRCS :=  $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp)) main.cpp
		 
OBJS := $(SRCS:%.cpp=%.o)


STATIC_TARGET :=
SHARED_TARGET :=
EXECUTE_TARGET :=iSee


all: $(STATIC_TARGET) $(SHARED_TARGET) $(EXECUTE_TARGET)
	
$(STATIC_TARGET) : $(OBJS)
	$(AR) -rcs $(STATIC_TARGET) $(OBJS)
	
$(SHARED_TARGET) : $(OBJS)
	$(CXX) -shared -fPIC -o $(SHARED_TARGET) $(OBJS)

$(EXECUTE_TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTE_TARGET) $(OBJS)
	
strip:
	$(SRTIP) -s $(STATIC_TARGET) $(SHARED_TARGET)
	
install: all
	
clean :
	$(RM) $(OBJS)
	$(RM) $(STATIC_TARGET)
	$(RM) $(SHARED_TARGET)