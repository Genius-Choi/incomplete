OJPEGReadBlock(OJPEGState* sp, uint16 len, void* mem)
{
	uint16 mlen;
	uint8* mmem;
	uint16 n;
	assert(len>0);
	mlen=len;
	mmem=mem;
	do
	{
		if (sp->in_buffer_togo==0)
		{
			if (OJPEGReadBufferFill(sp)==0)
				return(0);
			assert(sp->in_buffer_togo>0);
		}
		n=mlen;
		if (n>sp->in_buffer_togo)
			n=sp->in_buffer_togo;
		_TIFFmemcpy(mmem,sp->in_buffer_cur,n);
		sp->in_buffer_cur+=n;
		sp->in_buffer_togo-=n;
		mlen-=n;
		mmem+=n;
	} while(mlen>0);
	return(1);
}
