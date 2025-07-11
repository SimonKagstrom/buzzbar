#pragma once

#include "application_state.hh"
#include "base_thread.hh"
#include "hal/i_display.hh"
#include "image_cache.hh"

#include <lvgl.h>


class UserInterface : public os::BaseThread
{
public:
    UserInterface(hal::IDisplay& display, ApplicationState& state, ImageCache& cache);

private:
    void OnStartup() final;
    std::optional<milliseconds> OnActivation() final;

    hal::IDisplay& m_display;
    ApplicationState& m_state;

    lv_display_t* m_lvgl_display {nullptr};
    uint32_t m_next_redraw_time {0};
    ImageCache& m_image_cache;

    uint32_t m_current_icon_hash {kInvalidIconHash};
    lv_obj_t* m_current_icon {nullptr};
};
