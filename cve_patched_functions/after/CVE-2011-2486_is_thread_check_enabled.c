static inline bool is_thread_check_enabled(void)
{
  static int thread_check = -1;
  if (thread_check < 0)
    thread_check = is_thread_check_enabled_1();
  return thread_check;
}
