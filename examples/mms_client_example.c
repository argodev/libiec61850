/*
 *  mms_client_example.c
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

#include <stdlib.h>
#include <stdio.h>
#include "mms_client_connection.h"

int main(int argc, char** argv) {

	char* hostname;
	int tcpPort = 102;

	if (argc > 1)
		hostname = argv[1];
	else
		hostname = "localhost";

	if (argc > 2)
		tcpPort = atoi(argv[2]);

	MmsConnection con = MmsConnection_create();

	MmsIndication indication;

	/* use authentication */
	AcseAuthenticationParameter auth = calloc(1, sizeof(struct sAcseAuthenticationParameter));
	auth->mechanism = AUTH_PASSWORD;
	auth->value.password.string = "testpw";

	IsoConnectionParameters* connectionParams = calloc(1, sizeof(IsoConnectionParameters));
	connectionParams->acseAuthParameter = auth;

	MmsConnection_setIsoConnectionParameters(con, connectionParams);

	indication = MmsConnection_connect(con, hostname, tcpPort);

	if (indication != MMS_OK) {
		printf("MMS connect failed!\n");
		goto exit;
	}
	else
		printf("MMS connected.\n\n");

	printf("Domains present on server:\n--------------------------\n");
	LinkedList nameList = MmsConnection_getDomainNames(con);
	LinkedList_printStringList(nameList);
	LinkedList_destroy(nameList);
	printf("\n");


	printf("Named variables for domain SampleIEDDevice1:\n--------------------------------------------\n");
	nameList = MmsConnection_getDomainVariableNames(con, "SampleIEDDevice1");
	LinkedList_printStringList(nameList);
	LinkedList_destroy(nameList);
	printf("\n");

	printf("Data sets for domain SampleIEDDevice1:\n--------------------------------------------\n");
	nameList = MmsConnection_getDomainVariableListNames(con, "SampleIEDDevice1");
	LinkedList_printStringList(nameList);
	LinkedList_destroy(nameList);
	printf("\n");

	MmsValue* value;

	MmsConnection_getVariableAccessAttributes(con, "SampleIEDDevice1", "MMXU2$MX$TotW");

	value = MmsConnection_readVariable(con, "SampleIEDDevice1", "MMXU2$MX$TotW$mag$f");

	printf("Read variable with value: %f\n", MmsValue_toFloat(value));

	MmsValue_setFloat(value, 1.234f);

	MmsConnection_writeVariable(con, "SampleIEDDevice1", "MMXU2$MX$TotW$mag$f", value);

	MmsValue_delete(value);

	value = MmsConnection_readVariable(con, "SampleIEDDevice1", "MMXU2$MX$TotW$mag$f");

	printf("Read variable with value: %f\n", MmsValue_toFloat(value));

	MmsValue_delete(value);

	value = MmsConnection_readVariable(con, "SampleIEDDevice1", "DGEN1$ST$Beh$stVal");

	printf("Read integer variable with value: %i\n", MmsValue_toInt32(value));

	MmsValue_delete(value);

exit:
	MmsConnection_destroy(con);
}
