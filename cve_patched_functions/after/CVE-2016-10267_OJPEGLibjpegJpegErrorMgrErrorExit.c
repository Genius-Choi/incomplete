OJPEGLibjpegJpegErrorMgrErrorExit(jpeg_common_struct* cinfo)
{
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)(cinfo,buffer);
	TIFFErrorExt(((TIFF*)(cinfo->client_data))->tif_clientdata,"LibJpeg","%s",buffer);
	jpeg_encap_unwind((TIFF*)(cinfo->client_data));
}
