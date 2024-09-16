void kgdb_roundup_cpus(unsigned long flags)
{
	apic->send_IPI_allbutself(APIC_DM_NMI);
}
