#pragma once

#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>

#include "includes.hpp"

void download_file(const string& url,const string& filename);