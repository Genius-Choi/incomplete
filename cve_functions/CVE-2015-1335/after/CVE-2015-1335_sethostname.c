static int sethostname(const char * name, size_t len)
{
#ifdef __NR_sethostname
return syscall(__NR_sethostname, name, len);
#else
errno = ENOSYS;
return -1;
#endif
}
