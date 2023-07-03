#include "utils.h"

#include <Windows.h>

#include "resource.h"

using namespace std::chrono;

static high_resolution_clock::time_point start_time;

void start_timer() { start_time = high_resolution_clock::now(); }

milliseconds stop_timer() {
  auto stop_time = high_resolution_clock::now();
  return duration_cast<milliseconds>(stop_time - start_time);
}

std::string load_text_resource(int resourceId) {
  HMODULE handle = ::GetModuleHandle(NULL);
  HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(resourceId),
                            MAKEINTRESOURCE(TEXTFILE));
  if (rc == NULL) return nullptr;
  HGLOBAL rcData = ::LoadResource(handle, rc);

  if (rcData == NULL) return nullptr;
  auto data = (const char*)::LockResource(rcData);

  std::string dataString(data);
  return dataString;
}