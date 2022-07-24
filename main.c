#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* flag set by --verbose flag */
static int verbose_flag;

int main (int argc, char **argv) 
{
	
	int c;
	int i = 0;
	FILE *fp;

	puts ("args are:\n");
	for (i = 0; i < argc; i++) {
		printf("%d: %s\n", i, argv[i]);
	}
	// https://stackoverflow.com/questions/48981712/command-line-argument-of-%E2%88%92-when-making-standard-unix-programs-for-c
	puts ("standard input is:\n");
	printf("%s\n", stdin);

	while (1) {
		static struct option long_options[] = {
			// these options set a flag.
			{"verbose", 	no_argument, 		&verbose_flag, 1},
			{"brief", 	no_argument, 		&verbose_flag, 0},
			// these options don't set a flag, will distiguish by indicies
			{"add", 	no_argument, 		0, 'a'},
			{"append", 	no_argument, 		0, 'b'},
			{"delete", 	required_argument, 	0, 'd'},
			{"create", 	required_argument, 	0, 'c'},
			{"file", 	required_argument, 	0, 'f'}

		};
		// getopt_long stores the option index here
		int option_index = 0;
		c = getopt_long (argc, argv, "abc:d:f", long_options, &option_index);
		
		// detect end of the options 
		if (c == -1) {
			break;
		}

		switch (c) {
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
				break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
				printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'a':
				puts ("option -a\n");
				break;

			case 'b':
				puts ("option -b\n");
				break;

			case 'c':
				printf ("option -c with value `%s'\n", optarg);
				break;

			case 'd':
				printf ("option -d with value `%s'\n", optarg);
				break;

			case 'f':
				printf ("option -f with value `%s'\n", optarg);
				break;

			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}

	}
	if (verbose_flag) {
		puts ("verbose flag is set");
	}

	if (optind < argc) {
		puts ("non option commands:");
		while (optind < argc) {
			printf ("%s ", argv[optind++]);
			puts("\n");
		}
	}

	return 0;
}
