static void *plugin_instance_allocate(void)
{
  return NPW_MemNew0(PluginInstance, 1);
}
