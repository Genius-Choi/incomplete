void sspi_SecureHandleInvalidate(SecHandle* handle)
{
	if (!handle)
		return;

	sspi_SecureHandleInit(handle);
}
