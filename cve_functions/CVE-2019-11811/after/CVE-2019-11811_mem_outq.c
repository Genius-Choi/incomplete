static void mem_outq(const struct si_sm_io *io, unsigned int offset,
		     unsigned char b)
{
	writeq((u64)b << io->regshift, (io->addr)+(offset * io->regspacing));
}
