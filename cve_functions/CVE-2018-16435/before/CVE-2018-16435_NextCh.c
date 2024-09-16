void NextCh(cmsIT8* it8)
{
    if (it8 -> FileStack[it8 ->IncludeSP]->Stream) {

        it8 ->ch = fgetc(it8 ->FileStack[it8 ->IncludeSP]->Stream);

        if (feof(it8 -> FileStack[it8 ->IncludeSP]->Stream))  {

            if (it8 ->IncludeSP > 0) {

                fclose(it8 ->FileStack[it8->IncludeSP--]->Stream);
                it8 -> ch = ' ';                            // Whitespace to be ignored

            } else
                it8 ->ch = 0;   // EOF
        }
    }
    else {
        it8->ch = *it8->Source;
        if (it8->ch) it8->Source++;
    }
}
