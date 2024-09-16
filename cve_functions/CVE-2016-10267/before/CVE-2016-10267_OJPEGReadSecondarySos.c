OJPEGReadSecondarySos(TIFF* tif, uint16 s)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint8 m;
	assert(s>0);
	assert(s<3);
	assert(sp->sos_end[0].log!=0);
	assert(sp->sos_end[s].log==0);
	sp->plane_sample_offset=(uint8)(s-1);
	while(sp->sos_end[sp->plane_sample_offset].log==0)
		sp->plane_sample_offset--;
	sp->in_buffer_source=sp->sos_end[sp->plane_sample_offset].in_buffer_source;
	sp->in_buffer_next_strile=sp->sos_end[sp->plane_sample_offset].in_buffer_next_strile;
	sp->in_buffer_file_pos=sp->sos_end[sp->plane_sample_offset].in_buffer_file_pos;
	sp->in_buffer_file_pos_log=0;
	sp->in_buffer_file_togo=sp->sos_end[sp->plane_sample_offset].in_buffer_file_togo;
	sp->in_buffer_togo=0;
	sp->in_buffer_cur=0;
	while(sp->plane_sample_offset<s)
	{
		do
		{
			if (OJPEGReadByte(sp,&m)==0)
				return(0);
			if (m==255)
			{
				do
				{
					if (OJPEGReadByte(sp,&m)==0)
						return(0);
					if (m!=255)
						break;
				} while(1);
				if (m==JPEG_MARKER_SOS)
					break;
			}
		} while(1);
		sp->plane_sample_offset++;
		if (OJPEGReadHeaderInfoSecStreamSos(tif)==0)
			return(0);
		sp->sos_end[sp->plane_sample_offset].log=1;
		sp->sos_end[sp->plane_sample_offset].in_buffer_source=sp->in_buffer_source;
		sp->sos_end[sp->plane_sample_offset].in_buffer_next_strile=sp->in_buffer_next_strile;
		sp->sos_end[sp->plane_sample_offset].in_buffer_file_pos=sp->in_buffer_file_pos-sp->in_buffer_togo;
		sp->sos_end[sp->plane_sample_offset].in_buffer_file_togo=sp->in_buffer_file_togo+sp->in_buffer_togo;
	}
	return(1);
}
