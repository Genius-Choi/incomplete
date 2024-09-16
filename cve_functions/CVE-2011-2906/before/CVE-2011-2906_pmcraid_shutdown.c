static void pmcraid_shutdown(struct pci_dev *pdev)
{
	struct pmcraid_instance *pinstance = pci_get_drvdata(pdev);
	pmcraid_reset_bringdown(pinstance);
}
