vips_tracked_get_files( void )
{
	int n;

	vips_tracked_init(); 

	g_mutex_lock( vips_tracked_mutex );

	n = vips_tracked_files;

	g_mutex_unlock( vips_tracked_mutex );

	return( n );
}
