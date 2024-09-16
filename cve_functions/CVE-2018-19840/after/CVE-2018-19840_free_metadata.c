void free_metadata (WavpackMetadata *wpmd)
{
    if (wpmd->data) {
        free (wpmd->data);
        wpmd->data = NULL;
    }
}
