/**
 * Creates passwords on the command line.
 *
 * Copyright (c) 2011-2012 Robert Weiler.
 * Released under the Zlib License, see LICENSE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//========================================================================

#define PWDGEN_VERSION "2.0"

//========================================================================

char *pwdgen(int);
char *sec_pwdgen(int, int);
char check_sec_pwd(char *, int);
char is_upper_case(char);
char is_lower_case(char);
char is_number(char);
char is_special_char(char);
char is_usable_char(char);
void version();
void usage();

//========================================================================

int main(int argc, char **argv) {
	int opt;
	int pwdcnt = 4;
	int pwdlen = 12;
	int pwdsec = 0;
	char *pwd;

	srand(rand() + time(NULL) - rand());

	while (-1 != (opt = getopt(argc, argv, "hvl:c:sS"))) {
		switch (opt) {
			case 'h':
				usage();
				return EXIT_SUCCESS;
				break;
			case 'v':
				version();
				return EXIT_SUCCESS;
				break;
			case 'l':
				pwdlen = atoi(optarg);
				break;
			case 'c':
				pwdcnt = atoi(optarg);
				break;
			case 's':
				pwdsec = 1;
				break;
			case 'S':
				pwdsec = 2;
				break;
		}
	}

	if (3 >= pwdlen) {
		printf("%s\n", "Error: The password length has to be > 3.");
		return EXIT_FAILURE;
	}
	if (0 >= pwdcnt) {
		printf("%s\n", "Error: The password count has to be > 0.");
		return EXIT_FAILURE;
	}

	if (0 == pwdsec) {
		while (0 < pwdcnt) {
			pwd = pwdgen(pwdlen);
			printf("%s\n", pwd);
			free(pwd);
			--pwdcnt;
		}
	} else {
		while (0 < pwdcnt) {
			pwd = sec_pwdgen(pwdlen, pwdsec);
			printf("%s\n", pwd);
			free(pwd);
			--pwdcnt;
		}
	}

	return 0;
}

//========================================================================

char *pwdgen(int len) {
	char *pwd = (char *)calloc(sizeof(char), len + 1);
	int ch;
	int i, j;

	srand(rand());
	j = 0;
	while (j < len) {
		ch = rand() % 127;
		if (44 > ch) {
			ch = ch + 44;
		}
		if (0 != is_usable_char(ch)) {
			pwd[j] = ch;
		} else {
			j--;
		}
		j++;
	}
	pwd[j] = 0;

	return pwd;
}

//========================================================================

char *sec_pwdgen(int len, int level) {
	char *pwd1;
	char *pwd2;
	char *pwd3;
	char *pwd4;
	char *final_pwd;
	int i, j;
	int ctypes;

	pwd1 = pwdgen(len);
	pwd2 = pwdgen(len);
	pwd3 = pwdgen(len);
	pwd4 = pwdgen(len);
	final_pwd = (char *)calloc(sizeof(char), len + 1);
	srand(rand());
	for (j = 0; j < len; ++j) {
		switch (rand() % 4) {
			case 0:
				final_pwd[j] = pwd1[j];
				break;
			case 1:
				final_pwd[j] = pwd2[j];
				break;
			case 2:
				final_pwd[j] = pwd3[j];
				break;
			case 3:
				final_pwd[j] = pwd4[j];
				break;
			default:
				--j;
				break;
		}
	}
	final_pwd[j] = 0;
	free(pwd1);
	free(pwd2);
	free(pwd3);
	free(pwd4);

	ctypes = 2 + level;
	while (ctypes > check_sec_pwd(final_pwd, len)) {
		free(final_pwd);
		final_pwd = sec_pwdgen(len, level);
	}

	return final_pwd;
}

//========================================================================

char check_sec_pwd(char *pwd, int len) {
	int i;
	char ch;
	char ucl;   // Upper Case Letter
	char lcl;   // Lower Case Letter
	char nmb;   // NuMBer
	char sch;   // Special CHaracter

	ucl = 0;
	lcl = 0;
	nmb = 0;
	sch = 0;

	for (i = 0; i < len; ++i) {
		ch = pwd[i];
		if (0 != is_upper_case(ch)) {
			ucl = 1;
		} else if (0 != is_lower_case(ch)) {
			lcl = 1;
		} else if (0 != is_number(ch)) {
			nmb = 1;
		} else if (0 != is_special_char(ch)) {
			sch = 1;
		}
	}

	return (ucl + lcl + nmb + sch);
}

//========================================================================

char is_upper_case(char ch) {
	if (65 <= ch  &&  90 >= ch) {
		return 1;
	}

	return 0;
}

//========================================================================

char is_lower_case(char ch) {
	if (97 <= ch  &&  122 >= ch) {
		return 1;
	}

	return 0;
}

//========================================================================

char is_number(char ch) {
	if (48 <= ch  &&  57 >= ch) {
		return 1;
	}

	return 0;
}

//========================================================================

char is_special_char(char ch) {
	if (33 == ch) {
		return 1;
	} else if (35 == ch) {
		return 1;
	} else if (37 == ch) {
		return 1;
	} else if (40 <= ch  &&  46 >= ch) {
		return 1;
	} else if (58 <= ch  &&  59 >= ch) {
		return 1;
	} else if (61 == ch) {
		return 1;
	} else if (63 <= ch  &&  64 >= ch) {
		return 1;
	} else if (95 == ch) {
		return 1;
	}

	return 0;
}

//========================================================================

char is_usable_char(char ch) {
	return (is_upper_case(ch) + is_lower_case(ch) + is_number(ch)
			+ is_special_char(ch));
}

//========================================================================

void version() {
	printf("pwdgen v%s - password creator\n", PWDGEN_VERSION);
	printf("(c) 2011-2012 Robert Weiler.\n");
	printf("Licensed under the Zlib License.\n");
}

//========================================================================

void usage() {
	version();
	printf("\n");
	printf("Usage: pwdgen [-l LENGTH] [-c COUNT] [-s] [-S]\n");
	printf("\n");
	printf("  -h\n");
	printf("    Show this usage message.\n");
	printf("  -v\n");
	printf("    Show version and license information.\n");
	printf("  -l LENGTH\n");
	printf("    The desired length of the password(s).\n");
	printf("    Defaults to 12.\n");
	printf("  -c COUNT\n");
	printf("    The desired number of passwords.\n");
	printf("    Defaults to 4.\n");
	printf("  -s\n");
	printf("    Create stronger, more secure password(s).\n");
	printf("  -S\n");
	printf("    Create really strong password(s).\n");
}

// vim: set sw=4 ts=4 noet ft=c fenc=us-ascii ff=dos tw=74 :
