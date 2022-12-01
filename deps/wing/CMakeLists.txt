add_library(wing32 SHARED)
include(TargetExports)

target_sources(wing32 PRIVATE
    hooker.cpp
    hooker.h
    mapview.cpp
    mapview.h
    proxydll.cpp
    sha1.cpp
    sha1.h
    wing32.c
    wing32.h
)

target_link_libraries(wing32 PRIVATE compat)
target_include_directories(wing32 INTERFACE .)

target_exports(wing32 SYMBOLS
    WinGCreateDC
    WinGRecommendDIBFormat
    WinGCreateBitmap
    WinGGetDIBPointer
    WinGSetDIBColorTable
    WinGGetDIBColorTable
    WinGCreateHalftonePalette
    WinGCreateHalftoneBrush
    WinGStretchBlt
    WinGBitBlt
)
