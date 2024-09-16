g_NPN_MemFree(void *ptr)
{
  D(bugiI("NPN_MemFree ptr=%p\n", ptr));
  NPW_MemFree(ptr);
  D(bugiD("NPN_MemFree done\n"));
}
