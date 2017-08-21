#pragma once

// The type of keyphrase
enum KeyphraseCategory {
	CONTROL_KEYPHRASE, /* have, make, times, if, end if, etc */
	OPERATOR_KEYPHRASE,/* all those naughty words ;) */
	COMPARISON_OPERATOR_KEYPHRASE, /* is, is not, etc */
	PRONOUN_KEYPHRASE, /*him, her, its own, etc, their */
};
