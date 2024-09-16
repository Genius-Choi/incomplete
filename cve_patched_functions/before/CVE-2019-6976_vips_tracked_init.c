vips_tracked_init( void )
{
	static GOnce vips_tracked_once = G_ONCE_INIT;

	VIPS_ONCE( &vips_tracked_once, 
		(GThreadFunc) vips_tracked_init_mutex, NULL );
}
