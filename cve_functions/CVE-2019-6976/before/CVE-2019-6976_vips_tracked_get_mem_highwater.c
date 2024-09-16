vips_tracked_get_mem_highwater( void )
{
	size_t mx;

	vips_tracked_init(); 

	g_mutex_lock( vips_tracked_mutex );

	mx = vips_tracked_mem_highwater;

	g_mutex_unlock( vips_tracked_mutex );

	return( mx );
}
