static int get8_packet(vorb *f)
{
   int x = get8_packet_raw(f);
   f->valid_bits = 0;
   return x;
}
