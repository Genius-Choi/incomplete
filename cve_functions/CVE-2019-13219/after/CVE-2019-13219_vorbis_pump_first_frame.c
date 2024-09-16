static int vorbis_pump_first_frame(stb_vorbis *f)
{
   int len, right, left, res;
   res = vorbis_decode_packet(f, &len, &left, &right);
   if (res)
      vorbis_finish_frame(f, len, left, right);
   return res;
}
