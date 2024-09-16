free_side (ProxySide *side)
{
  g_clear_object (&side->connection);
  g_clear_pointer (&side->extra_input_data, g_bytes_unref);

  g_list_free_full (side->buffers, (GDestroyNotify) buffer_unref);
  g_list_free_full (side->control_messages, (GDestroyNotify) g_object_unref);

  if (side->in_source)
    g_source_destroy (side->in_source);
  if (side->out_source)
    g_source_destroy (side->out_source);

  g_hash_table_destroy (side->expected_replies);
}
