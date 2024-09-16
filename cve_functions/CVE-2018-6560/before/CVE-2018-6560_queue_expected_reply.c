queue_expected_reply (ProxySide *side, guint32 serial, ExpectedReplyType type)
{
  g_hash_table_replace (side->expected_replies,
                        GUINT_TO_POINTER (serial),
                        GUINT_TO_POINTER (type));
}
