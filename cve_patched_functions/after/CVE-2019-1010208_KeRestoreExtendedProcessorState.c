VOID NTAPI KeRestoreExtendedProcessorState (
	PXSTATE_SAVE XStateSave
	)
{
	if (KeRestoreExtendedProcessorStatePtr)
	{
		(KeRestoreExtendedProcessorStatePtr) (XStateSave);
	}
}