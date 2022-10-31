/*
 *  mms_server_example.c
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

#include "mms_server.h"
#include "mms_mapping.h"

#include <signal.h>

extern IedModel staticIedModel;

static MmsMapping mmsMapping;

static IsoServer isoServer;

static MmsServer mmsServer;

static int running = 1;

void sigint_handler(int sign) {
	running = 0;
}

static void mmsConnectionHandler (void* parameter, MmsServerConnection* connection, MmsServerEvent event) {
	if (event == MMS_SERVER_NEW_CONNECTION) {
		printf("New connection\n");
	}
	else {
		printf("Connection closed!\n");
	}
}

static MmsValue* readVariableHandler (void* object, MmsDomain* domain, char* variableId) {
	MmsTypeSpecification* typeSpec = MmsDomain_getNamedVariable(domain, variableId);

	MmsValue* value = NULL;

	switch(typeSpec->type) {
	case MMS_ARRAY:
		value = MmsValue_createArray(typeSpec->typeSpec.array.elementTypeSpec,
				typeSpec->typeSpec.array.elementCount);
		break;
	case MMS_UTC_TIME:
		value = MmsValue_newUtcTime(time(NULL));
		break;
	case MMS_INTEGER:
		value = MmsValue_newIntegerFromInt32(12345678);
		break;
	case MMS_VISIBLE_STRING:
		value = MmsValue_newVisibleString("teststring");
		break;
	case MMS_FLOAT:
		if (typeSpec->typeSpec.floatingpoint.formatWidth == 64) {
			value = MmsValue_newDouble(0.12345f);
		}
		else {
			value = MmsValue_newFloat(0.12345f);
		}
		break;
	default:
		value = MmsValue_newDefaultValue(typeSpec);
		break;
	}

	if (value != NULL)
		MmsValue_setDeletable(value);

	return value;
}

int main(int argc, char** argv) {
	MmsMapping_init(&mmsMapping, &staticIedModel);
	MmsDevice* mmsDevice = MmsMapping_getMmsDeviceModel(&mmsMapping);

	isoServer = IsoServer_create();

	mmsServer = MmsServer_create(isoServer, mmsDevice);

	MmsServer_installReadHandler(mmsServer, readVariableHandler, NULL);
	MmsServer_installConnectionHandler(mmsServer, mmsConnectionHandler, NULL);

	MmsServer_startListening(mmsServer);

	running = 1;

	signal(SIGINT, sigint_handler);

	while (running) {
		usleep(100);
	}

	MmsServer_stopListening(mmsServer);

	MmsServer_destroy(mmsServer);

	IsoServer_destroy(isoServer);
} /* main() */
