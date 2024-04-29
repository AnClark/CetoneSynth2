cmake_minimum_required (VERSION 3.20)

project (cetonesynth2
    VERSION 1.0.0
    LANGUAGES C CXX
)

# Explicitily specify C++ standard to prevent build error on Github CI - macOS build
set (CMAKE_CXX_STANDARD 17)

add_subdirectory (dpf)

include_directories (   
    src/
    images/
)

set (SRC_BACKEND
    src/arp.cpp
    src/envelope.cpp
    src/filter.cpp
    src/lfo.cpp
    src/log.cpp
    src/osc.cpp
    src/statics.cpp
    src/svoice.cpp
    src/Synth.cpp
)

dpf_add_plugin (${PROJECT_NAME}
    TARGETS vst2 vst3 lv2 clap jack
    FILES_DSP
        src/CetoneSynth2.cpp
        src/CetoneSynth2_DPF.cpp
        ${SRC_BACKEND}
    FILES_UI
        src/Gui_DPF.cpp
        src/GuiHelper.cpp
        fonts/CetoneFonts.cpp
        images/CS2_Art.cpp
    FILES_COMMON
        src/full_parameters.cpp
)

