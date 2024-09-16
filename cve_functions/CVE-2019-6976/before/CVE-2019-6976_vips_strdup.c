vips_strdup( VipsObject *object, const char *str )
{
	char *str_dup;

	str_dup = g_strdup( str );

        if( object ) {
		g_signal_connect( object, "postclose", 
			G_CALLBACK( vips_malloc_cb ), str_dup );
		object->local_memory += strlen( str );
	}

	return( str_dup );
}
