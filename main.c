/*
 * Copyright (C) 2017 John M. Harris, Jr. <johnmh@openblox.org>
 *
 * This file is part of Habsup.
 *
 * Habsup is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Habsup is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Habsup. If not, see <https://www.gnu.org/licenses/>.
 */

#include "habsup.h"

#include <getopt.h>

int main(int argc, char* argv[]){
    char* configDir = NULL;
    
    static struct option long_opts[] = {
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"config", required_argument, 0, 'c'},
        {0, 0, 0, 0}
    };

    int opt_idx = 0;

    while(1){
        int c = getopt_long(argc, argv, "vhc:", long_opts, &opt_idx);

        if(c == -1){
            break;
        }

        switch(c){
            case 'v': {
                /* This isn't optimal, but we don't care too much about
                 * optimization when all we're doing is printing and
                 * returning EXIT_SUCCESS.
                 *
                 * Besides, it looks a lot more clean.
                 */
                puts("Habsup");
                puts("Copyright (c) 2017 John M. Harris, Jr.");
                puts("This is free software. It is licensed for use, modification and");
                puts("redistribution under the terms of the GNU General Public License,");
                puts("version 3 or later <https://gnu.org/licenses/gpl.html>");
                puts("");
                puts("Please send bug reports to: <johnmh@openblox.org>");
                exit(EXIT_SUCCESS);
                break;
            }
            case 'h': {
                puts("Habsup - A few sexps");
                printf("Usage: %s [opts]\n", argv[0]);
                puts("    -c, --config <PATH>    Sets the configuration directory");
                puts("");
                puts("    -v, --version          Prints version information and exits");
                puts("    -h, --help             Prints this help text and exits");
                puts("");
                puts("Options are specified by doubled hyphens and their name or by a single");
                puts("hyphen and the flag character.");
                puts("");
                puts("Please send bug reports to: <johnmh@openblox.org>");
                exit(EXIT_SUCCESS);
                break;
            }
            case 'c': {
                if(configDir){
                    free(configDir);
                }
                configDir = strdup(optarg);
                break;
            }
            case '?':
            default: {
                if(configDir){
                    free(configDir);
                }

                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    if(!configDir){
        configDir = habsup_find_cfg();
        if(!configDir){
            fputs("Failed to find configuration directory.\n", stderr);
        }
    }
    
    
    return 0;
}
