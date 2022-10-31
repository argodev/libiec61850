/*
 *  simple_server_example1.c
 *
 *  Example server application using the simple API.
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

#include "iec61850_simple_server_api.h"
#include "thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* import IEC 61850 device model created from SCL-File */
extern IedModel staticIedModel;

static int running = 0;

void sigint_handler(int signalId) {
	running = 0;
}

int main(int argc, char** argv) {

	IedServer iedServer = IedServer_create(&staticIedModel);

	/* This will create default values for the complete IEC model and installs them in the
	 * MMS server's value cache.
	 */
	IedServer_setAllModelDefaultValues(iedServer);


	/* MMS server will be instructed to start listening to client connections. */
	IedServer_start(iedServer);

	running = 1;

	signal(SIGINT, sigint_handler);

	/* Main loop - here we do nothing. IedServer handles all requests by itself */
	while (running) {
		Thread_sleep(1);
	}

	/* stop MMS server - close TCP server socket and all client sockets */
	IedServer_stop(iedServer);

	/* Cleanup - free all resources */
	IedServer_destroy(iedServer);
} /* main() */
