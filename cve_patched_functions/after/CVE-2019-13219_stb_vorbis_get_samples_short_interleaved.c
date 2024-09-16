int stb_vorbis_get_samples_short_interleaved(stb_vorbis *f, int channels, short *buffer, int num_shorts)
{
   float **outputs;
   int len = num_shorts / channels;
   int n=0;
   int z = f->channels;
   if (z > channels) z = channels;
   while (n < len) {
      int k = f->channel_buffer_end - f->channel_buffer_start;
      if (n+k >= len) k = len - n;
      if (k)
         convert_channels_short_interleaved(channels, buffer, f->channels, f->channel_buffers, f->channel_buffer_start, k);
      buffer += k*channels;
      n += k;
      f->channel_buffer_start += k;
      if (n == len) break;
      if (!stb_vorbis_get_frame_float(f, NULL, &outputs)) break;
   }
   return n;
}
