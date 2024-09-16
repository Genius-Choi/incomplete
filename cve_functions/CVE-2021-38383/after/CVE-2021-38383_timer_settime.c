timer_settime(timer_t timer_id, int flags, const struct itimerspec *tp, struct itimerspec *old)
{
  struct itimerval tv;

  if (timer_id != 0 || ! tp || old)
    return -1;

  TIMESPEC_TO_TIMEVAL(&(tv.it_value), &(tp->it_value));
  TIMESPEC_TO_TIMEVAL(&(tv.it_interval), &(tp->it_interval));

  return setitimer(ITIMER_REAL, &tv, NULL);
}
