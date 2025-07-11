#pragma once

#include "semaphore.hh"

#include <array>
#include <atomic>
#include <etl/mutex.h>
#include <etl/vector.h>

constexpr auto kInvalidIconHash = 0;

class ApplicationState
{
public:
    class IListener
    {
    public:
        virtual ~IListener() = default;
    };


    struct State
    {
        virtual ~State() = default;

        bool navigation_active {false};
        uint32_t dist_to_next {0};
        uint32_t current_icon_hash {kInvalidIconHash};

        bool operator==(const State& other) const = default;
        State& operator=(const State& other) = default;
    };

    std::unique_ptr<IListener> AttachListener(os::binary_semaphore& semaphore);

    // Checkout a local copy of the global state. Rewritten when the unique ptr is released
    std::unique_ptr<State> Checkout();

    const State* CheckoutReadonly() const;

private:
    class ListenerImpl;
    class StateImpl;

    template <typename M>
    bool UpdateIfChanged(M ApplicationState::State::* member,
                         const ApplicationState::StateImpl* current_state,
                         ApplicationState::State* global_state) const;

    void Commit(const StateImpl* state);

    State m_global_state;
    etl::mutex m_mutex;
    etl::vector<ListenerImpl*, 4> m_listeners;
};
