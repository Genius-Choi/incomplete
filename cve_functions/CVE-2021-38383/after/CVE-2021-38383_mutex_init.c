mutex_init(pthread_mutex_t *mutex)
{
  pthread_mutexattr_t mattr;
  int err;

  CHECK_ERR(L_MISC, pthread_mutexattr_init(&mattr));
  CHECK_ERR(L_MISC, pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_ERRORCHECK));
  err = pthread_mutex_init(mutex, &mattr);
  CHECK_ERR(L_MISC, pthread_mutexattr_destroy(&mattr));

  return err;
}
