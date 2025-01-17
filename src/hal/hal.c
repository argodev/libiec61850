/*
 *  hal.c
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


#include "hal.h"

#include <time.h>

#if defined __linux__ || defined __APPLE__

#if defined __MACH__ || defined __linux__

#include <sys/time.h>

#if defined __MACH__
#define CLOCK_REALTIME 1
#endif


int clock_gettime(int dummy, struct timespec* t) {
	struct timeval now;
	int rv = gettimeofday(&now, NULL);
	if (rv) return rv;
	t->tv_sec = now.tv_sec;
	t->tv_nsec = now.tv_usec * 1000;
}

#endif

uint64_t Hal_getTimeInMs() {
	struct timespec tp;

	clock_gettime(CLOCK_REALTIME, &tp);

	return tp.tv_sec * 1000 + (tp.tv_nsec / 1000000);
}

#elif defined _WIN32
#include "windows.h"

uint64_t Hal_getTimeInMs() {
	FILETIME ft;
	uint64_t ll_now;
	GetSystemTimeAsFileTime(&ft);

	ll_now = (LONGLONG)ft.dwLowDateTime + ((LONGLONG)(ft.dwHighDateTime) << 32LL);

	return ll_now;
}
#endif
