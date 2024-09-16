timer_delete(timer_t timer_id)
{
  struct itimerval timerval;

  if (timer_id != 0)
    return -1;

  memset(&timerval, 0, sizeof(struct itimerval));

  return setitimer(ITIMER_REAL, &timerval, NULL);
}
