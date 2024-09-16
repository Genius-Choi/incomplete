static int dynamicSeek(struct gdIOCtx *ctx, const int pos)
{
	int bytesNeeded;
	dynamicPtr *dp;
	dpIOCtx *dctx;

	dctx = (dpIOCtx *)ctx;
	dp = dctx->dp;

	if(!dp->dataGood) {
		return FALSE;
	}

	bytesNeeded = pos;
	if(bytesNeeded > dp->realSize) {
		/* 2.0.21 */
		if(!dp->freeOK) {
			return FALSE;
		}

		if(overflow2(dp->realSize, 2)) {
			return FALSE;
		}

		if(!gdReallocDynamic(dp, dp->realSize * 2)) {
			dp->dataGood = FALSE;
			return FALSE;
		}
	}

	/* if we get here, we can be sure that we have enough bytes
	 * to copy safely */

	/* Extend the logical size if we seek beyond EOF. */
	if(pos > dp->logicalSize) {
		dp->logicalSize = pos;
	};

	dp->pos = pos;

	return TRUE;
}
