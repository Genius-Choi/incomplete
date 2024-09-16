gst_asf_demux_parse_data_object_start (GstASFDemux * demux, guint8 * data)
{
  AsfObject obj;

  if (!asf_demux_peek_object (demux, data, 50, &obj, TRUE)) {
    GST_WARNING_OBJECT (demux, "Corrupted data");
    return FALSE;
  }
  if (obj.id != ASF_OBJ_DATA) {
    GST_WARNING_OBJECT (demux, "headers not followed by a DATA object");
    return FALSE;
  }

  demux->state = GST_ASF_DEMUX_STATE_DATA;

  if (!demux->broadcast && obj.size > 50) {
    demux->data_size = obj.size - 50;
    /* CHECKME: for at least one file this is off by +158 bytes?! */
    demux->index_offset = demux->data_offset + demux->data_size;
  } else {
    demux->data_size = 0;
    demux->index_offset = 0;
  }

  demux->packet = 0;

  if (!demux->broadcast) {
    /* skip object header (24 bytes) and file GUID (16 bytes) */
    demux->num_packets = GST_READ_UINT64_LE (data + (16 + 8) + 16);
  } else {
    demux->num_packets = 0;
  }

  if (demux->num_packets == 0)
    demux->seekable = FALSE;

  /* fallback in the unlikely case that headers are inconsistent, can't hurt */
  if (demux->data_size == 0 && demux->num_packets > 0) {
    demux->data_size = demux->num_packets * demux->packet_size;
    demux->index_offset = demux->data_offset + demux->data_size;
  }

  /* process pending stream objects and create pads for those */
  gst_asf_demux_process_queued_extended_stream_objects (demux);

  GST_INFO_OBJECT (demux, "Stream has %" G_GUINT64_FORMAT " packets, "
      "data_offset=%" G_GINT64_FORMAT ", data_size=%" G_GINT64_FORMAT
      ", index_offset=%" G_GUINT64_FORMAT, demux->num_packets,
      demux->data_offset, demux->data_size, demux->index_offset);

  return TRUE;
}
