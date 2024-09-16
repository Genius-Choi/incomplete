OJPEGPrintDir(TIFF* tif, FILE* fd, long flags)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint8 m;
	(void)flags;
	assert(sp!=NULL);
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGINTERCHANGEFORMAT))
		fprintf(fd,"  JpegInterchangeFormat: " TIFF_UINT64_FORMAT "\n",(TIFF_UINT64_T)sp->jpeg_interchange_format);  
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGINTERCHANGEFORMATLENGTH))
		fprintf(fd,"  JpegInterchangeFormatLength: " TIFF_UINT64_FORMAT "\n",(TIFF_UINT64_T)sp->jpeg_interchange_format_length);  
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGQTABLES))
	{
		fprintf(fd,"  JpegQTables:");
		for (m=0; m<sp->qtable_offset_count; m++)
			fprintf(fd," " TIFF_UINT64_FORMAT,(TIFF_UINT64_T)sp->qtable_offset[m]);
		fprintf(fd,"\n");
	}
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGDCTABLES))
	{
		fprintf(fd,"  JpegDcTables:");
		for (m=0; m<sp->dctable_offset_count; m++)
			fprintf(fd," " TIFF_UINT64_FORMAT,(TIFF_UINT64_T)sp->dctable_offset[m]);
		fprintf(fd,"\n");
	}
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGACTABLES))
	{
		fprintf(fd,"  JpegAcTables:");
		for (m=0; m<sp->actable_offset_count; m++)
			fprintf(fd," " TIFF_UINT64_FORMAT,(TIFF_UINT64_T)sp->actable_offset[m]);
		fprintf(fd,"\n");
	}
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGPROC))
		fprintf(fd,"  JpegProc: %u\n",(unsigned int)sp->jpeg_proc);
	if (TIFFFieldSet(tif,FIELD_OJPEG_JPEGRESTARTINTERVAL))
		fprintf(fd,"  JpegRestartInterval: %u\n",(unsigned int)sp->restart_interval);
	if (sp->printdir)
		(*sp->printdir)(tif, fd, flags);
}
