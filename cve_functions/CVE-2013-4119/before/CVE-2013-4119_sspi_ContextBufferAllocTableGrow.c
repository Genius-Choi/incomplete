void sspi_ContextBufferAllocTableGrow()
{
	size_t size;
	ContextBufferAllocTable.cEntries = 0;
	ContextBufferAllocTable.cMaxEntries *= 2;

	size = sizeof(CONTEXT_BUFFER_ALLOC_ENTRY) * ContextBufferAllocTable.cMaxEntries;

	ContextBufferAllocTable.entries = realloc(ContextBufferAllocTable.entries, size);
	ZeroMemory((void*) &ContextBufferAllocTable.entries[ContextBufferAllocTable.cMaxEntries / 2], size / 2);
}
