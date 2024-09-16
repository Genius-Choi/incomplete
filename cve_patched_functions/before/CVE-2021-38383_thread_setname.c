thread_setname(pthread_t thread, const char *name)
{
#if defined(HAVE_PTHREAD_SETNAME_NP)
  pthread_setname_np(thread, name);
#elif defined(HAVE_PTHREAD_SET_NAME_NP)
  pthread_set_name_np(thread, name);
#endif
}
