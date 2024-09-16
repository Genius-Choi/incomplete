g_NPN_MemAlloc(uint32_t size)
{
  D(bugiI("NPN_MemAlloc size=%d\n", size));

  void *ptr = NPW_MemAlloc(size);
  D(bugiD("NPN_MemAlloc return: %p\n", ptr));
  return ptr;
}
