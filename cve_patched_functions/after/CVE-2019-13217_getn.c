static int getn(vorb *z, uint8 *data, int n)
{
   if (USE_MEMORY(z)) {
      if (z->stream+n > z->stream_end) { z->eof = 1; return 0; }
      memcpy(data, z->stream, n);
      z->stream += n;
      return 1;
   }

   #ifndef STB_VORBIS_NO_STDIO   
   if (fread(data, n, 1, z->f) == 1)
      return 1;
   else {
      z->eof = 1;
      return 0;
   }
   #endif
}
