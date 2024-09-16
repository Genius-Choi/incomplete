VOID TCUnloadDriver (PDRIVER_OBJECT DriverObject)
{
	Dump ("TCUnloadDriver BEGIN\n");

	OnShutdownPending();

	if (IsBootDriveMounted())
		TC_BUG_CHECK (STATUS_INVALID_DEVICE_STATE);

	EncryptionThreadPoolStop();
	TCDeleteDeviceObject (RootDeviceObject, (PEXTENSION) RootDeviceObject->DeviceExtension);

	Dump ("TCUnloadDriver END\n");
}
