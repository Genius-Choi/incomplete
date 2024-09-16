passphrase_free(char *ppbuff)
{
	if (ppbuff != NULL) {
		memset(ppbuff, 0, PPBUFF_SIZE);
		free(ppbuff);
	}
}
