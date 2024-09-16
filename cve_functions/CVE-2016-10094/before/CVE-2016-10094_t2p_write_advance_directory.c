t2p_write_advance_directory(T2P* t2p, TIFF* output)
{
	t2p_disable(output);
	if(!TIFFWriteDirectory(output)){
		TIFFError(TIFF2PDF_MODULE, 
			"Error writing virtual directory to output PDF %s", 
			TIFFFileName(output));
		t2p->t2p_error = T2P_ERR_ERROR;
		return;
	}
	t2p_enable(output);
	return;
}
