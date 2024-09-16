void __init *set_except_vector(int n, void *addr)
{
	unsigned long handler = (unsigned long) addr;
	unsigned long old_handler = exception_handlers[n];

	exception_handlers[n] = handler;
	if (n == 0 && cpu_has_divec) {
		unsigned long jump_mask = ~((1 << 28) - 1);
		u32 *buf = (u32 *)(ebase + 0x200);
		unsigned int k0 = 26;
		if ((handler & jump_mask) == ((ebase + 0x200) & jump_mask)) {
			uasm_i_j(&buf, handler & ~jump_mask);
			uasm_i_nop(&buf);
		} else {
			UASM_i_LA(&buf, k0, handler);
			uasm_i_jr(&buf, k0);
			uasm_i_nop(&buf);
		}
		local_flush_icache_range(ebase + 0x200, (unsigned long)buf);
	}
	return (void *)old_handler;
}
