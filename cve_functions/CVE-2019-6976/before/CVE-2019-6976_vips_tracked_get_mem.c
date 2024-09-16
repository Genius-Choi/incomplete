vips_tracked_get_mem( void )
{
	size_t mem;

	vips_tracked_init(); 

	g_mutex_lock( vips_tracked_mutex );

	mem = vips_tracked_mem;

	g_mutex_unlock( vips_tracked_mutex );

	return( mem );
}
