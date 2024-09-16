OJPEGReadBytePeek(OJPEGState* sp, uint8* byte)
{
	if (sp->in_buffer_togo==0)
	{
		if (OJPEGReadBufferFill(sp)==0)
			return(0);
		assert(sp->in_buffer_togo>0);
	}
	*byte=*(sp->in_buffer_cur);
	return(1);
}
