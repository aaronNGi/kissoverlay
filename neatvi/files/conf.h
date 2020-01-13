/* neatvi configuration file */

/* map file names to file types */
static struct filetype {
	char *ft;		/* file type */
	char *pat;		/* file name pattern */
} filetypes[] = {
	{"c", "\\.[hc]$"},				/* C */
	{"roff", "\\.(ms|tr|roff|tmac|txt|[1-9])$"},	/* troff */
	{"mk", "Makefile$|makefile$|\\.mk$"},		/* makefile */
	{"sh", "\\.sh$"},				/* shell script */
	{"awk", "\\.awk$"},				/* awk script */
};

/* syntax highlighting patterns */
static struct highlight {
	char *ft;		/* the filetype of this pattern */
	int att[16];		/* attributes of the matched groups */
	char *pat;		/* regular expression */
	int end;		/* the group ending this pattern */
} highlights[] = {
	{"c", {5}, "\\<(signed|unsigned|char|short|int|long|float|double|void|struct|enum|union|typedef)\\>"},
	{"c", {5}, "\\<(static|extern|register)\\>"},
	{"c", {3}, "\\<(return|for|while|if|else|do|sizeof|goto|switch|case|default|break|continue)\\>"},
	{"c", {4}, "//.*$"},
	{"c", {4}, "/\\*([^*]|\\*+[^*/])*\\*+/"},
	{"c", {4}, "^#[ \t]*[a-zA-Z0-9_]+"},
	{"c", {0, SYN_BD}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"c", {}, "\"([^\"]|\\\\\")*\""},
	{"c", {}, "'([^\\]|\\\\.)'"},
	{"c", {2}, "[-+]?\\<(0[xX][0-9a-fA-F]+|[0-9]+)\\>"},

	{"roff", {4, 0, 5 | SYN_BD, 4 | SYN_BD, 5 | SYN_BD, 4 | SYN_BD},
		"^[.'][ \t]*((SH.*)|(de) (.*)|([^ \t\\]{2,}))?.*$", 1},
	{"roff", {2}, "\\\\\".*$"},
	{"roff", {3}, "\\\\{1,2}[*$fgkmns]([^[(]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\\\([^[(*$fgkmns]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\$[^$]+\\$"},

	/* makefile */
	{"mk", {4}, "#.*$"},
	{"mk", {4}, "([A-Za-z_%.]+):"},

	/* shell script */
	{"sh", {0,0,4}, "(^|[^\\])(#.*$)"},
	{"sh", {}, "\"([^\"]|\\\\\")*\""},
	{"sh", {}, "\'[^\']*\'"},

	/* awk script */
	{"awk", {SYN_BD}, "\\<(if|else|while|for|do|break|continue)\\>"},
	{"awk", {SYN_BD}, "\\<(print|printf|return|next|nextfile|delete|exit|getline)\\>"},
	{"awk", {0,0,4}, "(^|[^\\])(#.*$)"},
	{"awk", {0, SYN_BD}, "([a-zA-Z_][a-zA-Z0-9_]+)[ \t]*\\(", 1},
	{"awk", {}, "\"([^\"]|\\\\\")*\""},
	{"awk", {}, "\'[^\']*\'"},

	/* status bar */
	{"---", {3}, "^(\\[enter to continue\\])"},
};

/* how to hightlight text in the reverse direction */
#define SYN_REVDIR		(SYN_BGMK(255))

/* right-to-left characters (used only in dircontexts[] and dirmarks[]) */
#define CR2L		"\330\241\330\242\330\243\330\244\330\245\330\246\330\247\330\250\330\251\330\252\330\253\330\254\330\255\330\256\330\257\330\260\330\261\330\262\330\263\330\264\330\265\330\266\330\267\330\270\330\271\330\272\331\200\331\201\331\202\331\203\331\204\331\205\331\206\331\207\331\210\331\211\331\212\331\212\331\276\332\206\332\230\332\251\332\257\333\214\342\200\214\342\200\215\330\233\330\214\302\273\302\253\330\237\331\222\331\214\331\215\331\213\331\217\331\220\331\216\331\221"
/* neutral characters (used only in dircontexts[] and dirmarks[]) */
#define CNEUT		"-!\"#$%&'()*+,./:;<=>?@^_`{|}~ "

/* direction context patterns; specifies the direction of a whole line */
static struct dircontext {
	int dir;
	char *pat;
} dircontexts[] = {
	{-1, "^[" CR2L "]"},
	{+1, "^[a-zA-Z_0-9]"},
};

/* direction marks; the direction of a few words in a line */
static struct dirmark {
	int ctx;	/* the direction context for this mark; 0 means any */
	int dir;	/* the direction of the matched text */
	int grp;	/* the nested subgroup; 0 means no groups */
	char *pat;
} dirmarks[] = {
	{+0, +1, 1, "\\\\\\*\\[([^]]+)\\]"},
	{+1, -1, 0, "[" CR2L "][" CNEUT CR2L "]*[" CR2L "]"},
	{-1, +1, 0, "[a-zA-Z0-9_][^" CR2L "\\\\`$']*[a-zA-Z0-9_]"},
	{+0, +1, 0, "\\$([^$]+)\\$"},
	{+0, +1, 1, "\\\\[a-zA-Z0-9_]+\\{([^}]+)\\}"},
	{-1, +1, 0, "\\\\[^ \t" CR2L "]+"},
};

/* character placeholders */
static struct placeholder {
	char *s;	/* the source character */
	char *d;	/* the placeholder */
	int wid;	/* the width of the placeholder */
} placeholders[] = {
	{"\342\200\214", "\x1b[7m^-\x1b[27m", 2},	/* zero width non joiner */
	{"\342\200\215", "\x1b[7m^-\x1b[27m", 2},	/* zero width non joiner */
	{"\x00", "\x1b[7m^@\x1b[27m", 2},
	{"\x01", "\x1b[7m^A\x1b[27m", 2},
	{"\x02", "\x1b[7m^B\x1b[27m", 2},
	{"\x03", "\x1b[7m^C\x1b[27m", 2},
	{"\x04", "\x1b[7m^D\x1b[27m", 2},
	{"\x05", "\x1b[7m^E\x1b[27m", 2},
	{"\x06", "\x1b[7m^F\x1b[27m", 2},
	{"\x07", "\x1b[7m^G\x1b[27m", 2},
	{"\x08", "\x1b[7m^H\x1b[27m", 2},
	/*{"\x09", "\x1b[7m^I\x1b[27m", 2},*/
	/*{"\x0A", "$", 1},*/
	{"\x0B", "\x1b[7m^K\x1b[27m", 2},
	{"\x0C", "\x1b[7m^L\x1b[27m", 2},
	{"\x0D", "\x1b[7m^M\x1b[27m", 2},
	{"\x0E", "\x1b[7m^N\x1b[27m", 2},
	{"\x0F", "\x1b[7m^O\x1b[27m", 2},
	{"\x10", "\x1b[7m^P\x1b[27m", 2},
	{"\x11", "\x1b[7m^Q\x1b[27m", 2},
	{"\x12", "\x1b[7m^R\x1b[27m", 2},
	{"\x13", "\x1b[7m^S\x1b[27m", 2},
	{"\x14", "\x1b[7m^T\x1b[27m", 2},
	{"\x15", "\x1b[7m^U\x1b[27m", 2},
	{"\x16", "\x1b[7m^V\x1b[27m", 2},
	{"\x17", "\x1b[7m^W\x1b[27m", 2},
	{"\x18", "\x1b[7m^X\x1b[27m", 2},
	{"\x19", "\x1b[7m^Y\x1b[27m", 2},
	{"\x1A", "\x1b[7m^Z\x1b[27m", 2},
	{"\x1B", "\x1b[7m^[\x1b[27m", 2},
	{"\x1C", "\x1b[7m^\\\x1b[27m", 2},
	{"\x1D", "\x1b[7m^]\x1b[27m", 2},
	{"\x1E", "\x1b[7m^^\x1b[27m", 2},
	{"\x1F", "\x1b[7m^_\x1b[27m", 2},
	{"\x7F", "\x1b[7m^?\x1b[27m", 2},
};
