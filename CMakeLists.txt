project(obs-game-bar)

if(MSVC)
    set(obs-game-bar_PLATFORM_DEPS
        w32-pthreads)
endif()

set(obs-game-bar_SOURCES
    obs-game-bar.c)

add_library(obs-game-bar MODULE
    ${obs-game-bar_SOURCES})
target_link_libraries(obs-game-bar
    libobs
    ${obs-game-bar_PLATFORM_DEPS})

install_obs_plugin_with_data(obs-game-bar data)