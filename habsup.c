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

#include <sys/types.h>
#include <dirent.h>
#include <wordexp.h>

// Habsup functions start with habsup_, utilities start with hab_

char* hab_canon_shellpath(char* str){
    wordexp_t exp_result;
    wordexp(str, &exp_result, 0);
    char* r = strdup(exp_result.we_wordv[0]);
    wordfree(&exp_result);
    return r;
}

char* habsup_find_cfg(){
    char* pathFromEnv = getenv(HABSUP_CONFIG_ENV);
    if(pathFromEnv){
        return strdup(pathFromEnv);
    }
    char* homePath = hab_canon_shellpath("~/.habsup");
    if(homePath){
        DIR* dir = opendir(homePath);
        if(dir){
            closedir(dir);
            return homePath;
        }
        free(homePath);
    }
    homePath = hab_canon_shellpath("~/.local/habsup");
    if(homePath){
        DIR* dir = opendir(homePath);
        if(dir){
            closedir(dir);
            return homePath;
        }
        free(homePath);
    }

    return NULL;
}
