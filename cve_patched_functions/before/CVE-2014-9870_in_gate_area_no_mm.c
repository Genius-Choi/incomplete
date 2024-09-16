int in_gate_area_no_mm(unsigned long addr)
{
	return in_gate_area(NULL, addr);
}
