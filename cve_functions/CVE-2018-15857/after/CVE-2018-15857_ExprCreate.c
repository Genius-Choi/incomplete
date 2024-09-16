ExprCreate(enum expr_op_type op, enum expr_value_type type, size_t size)
{
    ExprDef *expr = malloc(size);
    if (!expr)
        return NULL;

    expr->common.type = STMT_EXPR;
    expr->common.next = NULL;
    expr->expr.op = op;
    expr->expr.value_type = type;

    return expr;
}
