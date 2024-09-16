static int vfio_intx_enable(struct vfio_pci_device *vdev)
{
	if (!is_irq_none(vdev))
		return -EINVAL;

	if (!vdev->pdev->irq)
		return -ENODEV;

	vdev->ctx = kzalloc(sizeof(struct vfio_pci_irq_ctx), GFP_KERNEL);
	if (!vdev->ctx)
		return -ENOMEM;

	vdev->num_ctx = 1;

	/*
	 * If the virtual interrupt is masked, restore it.  Devices
	 * supporting DisINTx can be masked at the hardware level
	 * here, non-PCI-2.3 devices will have to wait until the
	 * interrupt is enabled.
	 */
	vdev->ctx[0].masked = vdev->virq_disabled;
	if (vdev->pci_2_3)
		pci_intx(vdev->pdev, !vdev->ctx[0].masked);

	vdev->irq_type = VFIO_PCI_INTX_IRQ_INDEX;

	return 0;
}
