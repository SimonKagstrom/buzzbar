#pragma once

#include "application_state.hh"
#include "base_thread.hh"
#include "hal/i_ble_server.hh"
#include "image_cache.hh"

class BleHandler : public os::BaseThread
{
public:
    BleHandler(hal::IBleServer& server, ApplicationState& state, ImageCache& cache);

private:
    // From BaseThread
    void OnStartup() final;
    std::optional<milliseconds> OnActivation() final;

    void OnChaNav(std::span<const uint8_t> data);
    void OnIcon(std::span<const uint8_t> data);

    os::TimerHandle m_ble_poller;
    hal::IBleServer& m_server;
    ApplicationState& m_state;
    ImageCache& m_image_cache;
};
