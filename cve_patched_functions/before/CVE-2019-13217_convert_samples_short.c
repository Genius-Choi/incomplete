static void convert_samples_short(int buf_c, short **buffer, int b_offset, int data_c, float **data, int d_offset, int samples)
{
   int i;
   if (buf_c != data_c && buf_c <= 2 && data_c <= 6) {
      static int channel_selector[3][2] = { {0}, {PLAYBACK_MONO}, {PLAYBACK_LEFT, PLAYBACK_RIGHT} };
      for (i=0; i < buf_c; ++i)
         compute_samples(channel_selector[buf_c][i], buffer[i]+b_offset, data_c, data, d_offset, samples);
   } else {
      int limit = buf_c < data_c ? buf_c : data_c;
      for (i=0; i < limit; ++i)
         copy_samples(buffer[i]+b_offset, data[i]+d_offset, samples);
      for (   ; i < buf_c; ++i)
         memset(buffer[i]+b_offset, 0, sizeof(short) * samples);
   }
}
