HandleCompatMapFile(CompatInfo *info, XkbFile *file, enum merge_mode merge)
{
    bool ok;

    merge = (merge == MERGE_DEFAULT ? MERGE_AUGMENT : merge);

    free(info->name);
    info->name = strdup_safe(file->name);

    for (ParseCommon *stmt = file->defs; stmt; stmt = stmt->next) {
        switch (stmt->type) {
        case STMT_INCLUDE:
            ok = HandleIncludeCompatMap(info, (IncludeStmt *) stmt);
            break;
        case STMT_INTERP:
            ok = HandleInterpDef(info, (InterpDef *) stmt, merge);
            break;
        case STMT_GROUP_COMPAT:
            log_dbg(info->ctx,
                    "The \"group\" statement in compat is unsupported; "
                    "Ignored\n");
            ok = true;
            break;
        case STMT_LED_MAP:
            ok = HandleLedMapDef(info, (LedMapDef *) stmt, merge);
            break;
        case STMT_VAR:
            ok = HandleGlobalVar(info, (VarDef *) stmt);
            break;
        case STMT_VMOD:
            ok = HandleVModDef(info->ctx, &info->mods, (VModDef *) stmt, merge);
            break;
        default:
            log_err(info->ctx,
                    "Compat files may not include other types; "
                    "Ignoring %s\n", stmt_type_to_string(stmt->type));
            ok = false;
            break;
        }

        if (!ok)
            info->errorCount++;

        if (info->errorCount > 10) {
            log_err(info->ctx,
                    "Abandoning compatibility map \"%s\"\n", file->name);
            break;
        }
    }
}
