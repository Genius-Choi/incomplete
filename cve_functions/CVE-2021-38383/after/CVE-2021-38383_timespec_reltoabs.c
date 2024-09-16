timespec_reltoabs(struct timespec relative)
{
  struct timespec absolute;

#ifdef CLOCK_REALTIME
  clock_gettime(CLOCK_REALTIME, &absolute);
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  TIMEVAL_TO_TIMESPEC(&tv, &absolute);
#endif
  return timespec_add(absolute, relative);
}
