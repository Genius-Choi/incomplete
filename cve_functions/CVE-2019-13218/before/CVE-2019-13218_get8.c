static uint8 get8(vorb *z)
{
   if (USE_MEMORY(z)) {
      if (z->stream >= z->stream_end) { z->eof = TRUE; return 0; }
      return *z->stream++;
   }

   #ifndef STB_VORBIS_NO_STDIO
   {
   int c = fgetc(z->f);
   if (c == EOF) { z->eof = TRUE; return 0; }
   return c;
   }
   #endif
}
