
CROSS_COMPILE := arm-hisiv300-linux-
RM  := rm -f
AR  := $(CROSS_COMPILE)ar
CC  := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
STRIP := $(CROSS_COMPILE)strip

DEFINES  := PLATFORM_HISI
INCLUDES := ../include ../include/hi3531a
LIBRARYS := ../lib
LDLIBS   := pthread mpi jpeg6b upvqe dnvqe VoiceEngine

CFLAGS	 += $(strip $(addprefix -D,$(DEFINES)) $(addprefix -I,$(INCLUDES)) $(addprefix -L,$(LIBRARYS)) $(addprefix -l,$(LDLIBS)))
CXXFLAGS += $(strip $(addprefix -D,$(DEFINES)) $(addprefix -I,$(INCLUDES)) $(addprefix -L,$(LIBRARYS)) $(addprefix -l,$(LDLIBS)))

CFLAGS   += -std=c11 -fPIC -g -Wall -Wno-deprecated-declarations -pedantic -pedantic-error -Werror
CXXFLAGS += -std=c++11 -fPIC -g -Wno-deprecated-declarations

PREFIX :=../mtd/app

BUILDDIR := ../build

DIRS := 3rdparty base channel device media misc platform platform/hisilicon server stream utils

SRCS :=  $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp)) main.cpp
		 
#OBJS := $(SRCS:%.cpp=%.o)
OBJS := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))

$(foreach dir,$(DIRS),$(shell mkdir $(BUILDDIR)/$(dir) -p))
$(shell mkdir $(PREFIX) -p)


STATIC_TARGET :=
SHARED_TARGET :=
EXECUTE_TARGET :=iSee


all: $(STATIC_TARGET) $(SHARED_TARGET) $(EXECUTE_TARGET)

$(OBJS):$(BUILDDIR)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(STATIC_TARGET) : $(OBJS)
	$(AR) -rcs $(STATIC_TARGET) $(OBJS)
	
$(SHARED_TARGET) : $(OBJS)
	$(CXX) -shared -fPIC $(OBJS) -o $(SHARED_TARGET)

$(EXECUTE_TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXECUTE_TARGET)
	
strip:
	$(SRTIP) -s $(STATIC_TARGET) $(SHARED_TARGET)
	
install: all
	$(STRIP) --strip-unneeded $(EXECUTE_TARGET)
	tar -zcf $(EXECUTE_TARGET).tar.gz $(EXECUTE_TARGET)
	mv $(EXECUTE_TARGET).tar.gz $(PREFIX)/ -f
	
clean:
	$(RM) $(OBJS)
	$(RM) $(STATIC_TARGET) $(SHARED_TARGET) $(EXECUTE_TARGET)
