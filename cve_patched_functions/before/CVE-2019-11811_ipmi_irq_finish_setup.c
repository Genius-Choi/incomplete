void ipmi_irq_finish_setup(struct si_sm_io *io)
{
	if (io->si_type == SI_BT)
		/* Enable the interrupt in the BT interface. */
		io->outputb(io, IPMI_BT_INTMASK_REG,
			    IPMI_BT_INTMASK_ENABLE_IRQ_BIT);
}
