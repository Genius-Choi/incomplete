timespec_add(struct timespec time1, struct timespec time2)
{
  struct timespec result;

  result.tv_sec = time1.tv_sec + time2.tv_sec;
  result.tv_nsec = time1.tv_nsec + time2.tv_nsec;
  if (result.tv_nsec >= 1000000000L)
    {
      result.tv_sec++;
      result.tv_nsec -= 1000000000L;
    }
  return result;
}
