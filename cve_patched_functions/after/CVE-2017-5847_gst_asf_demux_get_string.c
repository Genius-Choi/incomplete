gst_asf_demux_get_string (gchar ** p_str, guint16 * p_strlen,
    guint8 ** p_data, guint64 * p_size)
{
  guint16 s_length;
  guint8 *s;

  *p_str = NULL;

  if (*p_size < 2)
    return FALSE;

  s_length = gst_asf_demux_get_uint16 (p_data, p_size);

  if (p_strlen)
    *p_strlen = s_length;

  if (s_length == 0) {
    GST_WARNING ("zero-length string");
    *p_str = g_strdup ("");
    return TRUE;
  }

  if (!gst_asf_demux_get_bytes (&s, s_length, p_data, p_size))
    return FALSE;

  g_assert (s != NULL);

  /* just because They don't exist doesn't
   * mean They are not out to get you ... */
  if (s[s_length - 1] != '\0') {
    s = g_realloc (s, s_length + 1);
    s[s_length] = '\0';
  }

  *p_str = (gchar *) s;
  return TRUE;
}
