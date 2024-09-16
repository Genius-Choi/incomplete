parse(struct xkb_compose_table *table, struct scanner *s,
      unsigned include_depth)
{
    enum rules_token tok;
    union lvalue val;
    xkb_keysym_t keysym;
    struct production production;
    enum { MAX_ERRORS = 10 };
    int num_errors = 0;

initial:
    production.len = 0;
    production.has_keysym = false;
    production.has_string = false;
    production.mods = 0;
    production.modmask = 0;

    /* fallthrough */

initial_eol:
    switch (tok = lex(s, &val)) {
    case TOK_END_OF_LINE:
        goto initial_eol;
    case TOK_END_OF_FILE:
        goto finished;
    case TOK_INCLUDE:
        goto include;
    default:
        goto lhs_tok;
    }

include:
    switch (tok = lex_include_string(s, table, &val)) {
    case TOK_INCLUDE_STRING:
        goto include_eol;
    default:
        goto unexpected;
    }

include_eol:
    switch (tok = lex(s, &val)) {
    case TOK_END_OF_LINE:
        if (!do_include(table, s, val.string.str, include_depth))
            goto fail;
        goto initial;
    default:
        goto unexpected;
    }

lhs:
    tok = lex(s, &val);
lhs_tok:
    switch (tok) {
    case TOK_COLON:
        if (production.len <= 0) {
            scanner_warn(s, "expected at least one keysym on left-hand side; skipping line");
            goto skip;
        }
        goto rhs;
    case TOK_IDENT:
        if (streq(val.string.str, "None")) {
            production.mods = 0;
            production.modmask = ALL_MODS_MASK;
            goto lhs_keysym;
        }
        goto lhs_mod_list_tok;
    case TOK_TILDE:
        goto lhs_mod_list_tok;
    case TOK_BANG:
        production.modmask = ALL_MODS_MASK;
        goto lhs_mod_list;
    default:
        goto lhs_keysym_tok;
    }

lhs_keysym:
    tok = lex(s, &val);
lhs_keysym_tok:
    switch (tok) {
    case TOK_LHS_KEYSYM:
        keysym = xkb_keysym_from_name(val.string.str, XKB_KEYSYM_NO_FLAGS);
        if (keysym == XKB_KEY_NoSymbol) {
            scanner_err(s, "unrecognized keysym \"%s\" on left-hand side",
                        val.string.str);
            goto error;
        }
        if (production.len + 1 > MAX_LHS_LEN) {
            scanner_warn(s, "too many keysyms (%d) on left-hand side; skipping line",
                         MAX_LHS_LEN + 1);
            goto skip;
        }
        production.lhs[production.len++] = keysym;
        production.mods = 0;
        production.modmask = 0;
        goto lhs;
    default:
        goto unexpected;
    }

lhs_mod_list:
    tok = lex(s, &val);
lhs_mod_list_tok: {
        bool tilde = false;
        xkb_mod_index_t mod;

        if (tok != TOK_TILDE && tok != TOK_IDENT)
            goto lhs_keysym_tok;

        if (tok == TOK_TILDE) {
            tilde = true;
            tok = lex(s, &val);
        }

        if (tok != TOK_IDENT)
            goto unexpected;

        mod = resolve_modifier(val.string.str);
        if (mod == XKB_MOD_INVALID) {
            scanner_err(s, "unrecognized modifier \"%s\"",
                        val.string.str);
            goto error;
        }

        production.modmask |= 1 << mod;
        if (tilde)
            production.mods &= ~(1 << mod);
        else
            production.mods |= 1 << mod;

        goto lhs_mod_list;
    }

rhs:
    switch (tok = lex(s, &val)) {
    case TOK_STRING:
        if (production.has_string) {
            scanner_warn(s, "right-hand side can have at most one string; skipping line");
            goto skip;
        }
        if (val.string.len <= 0) {
            scanner_warn(s, "right-hand side string must not be empty; skipping line");
            goto skip;
        }
        if (val.string.len >= sizeof(production.string)) {
            scanner_warn(s, "right-hand side string is too long; skipping line");
            goto skip;
        }
        strcpy(production.string, val.string.str);
        production.has_string = true;
        goto rhs;
    case TOK_IDENT:
        keysym = xkb_keysym_from_name(val.string.str, XKB_KEYSYM_NO_FLAGS);
        if (keysym == XKB_KEY_NoSymbol) {
            scanner_err(s, "unrecognized keysym \"%s\" on right-hand side",
                        val.string.str);
            goto error;
        }
        if (production.has_keysym) {
            scanner_warn(s, "right-hand side can have at most one keysym; skipping line");
            goto skip;
        }
        production.keysym = keysym;
        production.has_keysym = true;
	/* fallthrough */
    case TOK_END_OF_LINE:
        if (!production.has_string && !production.has_keysym) {
            scanner_warn(s, "right-hand side must have at least one of string or keysym; skipping line");
            goto skip;
        }
        add_production(table, s, &production);
        goto initial;
    default:
        goto unexpected;
    }

unexpected:
    if (tok != TOK_ERROR)
        scanner_err(s, "unexpected token");
error:
    num_errors++;
    if (num_errors <= MAX_ERRORS)
        goto skip;

    scanner_err(s, "too many errors");
    goto fail;

fail:
    scanner_err(s, "failed to parse file");
    return false;

skip:
    while (tok != TOK_END_OF_LINE && tok != TOK_END_OF_FILE)
        tok = lex(s, &val);
    goto initial;

finished:
    return true;
}
