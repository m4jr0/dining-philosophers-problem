// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "dining_party.h"

namespace dpp {
DiningParty& DiningParty::Get() { return *DiningParty::party_; }

DiningParty::DiningParty() { DiningParty::party_ = this; }

void DiningParty::Start() {
#ifdef DPP_WINDOWS
  if (!SetConsoleCtrlHandler(static_cast<PHANDLER_ROUTINE>(HandleConsole),
                             TRUE)) {
    std::cout
        << "Could not set console handler. This could result in "
        << "memory leaks as the party would not shut down properly if the "
        << "console window is closed." << '\n';
  }
#endif  // DPP_WINDOWS

#ifdef DPP_UNIX
  struct sigaction sig_handler;
  sig_handler.sa_handler = [&](s32 signal) { DiningParty::Get().Stop(); };

  sigemptyset(&sig_handler.sa_mask);
  sig_handler.sa_flags = 0;

  sigaction(SIGINT, &sig_handler, NULL);
#endif  // DPP_UNIX

  is_partying_.store(true);
  Initialize();
}

void dpp::DiningParty::Stop() { is_partying_.store(false); }

#ifdef DPP_WINDOWS
BOOL WINAPI DiningParty::HandleConsole(DWORD window_event) {
  switch (window_event) {
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
      DiningParty::Get().Stop();
      return TRUE;

    default:
      break;
  }

  return FALSE;
}
#endif  // DPP_WINDOWS
}  // namespace dpp