#include "approximate_counter.h"
#include <stdlib.h>

int approx_counter_init(approx_counter_t *c, int threshold, int num_threads) {
	c->global_value = 0;
	c->threshold = threshold;
	c->num_threads = num_threads;
	c->local_values = calloc(num_threads, sizeof(int));
	if (!c->local_values) return -1;
	c->local_locks = malloc(sizeof(pthread_mutex_t) * num_threads);
	if (!c->local_locks) return -1;
	// initialize locks
	int rc = pthread_mutex_init(&c->global_lock, NULL);
	for (int i = 0; i < num_threads; i++) {
		rc = pthread_mutex_init(&c->local_locks[i], NULL);
	}
	if (rc) return -1;
	return 0;
}

int approx_counter_destroy(approx_counter_t *c) {
	free(c->local_values);
	// destroy locks
	int rc = pthread_mutex_destroy(&c->global_lock);
	for (int i = 0; i < c->num_threads; i++) {
		rc = pthread_mutex_destroy(&c->local_locks[i]);
	}
	free(c->local_locks);
	return rc;
}

int approx_counter_update(approx_counter_t *c, int thread_id, int amount) {
	int rc = 0;
	int thread = thread_id % c->num_threads;
	// get local lock
	rc = pthread_mutex_lock(&c->local_locks[thread]);
	if (rc) return -1;
	
	c->local_values[thread] += amount;

	if (c->local_values[thread] > c->threshold) {
		// get global lock
		rc = pthread_mutex_lock(&c->global_lock);
		if (rc) goto unlock_local;

		c->global_value += c->local_values[thread];

		rc = pthread_mutex_unlock(&c->global_lock);
		if (rc) goto unlock_local;

		c->local_values[thread] = 0;
	}

unlock_local:
	rc = pthread_mutex_unlock(&c->local_locks[thread]);

	return rc;
}

int approx_counter_get(approx_counter_t *c, int *value) {
	int rc = pthread_mutex_lock(&c->global_lock);
	if (rc) return -1;
	*value = c->global_value;
	rc = pthread_mutex_unlock(&c->global_lock);
	if (rc) return -1;
	return 0;
}

// add all local values to the global
int approx_counter_flush(approx_counter_t *c) {
	int rc = 0;
	rc = pthread_mutex_lock(&c->global_lock);
	if (rc) return -1;
	for (int i = 0; i < c->num_threads; i++) {
		rc = pthread_mutex_lock(&c->local_locks[i]);
		if (rc) goto unlock_global;
		c->global_value += c->local_values[i];
		c->local_values[i] = 0;
		rc = pthread_mutex_unlock(&c->local_locks[i]);
		if (rc) goto unlock_global;
	}
unlock_global:
	rc = pthread_mutex_unlock(&c->global_lock);
	return rc;
}