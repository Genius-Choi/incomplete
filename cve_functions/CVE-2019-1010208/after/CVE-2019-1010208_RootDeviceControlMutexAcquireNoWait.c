BOOL RootDeviceControlMutexAcquireNoWait ()
{
	NTSTATUS status;
	LARGE_INTEGER timeout;
	timeout.QuadPart = 0;

	status = KeWaitForMutexObject (&RootDeviceControlMutex, Executive, KernelMode, FALSE, &timeout);
	return NT_SUCCESS (status) && status != STATUS_TIMEOUT;
}
