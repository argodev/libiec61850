/*
 *  ied_value.h
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

#ifndef IED_VALUE_H_
#define IED_VALUE_H_

typedef struct sIedValue* IedValue;

enum eIedType {
	IED_TYPE_ARRAY,
	IED_TYPE_STRUCTURE
};

IedValue
IedValue_getType(IedValue value);

#endif /* IED_VALUE_H_ */
