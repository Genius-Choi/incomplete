void DefragDestroy(void)
{
    DefragHashShutdown();
    DefragContextDestroy(defrag_context);
    defrag_context = NULL;
    DefragTreeDestroy();
}
