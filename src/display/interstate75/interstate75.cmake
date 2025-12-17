add_library(display INTERFACE)

include(libraries/hershey_fonts/hershey_fonts)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/pico_graphics/pico_graphics)
include(drivers/hub75/hub75)

target_sources(display INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/interstate75.cpp
)

target_include_directories(display INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(display INTERFACE
    
    pico_graphics
    hershey_fonts
    bitmap_fonts
    hub75

    pico_stdlib
    hardware_adc
    hardware_pio
    hardware_dma

    #plasma
)

set(DISPLAY_NAME "Interstate75")