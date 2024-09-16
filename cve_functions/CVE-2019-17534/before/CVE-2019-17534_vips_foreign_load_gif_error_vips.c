vips_foreign_load_gif_error_vips( VipsForeignLoadGif *gif, int error )
{
	VipsObjectClass *class = VIPS_OBJECT_GET_CLASS( gif );

	const char *message;

	if( (message = vips_foreign_load_gif_errstr( error )) )
		vips_error( class->nickname, "%s", message ); 
}
