list1node(FILE *fp, node *n)
{
    if (n == 0)
        return;
    if (ISNONTERMINAL(TYPE(n))) {
        int i;
        for (i = 0; i < NCH(n); i++)
            list1node(fp, CHILD(n, i));
    }
    else if (ISTERMINAL(TYPE(n))) {
        switch (TYPE(n)) {
        case INDENT:
            ++level;
            break;
        case DEDENT:
            --level;
            break;
        default:
            if (atbol) {
                int i;
                for (i = 0; i < level; ++i)
                    fprintf(fp, "\t");
                atbol = 0;
            }
            if (TYPE(n) == NEWLINE) {
                if (STR(n) != NULL)
                    fprintf(fp, "%s", STR(n));
                fprintf(fp, "\n");
                atbol = 1;
            }
            else
                fprintf(fp, "%s ", STR(n));
            break;
        }
    }
    else
        fprintf(fp, "? ");
}
