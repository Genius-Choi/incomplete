gst_asf_demux_get_stream_video_format (asf_stream_video_format * fmt,
    guint8 ** p_data, guint64 * p_size)
{
  if (*p_size < (4 + 4 + 4 + 2 + 2 + 4 + 4 + 4 + 4 + 4 + 4))
    return FALSE;

  fmt->size = gst_asf_demux_get_uint32 (p_data, p_size);
  /* Sanity checks */
  if (fmt->size < 40) {
    GST_WARNING ("Corrupted asf_stream_video_format (size < 40)");
    return FALSE;
  }
  if ((guint64) fmt->size - 4 > *p_size) {
    GST_WARNING ("Corrupted asf_stream_video_format (codec_data is too small)");
    return FALSE;
  }
  fmt->width = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->height = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->planes = gst_asf_demux_get_uint16 (p_data, p_size);
  fmt->depth = gst_asf_demux_get_uint16 (p_data, p_size);
  fmt->tag = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->image_size = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->xpels_meter = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->ypels_meter = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->num_colors = gst_asf_demux_get_uint32 (p_data, p_size);
  fmt->imp_colors = gst_asf_demux_get_uint32 (p_data, p_size);
  return TRUE;
}
