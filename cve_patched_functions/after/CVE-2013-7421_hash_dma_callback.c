static void hash_dma_callback(void *data)
{
	struct hash_ctx *ctx = data;

	complete(&ctx->device->dma.complete);
}
