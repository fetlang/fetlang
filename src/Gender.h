#pragma once
// There are exactly 6 genders in the world. No more, no less.
enum Gender {
	// Gender has yet to be assigned - Variables should default to this
	UNASSIGNED_GENDER = 0,

	// Applies to people (singular) only
	MALE_GENDER,
	FEMALE_GENDER,

	// Includes non-binary and plural, mostly applies to
	// people, rarely to a group of objects.
	// No technical distinction is made between singular
	// non-binary and plural
	NEUTRAL_GENDER,

	// Singular object, applies to nouns only
	NONPERSON_GENDER,

	// Gender not applicable - applies to non-nouns only
	NA_GENDER,
};
