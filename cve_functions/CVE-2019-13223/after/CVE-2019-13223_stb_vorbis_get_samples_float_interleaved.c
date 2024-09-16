int stb_vorbis_get_samples_float_interleaved(stb_vorbis *f, int channels, float *buffer, int num_floats)
{
   float **outputs;
   int len = num_floats / channels;
   int n=0;
   int z = f->channels;
   if (z > channels) z = channels;
   while (n < len) {
      int i,j;
      int k = f->channel_buffer_end - f->channel_buffer_start;
      if (n+k >= len) k = len - n;
      for (j=0; j < k; ++j) {
         for (i=0; i < z; ++i)
            *buffer++ = f->channel_buffers[i][f->channel_buffer_start+j];
         for (   ; i < channels; ++i)
            *buffer++ = 0;
      }
      n += k;
      f->channel_buffer_start += k;
      if (n == len)
         break;
      if (!stb_vorbis_get_frame_float(f, NULL, &outputs))
         break;
   }
   return n;
}
