vips_foreign_load_gif_ext_next( VipsForeignLoadGif *gif, 
	GifByteType **extension )
{
	if( DGifGetExtensionNext( gif->file, extension ) == GIF_ERROR ) {
		vips_foreign_load_gif_error( gif ); 
		return( -1 ); 
	}

	if( *extension ) 
		VIPS_DEBUG_MSG( "gifload: EXTENSION_NEXT\n" ); 

	return( 0 );
}
