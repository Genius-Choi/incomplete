LogLuvEncodeStrip(TIFF* tif, uint8* bp, tmsize_t cc, uint16 s)
{
	tmsize_t rowlen = TIFFScanlineSize(tif);

        if (rowlen == 0)
                return 0;

	assert(cc%rowlen == 0);
	while (cc && (*tif->tif_encoderow)(tif, bp, rowlen, s) == 1) {
		bp += rowlen;
		cc -= rowlen;
	}
	return (cc == 0);
}
