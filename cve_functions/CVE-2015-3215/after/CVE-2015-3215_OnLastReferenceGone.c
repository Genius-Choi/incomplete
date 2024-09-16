void CNBL::OnLastReferenceGone()
{
    Destroy(this, m_Context->MiniportHandle);
}
