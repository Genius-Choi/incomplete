OJPEGVGetField(TIFF* tif, uint32 tag, va_list ap)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	switch(tag)
	{
		case TIFFTAG_JPEGIFOFFSET:
			*va_arg(ap,uint64*)=(uint64)sp->jpeg_interchange_format;
			break;
		case TIFFTAG_JPEGIFBYTECOUNT:
			*va_arg(ap,uint64*)=(uint64)sp->jpeg_interchange_format_length;
			break;
		case TIFFTAG_YCBCRSUBSAMPLING:
			if (sp->subsamplingcorrect_done==0)
				OJPEGSubsamplingCorrect(tif);
			*va_arg(ap,uint16*)=(uint16)sp->subsampling_hor;
			*va_arg(ap,uint16*)=(uint16)sp->subsampling_ver;
			break;
		case TIFFTAG_JPEGQTABLES:
			*va_arg(ap,uint32*)=(uint32)sp->qtable_offset_count;
			*va_arg(ap,void**)=(void*)sp->qtable_offset; 
			break;
		case TIFFTAG_JPEGDCTABLES:
			*va_arg(ap,uint32*)=(uint32)sp->dctable_offset_count;
			*va_arg(ap,void**)=(void*)sp->dctable_offset;  
			break;
		case TIFFTAG_JPEGACTABLES:
			*va_arg(ap,uint32*)=(uint32)sp->actable_offset_count;
			*va_arg(ap,void**)=(void*)sp->actable_offset;
			break;
		case TIFFTAG_JPEGPROC:
			*va_arg(ap,uint16*)=(uint16)sp->jpeg_proc;
			break;
		case TIFFTAG_JPEGRESTARTINTERVAL:
			*va_arg(ap,uint16*)=sp->restart_interval;
			break;
		default:
			return (*sp->vgetparent)(tif,tag,ap);
	}
	return (1);
}
