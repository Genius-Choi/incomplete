static void skip(vorb *z, int n)
{
   if (USE_MEMORY(z)) {
      z->stream += n;
      if (z->stream >= z->stream_end) z->eof = 1;
      return;
   }
   #ifndef STB_VORBIS_NO_STDIO
   {
      long x = ftell(z->f);
      fseek(z->f, x+n, SEEK_SET);
   }
   #endif
}
