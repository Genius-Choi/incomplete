FreeStmt(ParseCommon *stmt)
{
    ParseCommon *next;

    while (stmt)
    {
        next = stmt->next;

        switch (stmt->type) {
        case STMT_INCLUDE:
            FreeInclude((IncludeStmt *) stmt);
            /* stmt is already free'd here. */
            stmt = NULL;
            break;
        case STMT_EXPR:
            FreeExpr((ExprDef *) stmt);
            break;
        case STMT_VAR:
            FreeStmt((ParseCommon *) ((VarDef *) stmt)->name);
            FreeStmt((ParseCommon *) ((VarDef *) stmt)->value);
            break;
        case STMT_TYPE:
            FreeStmt((ParseCommon *) ((KeyTypeDef *) stmt)->body);
            break;
        case STMT_INTERP:
            FreeStmt((ParseCommon *) ((InterpDef *) stmt)->match);
            FreeStmt((ParseCommon *) ((InterpDef *) stmt)->def);
            break;
        case STMT_VMOD:
            FreeStmt((ParseCommon *) ((VModDef *) stmt)->value);
            break;
        case STMT_SYMBOLS:
            FreeStmt((ParseCommon *) ((SymbolsDef *) stmt)->symbols);
            break;
        case STMT_MODMAP:
            FreeStmt((ParseCommon *) ((ModMapDef *) stmt)->keys);
            break;
        case STMT_GROUP_COMPAT:
            FreeStmt((ParseCommon *) ((GroupCompatDef *) stmt)->def);
            break;
        case STMT_LED_MAP:
            FreeStmt((ParseCommon *) ((LedMapDef *) stmt)->body);
            break;
        case STMT_LED_NAME:
            FreeStmt((ParseCommon *) ((LedNameDef *) stmt)->name);
            break;
        default:
            break;
        }

        free(stmt);
        stmt = next;
    }
}
