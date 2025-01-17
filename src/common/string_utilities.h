/*
 *  string_utilities.h
 *
 *  Copyright 2013 Michael Zillgith
 *
 *	This file is part of libIEC61850.
 *
 *	libIEC61850 is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	libIEC61850 is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with libIEC61850.  If not, see <http://www.gnu.org/licenses/>.
 *
 *	See LICENSE file for the complete license text.
 */

#ifndef STRING_UTILITIES_H_
#define STRING_UTILITIES_H_

#include <stdint.h>

char* copyString(char* string);

/**
 * Concatenate strings. count indicates the number of strings
 * to concatenate.
 */
char* createString(int count, ...);

char* createStringFromBuffer(uint8_t* buf, int size);

#endif /* STRING_UTILITIES_H_ */
