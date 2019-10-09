#include "safe_counter.h"

int safe_counter_init(safe_counter_t *c) {
	c->value = 0;
	int rc = pthread_mutex_init(&c->mutex, NULL);
	if (rc) return -1;
	return 0;
}

int safe_counter_destroy(safe_counter_t *c) {
	int rc = pthread_mutex_destroy(&c->mutex);
	if (rc != 0) return -1;
	return 0;
}

int safe_counter_increment(safe_counter_t *c) {
	int rc;

	rc = pthread_mutex_lock(&c->mutex);
	if (rc) return -1;

	c->value++;

	rc = pthread_mutex_unlock(&c->mutex);
	if (rc) return -1;

	return 0;
}

int safe_counter_decrement(safe_counter_t *c) {
	int rc;

	rc = pthread_mutex_lock(&c->mutex);
	if (rc) return -1;

	c->value--;

	rc = pthread_mutex_unlock(&c->mutex);
	if (rc) return -1;

	return 0;
}

int safe_counter_get(safe_counter_t *c, int *value) {
	int rc;

	rc = pthread_mutex_lock(&c->mutex);
	if (rc) return -1;

	*value = c->value;

	rc = pthread_mutex_unlock(&c->mutex);
	if (rc) return -1;

	return 0;
}
