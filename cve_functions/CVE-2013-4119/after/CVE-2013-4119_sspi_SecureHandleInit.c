void sspi_SecureHandleInit(SecHandle* handle)
{
	if (!handle)
		return;

	memset(handle, 0xFF, sizeof(SecHandle));
}
