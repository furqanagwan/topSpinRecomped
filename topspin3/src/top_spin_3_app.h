#pragma once

#include <memory>

#include "recomp/app/game_recomp_app.h"

class TopSpin3App final : public recomp::GameRecompApp {
 public:
  static std::unique_ptr<rex::ui::WindowedApp> Create(rex::ui::WindowedAppContext& context) {
    return std::unique_ptr<TopSpin3App>(new TopSpin3App(context));
  }

 private:
  explicit TopSpin3App(rex::ui::WindowedAppContext& context)
      : GameRecompApp(context, Descriptor(), PPCImageConfig) {}

  static recomp::GameDescriptor Descriptor() {
    recomp::GameDescriptor descriptor;
    descriptor.app_name = "top_spin_3";
    descriptor.display_name = "Top Spin 3";
#ifdef RECOMP_DEVELOPMENT_GAME_ROOT
    descriptor.development_game_root = RECOMP_DEVELOPMENT_GAME_ROOT;
#endif
    return descriptor;
  }
};
