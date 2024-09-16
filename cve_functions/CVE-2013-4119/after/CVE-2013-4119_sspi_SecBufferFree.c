void sspi_SecBufferFree(PSecBuffer SecBuffer)
{
	free(SecBuffer->pvBuffer);
	SecBuffer->pvBuffer = NULL;
	SecBuffer->cbBuffer = 0;
}
