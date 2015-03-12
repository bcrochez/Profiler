#ifndef __MACRO__PROFILAGE__
#define __MACRO__PROFILAGE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

static FILE* log = NULL;

#define PROFILE \
	struct timespec start_log, end_log; \
	clock_gettime(CLOCK_REALTIME, &start_log); \
	if(log == NULL) { \
		if((log = fopen("bin/myprofiler.log", "w+")) == NULL) { \
			fprintf(stderr, "Error - fopen\n"); \
			exit(EXIT_FAILURE); \
		} \
	} \
	fprintf(log, "%s -- time : %.0f.%.0fs\n", __FUNCTION__, (double)start_log.tv_sec, (double)start_log.tv_nsec/1000); \


#define return \
	clock_gettime(CLOCK_REALTIME, &end_log); \
	fprintf(log, "END -- time : %.0f.%.0fs\n", (double)end_log.tv_sec, (double)end_log.tv_nsec/1000); \
	if(strcmp(__FUNCTION__, "main") == 0) \
		fclose(log); \
	return

#endif
