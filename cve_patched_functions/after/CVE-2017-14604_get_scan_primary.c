get_scan_primary (OpKind kind)
{
    switch (kind)
    {
        default:
        case OP_KIND_COPY:
        {
            return f (_("Error while copying."));
        }

        case OP_KIND_MOVE:
        {
            return f (_("Error while moving."));
        }

        case OP_KIND_DELETE:
        {
            return f (_("Error while deleting."));
        }

        case OP_KIND_TRASH:
        {
            return f (_("Error while moving files to trash."));
        }

        case OP_KIND_COMPRESS:
            return f (_("Error while compressing files."));
    }
}
