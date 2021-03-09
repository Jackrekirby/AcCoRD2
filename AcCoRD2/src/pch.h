// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
// Pre-Compiled Header
// Aims to reduce build times by storing commonly used (and rarely/non changing) headers in binary format

// Commonly used STL headers
#include <string>
#include <vector>
#include <array>
#include "enum_array.h"

#include <optional>
#include <memory>
#include <algorithm>

// Commonly used AcCoRD headers
#include "random.h"
#include "json.h"
#include "logger.h"