vips_foreign_find_load( const char *name )
{
	char filename[VIPS_PATH_MAX];
	char option_string[VIPS_PATH_MAX];
	VipsForeignLoadClass *load_class;

	vips__filename_split8( name, filename, option_string );

	if( !vips_existsf( "%s", filename ) ) {
		vips_error( "VipsForeignLoad", 
			_( "file \"%s\" not found" ), name );
		return( NULL );
	}

	if( !(load_class = (VipsForeignLoadClass *) vips_foreign_map( 
		"VipsForeignLoad",
		(VipsSListMap2Fn) vips_foreign_find_load_sub, 
		(void *) filename, NULL )) ) {
		vips_error( "VipsForeignLoad", 
			_( "\"%s\" is not a known file format" ), name );
		return( NULL );
	}

#ifdef DEBUG
	printf( "vips_foreign_find_load: selected %s\n", 
		VIPS_OBJECT_CLASS( load_class )->nickname );
#endif /*DEBUG*/

	return( G_OBJECT_CLASS_NAME( load_class ) );
}
