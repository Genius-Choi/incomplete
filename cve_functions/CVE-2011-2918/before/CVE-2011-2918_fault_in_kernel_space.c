static int fault_in_kernel_space(unsigned long address)
{
	return address >= TASK_SIZE_MAX;
}
