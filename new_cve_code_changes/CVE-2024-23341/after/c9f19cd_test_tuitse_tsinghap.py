from django.test.testcases import TestCase

from tuitse import kiamtsa
from tuitse.html import tuitse_html


class TuaLiongTuiTse(TestCase):

    def test_tuitse(self):
        tsusin = kiamtsa(
            '做代誌愛像走{<華><馬拉松>，沓沓仔來。',
            'tsò tāi-tsì ài tshiūnn tsáu <華><馬拉松> kāng-khuán, ta̍uh-ta̍uh-á lâi.',
        )
        tuitse_html(tsusin)
