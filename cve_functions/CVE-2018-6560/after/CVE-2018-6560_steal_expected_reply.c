steal_expected_reply (ProxySide *side, guint32 serial)
{
  ExpectedReplyType type;

  type = GPOINTER_TO_UINT (g_hash_table_lookup (side->expected_replies,
                                                GUINT_TO_POINTER (serial)));
  if (type)
    g_hash_table_remove (side->expected_replies,
                         GUINT_TO_POINTER (serial));
  return type;
}
