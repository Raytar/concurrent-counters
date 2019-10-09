#ifndef SAFE_COUNTER_H
#define SAFE_COUNTER_H

#include <pthread.h>

typedef struct {
	int value;
	pthread_mutex_t mutex;
} safe_counter_t;

int safe_counter_init(safe_counter_t *c);
int safe_counter_destroy(safe_counter_t *c);
int safe_counter_increment(safe_counter_t *c);
int safe_counter_decrement(safe_counter_t *c);
int safe_counter_get(safe_counter_t *c, int *value);

#endif // SAFE_COUNTER_H