OJPEGReadByteAdvance(OJPEGState* sp)
{
	assert(sp->in_buffer_togo>0);
	sp->in_buffer_cur++;
	sp->in_buffer_togo--;
}
