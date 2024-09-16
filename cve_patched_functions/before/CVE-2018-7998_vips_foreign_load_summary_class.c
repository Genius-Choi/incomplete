vips_foreign_load_summary_class( VipsObjectClass *object_class, VipsBuf *buf )
{
	VipsForeignLoadClass *class = VIPS_FOREIGN_LOAD_CLASS( object_class );

	VIPS_OBJECT_CLASS( vips_foreign_load_parent_class )->
		summary_class( object_class, buf );

	if( !G_TYPE_IS_ABSTRACT( G_TYPE_FROM_CLASS( class ) ) ) {
		if( class->is_a )
			vips_buf_appends( buf, ", is_a" );
		if( class->is_a_buffer )
			vips_buf_appends( buf, ", is_a_buffer" );
		if( class->get_flags )
			vips_buf_appends( buf, ", get_flags" );
		if( class->get_flags_filename )
			vips_buf_appends( buf, ", get_flags_filename" );
		if( class->header )
			vips_buf_appends( buf, ", header" );
		if( class->load )
			vips_buf_appends( buf, ", load" );

		/* You can omit ->load(), you must not omit ->header().
		 */
		g_assert( class->header );
	}
}
