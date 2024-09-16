_pango_get_emoji_type (gunichar codepoint)
{
  /* Those should only be Emoji presentation as combinations of two. */
  if (_pango_Is_Emoji_Keycap_Base (codepoint) ||
      _pango_Is_Regional_Indicator (codepoint))
    return PANGO_EMOJI_TYPE_TEXT;

  if (codepoint == kCombiningEnclosingKeycapCharacter)
    return PANGO_EMOJI_TYPE_EMOJI_EMOJI;

  if (_pango_Is_Emoji_Emoji_Default (codepoint) ||
      _pango_Is_Emoji_Modifier_Base (codepoint) ||
      _pango_Is_Emoji_Modifier (codepoint))
    return PANGO_EMOJI_TYPE_EMOJI_EMOJI;

  if (_pango_Is_Emoji_Text_Default (codepoint))
    return PANGO_EMOJI_TYPE_EMOJI_TEXT;

  return PANGO_EMOJI_TYPE_TEXT;
}
