LogLuvDecodeTile(TIFF* tif, uint8* bp, tmsize_t cc, uint16 s)
{
	tmsize_t rowlen = TIFFTileRowSize(tif);

        if (rowlen == 0)
                return 0;

	assert(cc%rowlen == 0);
	while (cc && (*tif->tif_decoderow)(tif, bp, rowlen, s)) {
		bp += rowlen;
		cc -= rowlen;
	}
	return (cc == 0);
}
