void sspi_GlobalFinish()
{
	if (sspi_initialized)
	{
		sspi_ContextBufferAllocTableFree();
	}

	sspi_initialized = FALSE;
}
