/*
 *  ber_integer.h
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

#ifndef BER_INTEGER_H_
#define BER_INTEGER_H_

#include "asn1_ber_primitive_value.h"

Asn1PrimitiveValue* BerInteger_createFromBuffer(uint8_t* buf, int size);

Asn1PrimitiveValue* BerInteger_createInt32();

int BerInteger_setFromBerInteger(Asn1PrimitiveValue* self, Asn1PrimitiveValue* value);

int BerInteger_setInt32(Asn1PrimitiveValue* self, int32_t value);

Asn1PrimitiveValue* BerInteger_createFromInt32(int32_t value);

int BerInteger_setUint32(Asn1PrimitiveValue* self, uint32_t value);

Asn1PrimitiveValue* BerInteger_createFromUint32(uint32_t value);

Asn1PrimitiveValue* BerInteger_createFromInt64(int64_t value);

Asn1PrimitiveValue* BerInteger_createInt64();

int BerInteger_setInt64(Asn1PrimitiveValue* self, int64_t value);

/* 1 - if conversion is possible, 0 - out of range */
int BerInteger_toInt32(Asn1PrimitiveValue* self, int32_t* nativeValue);

/* 1 - if conversion is possible, 0 - out of range */
int BerInteger_toUint32(Asn1PrimitiveValue* self, uint32_t* nativeValue);

/* 1 - if conversion is possible, 0 - out of range */
int BerInteger_toInt64(Asn1PrimitiveValue* self, int64_t* nativeValue);

#endif /* BER_INTEGER_H_ */
