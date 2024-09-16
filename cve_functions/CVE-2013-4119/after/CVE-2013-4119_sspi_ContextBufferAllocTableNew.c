void sspi_ContextBufferAllocTableNew()
{
	size_t size;

	ContextBufferAllocTable.cEntries = 0;
	ContextBufferAllocTable.cMaxEntries = 4;

	size = sizeof(CONTEXT_BUFFER_ALLOC_ENTRY) * ContextBufferAllocTable.cMaxEntries;

	ContextBufferAllocTable.entries = malloc(size);
	ZeroMemory(ContextBufferAllocTable.entries, size);
}
