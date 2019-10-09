#include "approximate_counter.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int thread_id;
	approx_counter_t *c;
} counter_thread_arg_t;

void *counter_thread(void *arg) {
	counter_thread_arg_t *args = arg;
	approx_counter_update(args->c, args->thread_id, 1);
	return NULL;
}

int main(int argc, char *argv[]) {
	approx_counter_t c;
	approx_counter_init(&c, 1024, 4);
	

	exit(EXIT_SUCCESS);
}