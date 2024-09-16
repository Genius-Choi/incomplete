OJPEGWriteStream(TIFF* tif, void** mem, uint32* len)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	*len=0;
	do
	{
		assert(sp->out_state<=ososEoi);
		switch(sp->out_state)
		{
			case ososSoi:
				OJPEGWriteStreamSoi(tif,mem,len);
				break;
			case ososQTable0:
				OJPEGWriteStreamQTable(tif,0,mem,len);
				break;
			case ososQTable1:
				OJPEGWriteStreamQTable(tif,1,mem,len);
				break;
			case ososQTable2:
				OJPEGWriteStreamQTable(tif,2,mem,len);
				break;
			case ososQTable3:
				OJPEGWriteStreamQTable(tif,3,mem,len);
				break;
			case ososDcTable0:
				OJPEGWriteStreamDcTable(tif,0,mem,len);
				break;
			case ososDcTable1:
				OJPEGWriteStreamDcTable(tif,1,mem,len);
				break;
			case ososDcTable2:
				OJPEGWriteStreamDcTable(tif,2,mem,len);
				break;
			case ososDcTable3:
				OJPEGWriteStreamDcTable(tif,3,mem,len);
				break;
			case ososAcTable0:
				OJPEGWriteStreamAcTable(tif,0,mem,len);
				break;
			case ososAcTable1:
				OJPEGWriteStreamAcTable(tif,1,mem,len);
				break;
			case ososAcTable2:
				OJPEGWriteStreamAcTable(tif,2,mem,len);
				break;
			case ososAcTable3:
				OJPEGWriteStreamAcTable(tif,3,mem,len);
				break;
			case ososDri:
				OJPEGWriteStreamDri(tif,mem,len);
				break;
			case ososSof:
				OJPEGWriteStreamSof(tif,mem,len);
				break;
			case ososSos:
				OJPEGWriteStreamSos(tif,mem,len);
				break;
			case ososCompressed:
				if (OJPEGWriteStreamCompressed(tif,mem,len)==0)
					return(0);
				break;
			case ososRst:
				OJPEGWriteStreamRst(tif,mem,len);
				break;
			case ososEoi:
				OJPEGWriteStreamEoi(tif,mem,len);
				break;
		}
	} while (*len==0);
	return(1);
}
