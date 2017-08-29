#pragma once
// There are exactly 6 genders in the world. No more, no less.
enum Gender {
	UNASSIGNED_GENDER = 0, /* Gender has yet to be assigned - Variables
				should default to this*/

	MALE_GENDER, FEMALE_GENDER, /* Applies to people (singular) only */

	NEUTRAL_GENDER, /* Includes non-binary and plural, mostly applies to
			 * people, rarely to a group of objects
			 *
			 * No technical distinction is made between singular
			 * non-binary and plural
			 */

	NONPERSON_GENDER, /* Singular object, applies to nouns only */

	NA_GENDER, /* Gender not applicable - applies to non-nouns only */
};
