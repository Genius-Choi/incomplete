static void entersafe_encode_bignum(u8 tag,sc_pkcs15_bignum_t bignum,u8** ptr)
{
	 u8 *p=*ptr;

	 *p++=tag;
	 if(bignum.len<128)
	 {
		  *p++=(u8)bignum.len;
	 }
	 else
	 {
		  u8 bytes=1;
		  size_t len=bignum.len;
		  while(len)
		  {
			   len=len>>8;
			   ++bytes;
		  }
		  bytes&=0x0F;
		  *p++=0x80|bytes;
		  while(bytes)
		  {
			   *p++=bignum.len>>((bytes-1)*8);
			   --bytes;
		  }
	 }
	 memcpy(p,bignum.data,bignum.len);
	 entersafe_reverse_buffer(p,bignum.len);
	 p+=bignum.len;
	 *ptr = p;
}
