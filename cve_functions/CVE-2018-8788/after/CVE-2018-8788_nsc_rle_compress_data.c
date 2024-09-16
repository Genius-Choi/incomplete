static void nsc_rle_compress_data(NSC_CONTEXT* context)
{
	UINT16 i;
	UINT32 planeSize;
	UINT32 originalSize;

	for (i = 0; i < 4; i++)
	{
		originalSize = context->OrgByteCount[i];

		if (originalSize == 0)
		{
			planeSize = 0;
		}
		else
		{
			planeSize = nsc_rle_encode(context->priv->PlaneBuffers[i],
			                           context->priv->PlaneBuffers[4], originalSize);

			if (planeSize < originalSize)
				CopyMemory(context->priv->PlaneBuffers[i], context->priv->PlaneBuffers[4],
				           planeSize);
			else
				planeSize = originalSize;
		}

		context->PlaneByteCount[i] = planeSize;
	}
}
