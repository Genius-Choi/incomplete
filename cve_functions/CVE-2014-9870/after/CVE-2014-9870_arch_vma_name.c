const char *arch_vma_name(struct vm_area_struct *vma)
{
	return (vma == &gate_vma) ? "[vectors]" : NULL;
}
