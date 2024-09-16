void sspi_SecBufferAlloc(PSecBuffer SecBuffer, size_t size)
{
	SecBuffer->cbBuffer = size;
	SecBuffer->pvBuffer = malloc(size);
	ZeroMemory(SecBuffer->pvBuffer, SecBuffer->cbBuffer);
}
