OJPEGWriteStreamCompressed(TIFF* tif, void** mem, uint32* len)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	if (sp->in_buffer_togo==0)
	{
		if (OJPEGReadBufferFill(sp)==0)
			return(0);
		assert(sp->in_buffer_togo>0);
	}
	*len=sp->in_buffer_togo;
	*mem=(void*)sp->in_buffer_cur;
	sp->in_buffer_togo=0;
	if (sp->in_buffer_file_togo==0)
	{
		switch(sp->in_buffer_source)
		{
			case osibsStrile:
				if (sp->in_buffer_next_strile<sp->in_buffer_strile_count)
					sp->out_state=ososRst;
				else
					sp->out_state=ososEoi;
				break;
			case osibsEof:
				sp->out_state=ososEoi;
				break;
			default:
				break;
		}
	}
	return(1);
}
