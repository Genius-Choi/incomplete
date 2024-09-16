OJPEGLibjpegJpegErrorMgrOutputMessage(jpeg_common_struct* cinfo)
{
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)(cinfo,buffer);
	TIFFWarningExt(((TIFF*)(cinfo->client_data))->tif_clientdata,"LibJpeg","%s",buffer);
}
