vips_tracked_get_allocs( void )
{
	int n;

	vips_tracked_init(); 

	g_mutex_lock( vips_tracked_mutex );

	n = vips_tracked_allocs;

	g_mutex_unlock( vips_tracked_mutex );

	return( n );
}
