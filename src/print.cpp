/*******************************************************************************
 *
 *	 This file is part of Senergy.
 *
 *   Senergy is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Senergy is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Senergy. If not, see <http://www.gnu.org/licenses/>.
 *
 *   Swen Kooij (Photonios) <swenkooij@gmail.com> <photonios@outlook.com>
 *
 *******************************************************************************/

#include <senergy/print.h>

namespace Senergy
{

void Print::Hexadecimal(char *data, int size)
{
	for(int i = 0; i < size; ++i)
		printf("%02X ", data[i]);

	printf("%s", "\n");
}

void Print::Hexadecimal(const std::string &data)
{
	int data_len = (int)data.size();
	for(int i = 0; i < data_len; ++i)
		printf("%02X ", data[i]);

	printf("%s", "\n");
}

void Print::Hexadecimal(char character)
{
	printf("%02X\n", character);	
}

void Print::Integer(int value)
{
	printf("%i\n", value);
}

} // namespace Senergy
