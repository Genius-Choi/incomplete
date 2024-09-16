static uint32 get32(vorb *f)
{
   uint32 x;
   x = get8(f);
   x += get8(f) << 8;
   x += get8(f) << 16;
   x += (uint32) get8(f) << 24;
   return x;
}
