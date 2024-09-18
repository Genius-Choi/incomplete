static void cryp_dma_done(struct cryp_ctx *ctx)
{
	struct dma_chan *chan;

	dev_dbg(ctx->device->dev, "[%s]: ", __func__);

	chan = ctx->device->dma.chan_mem2cryp;
	dmaengine_device_control(chan, DMA_TERMINATE_ALL, 0);
	dma_unmap_sg(chan->device->dev, ctx->device->dma.sg_src,
		     ctx->device->dma.sg_src_len, DMA_TO_DEVICE);

	chan = ctx->device->dma.chan_cryp2mem;
	dmaengine_device_control(chan, DMA_TERMINATE_ALL, 0);
	dma_unmap_sg(chan->device->dev, ctx->device->dma.sg_dst,
		     ctx->device->dma.sg_dst_len, DMA_FROM_DEVICE);
}
