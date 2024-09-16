int jpc_bitstream_putbit_func(jpc_bitstream_t *bitstream, int b)
{
	int ret;
	JAS_DBGLOG(1000, ("jpc_bitstream_putbit_func(%p, %d)\n", bitstream, b));
	ret = jpc_bitstream_putbit_macro(bitstream, b);
	JAS_DBGLOG(1000, ("jpc_bitstream_putbit_func() -> %d\n", ret));
	return ret;
}
