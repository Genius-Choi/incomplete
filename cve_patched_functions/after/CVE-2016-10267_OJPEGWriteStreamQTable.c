OJPEGWriteStreamQTable(TIFF* tif, uint8 table_index, void** mem, uint32* len)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	if (sp->qtable[table_index]!=0)
	{
		*mem=(void*)(sp->qtable[table_index]+sizeof(uint32));
		*len=*((uint32*)sp->qtable[table_index])-sizeof(uint32);
	}
	sp->out_state++;
}
