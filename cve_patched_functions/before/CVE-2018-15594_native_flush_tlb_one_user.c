static void native_flush_tlb_one_user(unsigned long addr)
{
	__native_flush_tlb_one_user(addr);
}
