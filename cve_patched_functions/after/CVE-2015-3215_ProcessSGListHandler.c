VOID ProcessSGListHandler(
    IN PDEVICE_OBJECT  pDO,
    IN PVOID  Reserved,
    IN PSCATTER_GATHER_LIST  pSGL,
    IN PVOID  Context
    )
{
    UNREFERENCED_PARAMETER(Reserved);
    UNREFERENCED_PARAMETER(pDO);

    auto NBHolder = static_cast<CNB*>(Context);
    NBHolder->MappingDone(pSGL);
}
