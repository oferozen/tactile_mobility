#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

typedef struct _timer_t* timer_t;

timer_t timer_create();
void timer_destroy (timer_t timer);
void timer_update(timer_t timer);
int timer_s_diff(timer_t timer);
int timer_ms_diff(timer_t timer);

#endif /* SRC_TIMER_H_ */
