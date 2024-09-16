static void entersafe_reverse_buffer(u8* buff,size_t size)
{
	 u8 t;
	 u8 * end=buff+size-1;

	 while(buff<end)
	 {
		  t = *buff;
		  *buff = *end;
		  *end=t;
		  ++buff;
		  --end;
	 }
}
