#ifndef APPROX_COUNTER_H
#define APPROX_COUNTER_H

#include <pthread.h>

typedef struct {
	int global_value;
	pthread_mutex_t global_lock;
	int *local_values;
	pthread_mutex_t *local_locks;
	int threshold;
	int num_threads;
} approx_counter_t;

int approx_counter_init(approx_counter_t *c, int threshold, int num_threads);
int approx_counter_destroy(approx_counter_t *c);
int approx_counter_update(approx_counter_t *c, int thread_id, int amount);
int approx_counter_get(approx_counter_t *c, int *value);
int approx_counter_flush(approx_counter_t *c);

#endif // APPROX_COUNTER_H