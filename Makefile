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
#   along with WhatsDesk.  If not, see <http://www.gnu.org/licenses/>.
#
#   Swen Kooij (Photonios) <swenkooij@gmail.com> <photonios@outlook.com>
#
#################################################################################

INVOKE=make -s
SOURCE_DIR=./src

all:
	$(INVOKE) -C $(SOURCE_DIR) all

docs: .FORCE
	doxygen docs/Doxyfile

commit: .FORCE
	$(INVOKE) docs
	git gui

.FORCE:

.DEFAULT:
	$(INVOKE) -C $(SOURCE_DIR) $@
