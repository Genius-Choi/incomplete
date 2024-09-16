gst_asf_demux_activate_mode (GstPad * sinkpad, GstObject * parent,
    GstPadMode mode, gboolean active)
{
  gboolean res;
  GstASFDemux *demux;

  demux = GST_ASF_DEMUX (parent);

  switch (mode) {
    case GST_PAD_MODE_PUSH:
      demux->state = GST_ASF_DEMUX_STATE_HEADER;
      demux->streaming = TRUE;
      res = TRUE;
      break;
    case GST_PAD_MODE_PULL:
      if (active) {
        demux->state = GST_ASF_DEMUX_STATE_HEADER;
        demux->streaming = FALSE;

        res = gst_pad_start_task (sinkpad, (GstTaskFunction) gst_asf_demux_loop,
            demux, NULL);
      } else {
        res = gst_pad_stop_task (sinkpad);
      }
      break;
    default:
      res = FALSE;
      break;
  }
  return res;
}
