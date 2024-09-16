bool thread_check(void)
{
#ifdef ENABLE_THREAD_CHECK
  if (is_thread_check_enabled())
	return (g_main_thread == pthread_self());
#endif
  return true;
}
