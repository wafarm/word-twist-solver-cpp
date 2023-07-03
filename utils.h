#pragma once

#include <string>
#include <chrono>

void start_timer();
std::chrono::milliseconds stop_timer();
std::string load_text_resource(int resourceId);