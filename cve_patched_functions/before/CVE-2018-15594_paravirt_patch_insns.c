unsigned paravirt_patch_insns(void *insnbuf, unsigned len,
			      const char *start, const char *end)
{
	unsigned insn_len = end - start;

	if (insn_len > len || start == NULL)
		insn_len = len;
	else
		memcpy(insnbuf, start, insn_len);

	return insn_len;
}
