static int dwc3_gadget_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct dwc3		*dwc = gadget_to_dwc(g);
	unsigned long		flags;
	int			ret = 0;
	int			irq;

	irq = dwc->irq_gadget;
	ret = request_threaded_irq(irq, dwc3_interrupt, dwc3_thread_interrupt,
			IRQF_SHARED, "dwc3", dwc->ev_buf);
	if (ret) {
		dev_err(dwc->dev, "failed to request irq #%d --> %d\n",
				irq, ret);
		goto err0;
	}

	spin_lock_irqsave(&dwc->lock, flags);
	if (dwc->gadget_driver) {
		dev_err(dwc->dev, "%s is already bound to %s\n",
				dwc->gadget.name,
				dwc->gadget_driver->driver.name);
		ret = -EBUSY;
		goto err1;
	}

	dwc->gadget_driver	= driver;

	if (pm_runtime_active(dwc->dev))
		__dwc3_gadget_start(dwc);

	spin_unlock_irqrestore(&dwc->lock, flags);

	return 0;

err1:
	spin_unlock_irqrestore(&dwc->lock, flags);
	free_irq(irq, dwc);

err0:
	return ret;
}
