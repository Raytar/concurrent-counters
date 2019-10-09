#ifndef SIMPLE_COUNTER_H
#define SIMPLE_COUNTER_H

typedef struct {
	int value;
} simple_counter_t;

void simple_counter_init(simple_counter_t *c);
void simple_counter_increment(simple_counter_t *c);
void simple_counter_decrement(simple_counter_t *c);
int simple_counter_get(simple_counter_t *c);

#endif // SIMPLE_COUNTER_H