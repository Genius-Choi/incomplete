gst_asf_demux_check_buffer_is_header (GstASFDemux * demux, GstBuffer * buf)
{
  AsfObject obj;
  GstMapInfo map;
  gboolean valid;
  g_assert (buf != NULL);

  GST_LOG_OBJECT (demux, "Checking if buffer is a header");

  gst_buffer_map (buf, &map, GST_MAP_READ);

  /* we return false on buffer too small */
  if (map.size < ASF_OBJECT_HEADER_SIZE) {
    gst_buffer_unmap (buf, &map);
    return FALSE;
  }

  /* check if it is a header */
  valid =
      asf_demux_peek_object (demux, map.data, ASF_OBJECT_HEADER_SIZE, &obj,
      TRUE);
  gst_buffer_unmap (buf, &map);
  if (valid && obj.id == ASF_OBJ_HEADER) {
    return TRUE;
  }
  return FALSE;
}
