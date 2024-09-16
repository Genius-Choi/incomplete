void sspi_GlobalInit()
{
	if (!sspi_initialized)
	{
		SSL_load_error_strings();
		SSL_library_init();

		sspi_ContextBufferAllocTableNew();
		sspi_initialized = TRUE;
	}
}
