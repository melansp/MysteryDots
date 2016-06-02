# GNU Makefile
CXX=g++
LINK=$(CXX)

TARGET:=MysteryDots

# Directories
SRCDIR:=src
INCDIR:=include
BUILDDIR:=obj
TARGETDIR:=bin
RESDIR:=res
SRCEXT:=cpp
OBJEXT:=o

#Flags, Libraries and Includes
CFLAGS:= -Wall -std=c++1y
LIB:=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INC:= -I$(INCDIR)


#------------------------------------------------------------------------------
SRCS:=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS:=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.$(OBJEXT)))

#Default Make
all: resources $(TARGET)

#Remake
remake: clean all

#Copy Resources Dir to Target Dir
resources:directories
	@cp -R $(RESDIR) $(TARGETDIR)/

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)

#Link
$(TARGET): $(OBJS)
	$(LINK) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(INC) -c -o $@  $<


#Non-File Targets
.PHONY: all remake clean resources
	
