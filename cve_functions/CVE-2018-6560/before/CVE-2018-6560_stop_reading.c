stop_reading (ProxySide *side)
{
  if (side->in_source)
    {
      g_source_destroy (side->in_source);
      side->in_source = NULL;
    }
}
