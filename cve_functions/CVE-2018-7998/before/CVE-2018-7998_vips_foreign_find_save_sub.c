vips_foreign_find_save_sub( VipsForeignSaveClass *save_class, 
	const char *filename )
{
	VipsForeignClass *class = VIPS_FOREIGN_CLASS( save_class );

	/* The suffs might be defined on an abstract base class, make sure we
	 * don't pick that.
	 */
	if( !G_TYPE_IS_ABSTRACT( G_TYPE_FROM_CLASS( class ) ) &&
		class->suffs &&
		vips_filename_suffix_match( filename, class->suffs ) )
		return( save_class );

	return( NULL );
}
