vips_malloc_cb( VipsObject *object, char *buf )
{
	g_free( buf );
}
