/*
 This file is part of Leela Zero.
 Copyright (C) 2017 Gian-Carlo Pascutto
 
 Leela Zero is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Leela Zero is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Leela Zero.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <random>
#include <chrono>

#include "config.h"
#include "Utils.h"
#include "UCTSearch.h"
#include "UCTNode.h"
#include "Network.h"
#include "Parameters.h"
#include "Training.h"

using namespace Utils;

// Configuration flags
bool cfg_allow_pondering;
int cfg_num_threads;
int cfg_max_playouts;
int cfg_lagbuffer_cs;
int cfg_resignpct;
int cfg_noise;
int cfg_randomize;
int cfg_min_resign_moves;
uint64_t cfg_rng_seed;
#ifdef USE_OPENCL
std::vector<int> cfg_gpus;
bool cfg_sgemm_exhaustive;
bool cfg_tune_only;
#endif
float cfg_puct;
float cfg_softmax_temp;
std::string cfg_weightsfile;
std::string cfg_logfile;
std::string cfg_supervise;
FILE* cfg_logfile_handle;
bool cfg_quiet;

void Parameters::setup_default_parameters() {
    cfg_allow_pondering = true;
    int num_cpus = std::thread::hardware_concurrency();
    //cfg_num_threads = std::max(1, std::min(num_cpus, MAX_CPUS));
    cfg_num_threads = 2;

    cfg_max_playouts = 800;
    cfg_lagbuffer_cs = 100;
#ifdef USE_OPENCL
    cfg_gpus = { };
    cfg_sgemm_exhaustive = false;
    cfg_tune_only = false;
#endif
    cfg_puct = 0.85f;
    cfg_softmax_temp = 1.0f;
    cfg_min_resign_moves = 20;
    cfg_resignpct = 10;
    cfg_noise = false;
    cfg_randomize = false;
    cfg_logfile_handle = nullptr;
    cfg_quiet = false;
    cfg_rng_seed = 0;
    cfg_weightsfile = "weights.txt";
}

