static int decode_space_limit(struct xdr_stream *xdr, u64 *maxsize)
{
        __be32 *p;
	uint32_t limit_type, nblocks, blocksize;

	READ_BUF(12);
	READ32(limit_type);
	switch (limit_type) {
		case 1:
			READ64(*maxsize);
			break;
		case 2:
			READ32(nblocks);
			READ32(blocksize);
			*maxsize = (uint64_t)nblocks * (uint64_t)blocksize;
	}
	return 0;
}
