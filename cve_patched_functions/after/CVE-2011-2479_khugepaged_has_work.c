static int khugepaged_has_work(void)
{
	return !list_empty(&khugepaged_scan.mm_head) &&
		khugepaged_enabled();
}
