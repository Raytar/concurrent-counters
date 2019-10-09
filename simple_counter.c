#include "simple_counter.h"

void simple_counter_init(simple_counter_t *c) {
	c->value = 0;
}

void simple_counter_increment(simple_counter_t *c) {
	c->value++;
}

void simple_counter_decrement(simple_counter_t *c) {
	c->value--;
}

int simple_counter_get(simple_counter_t *c) {
	return c->value;
}