static void pmcraid_release_minor(unsigned short minor)
{
	__clear_bit(minor, pmcraid_minor);
}
