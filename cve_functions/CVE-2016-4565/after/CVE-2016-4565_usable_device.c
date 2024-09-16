static int usable_device(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd = dd->pport;

	return driver_lstate(ppd) == IB_PORT_ACTIVE;
}
