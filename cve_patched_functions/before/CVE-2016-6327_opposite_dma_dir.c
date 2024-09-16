enum dma_data_direction opposite_dma_dir(enum dma_data_direction dir)
{
	switch (dir) {
	case DMA_TO_DEVICE:	return DMA_FROM_DEVICE;
	case DMA_FROM_DEVICE:	return DMA_TO_DEVICE;
	default:		return dir;
	}
}
