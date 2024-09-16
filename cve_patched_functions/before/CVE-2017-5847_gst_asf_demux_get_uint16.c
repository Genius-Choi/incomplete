gst_asf_demux_get_uint16 (guint8 ** p_data, guint64 * p_size)
{
  guint16 ret;

  g_assert (*p_size >= 2);
  ret = GST_READ_UINT16_LE (*p_data);
  *p_data += sizeof (guint16);
  *p_size -= sizeof (guint16);
  return ret;
}
