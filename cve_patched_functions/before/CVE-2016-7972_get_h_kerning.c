get_h_kerning(hb_font_t *font, void *font_data, hb_codepoint_t first,
                 hb_codepoint_t second, void *user_data)
{
    FT_Face face = font_data;
    FT_Vector kern;

    if (FT_Get_Kerning(face, first, second, FT_KERNING_DEFAULT, &kern))
        return 0;

    return kern.x;
}
