memcheck_seq_cmp(MEMCHECK *m1, MEMCHECK *m2)
{
	return m1->seq_num - m2->seq_num;
}
