#################################################################################
#
#	This file is part of Senergy.
#
#   Senergy is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Senergy is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Senergy.  If not, see <http://www.gnu.org/licenses/>.
#
#   Swen Kooij (Photonios) <swenkooij@gmail.com> <photonios@outlook.com>
#
#################################################################################

INVOKE_SELF=make -s

BASE_DIR=../
SOURCE_DIR=$(BASE_DIR)src/
OUTPUT_DIR=$(BASE_DIR)bin/
OUTPUT_FILE=senergy-dns
OUTPUT_PATH=$(OUTPUT_DIR)$(OUTPUT_FILE)

CXX=g++

CXXPATHS=-I/usr/include -I$(SOURCE_DIR)
CXXFLAGS=-std=c++11 -g 

LDPATHS=
LDFLAGS=

SOURCES=$(wildcard $(SOURCE_DIR)*.cpp)

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(OUTPUT_PATH)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(OUTPUT_DIR)
	@echo Linking....
	@$(CXX) $(LDPATHS) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	@echo Done.

.cpp.o:
	@echo Compiling $< into $@
	@$(CXX) $(CXXPATHS) $(CXXFLAGS) -c $(LDFLAGS) $(LDPATHS) $< -o $@
	
rebuild:
	$(INVOKE_SELF) clean
	$(INVOKE_SELF)

clean:
	rm -rf *.o

