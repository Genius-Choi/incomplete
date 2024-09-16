static bool is_thread_check_enabled_1(void)
{
  const char *thread_check_str;
  if ((thread_check_str =  getenv("NPW_THREAD_CHECK")) != NULL)
    return ((strcmp(thread_check_str, "yes") == 0) ||
			(strcmp(thread_check_str, "1") == 0));

  /* enable main-thread checks by default for all builds from snapshots */
  return NPW_SNAPSHOT > 0;
}
