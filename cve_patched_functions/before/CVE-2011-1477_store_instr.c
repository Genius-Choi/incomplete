static int store_instr(int instr_no, struct sbi_instrument *instr)
{
	if (instr->key != FM_PATCH && (instr->key != OPL3_PATCH || devc->model != 2))
		printk(KERN_WARNING "FM warning: Invalid patch format field (key) 0x%x\n", instr->key);
	memcpy((char *) &(devc->i_map[instr_no]), (char *) instr, sizeof(*instr));
	return 0;
}
