set(BUSINESS_SRC
    about.cpp
    about.h
    addplyr.cpp
    addplyr.h
    ai.cpp
    ai.h
    auction.cpp
    auction.h
    bank.cpp
    bank.h
    bankrupt.cpp
    bankrupt.h
    board.cpp
    board.h
    buybldg.cpp
    buybldg.h
    buyprop.cpp
    buyprop.h
    cards.cpp
    cards.h
    cleanup.cpp
    cleanup.h
    colorgrp.cpp
    colorgrp.h
    command.cpp
    command.h
    crc.cpp
    crc.h
    currency.cpp
    currency.h
    debt.cpp
    debt.h
    debug.cpp
    debug.h
    dib.cpp
    dib.h
    dice.cpp
    dice.h
    drawcard.cpp
    drawcard.h
    exprent.cpp
    exprent.h
    file/file.cpp
    file/file.h
    file/filecach.cpp
    file/filecach.h
    file/filedata.cpp
    file/filedata.h
    file/fileglob.cpp
    file/fileglob.h
    file/fileinit.cpp
    file/fileinit.h
    file/fileio.cpp
    file/fileio.h
    file/filelib.cpp
    file/filelib.h
    file/findfile.cpp
    file/findfile.h
    freepark.cpp
    freepark.h
    gamestat.cpp
    gamestat.h
    getvalue.cpp
    getvalue.h
    globals.cpp
    globals.h
    graphics.cpp
    graphics.h
    host.cpp
    host.h
    househot.cpp
    househot.h
    interupt.cpp
    interupt.h
    intrface.cpp
    intrface.h
    intro.cpp
    intro.h
    jail.cpp
    jail.h
    joiner.cpp
    joiner.h
    load.cpp
    load.h
    loadsave.cpp
    loadsave.h
    luxtax.cpp
    luxtax.h
    mcgaprim/buffer.cpp
    mcgaprim/buffer.h
    mcgaprim/fillrect.asm
    mcgaprim/fillrect.h
    mcgaprim/gbuffer.cpp
    mcgaprim/gbuffer.h
    mcgaprim/getmcga.asm
    mcgaprim/getmcga.h
    mem/alloc.cpp
    mem/alloc.h
    mem/mem.cpp
    mem/mem.h
    mem/newdel.cpp
    mem/newdel.h
    menus.cpp
    menus.h
    message.cpp
    message.h
    misc/exit.cpp
    misc/exit.h
    misc/findargv.cpp
    misc/findargv.h
    monochrm.cpp
    monochrm.h
    monomodm.cpp
    monomodm.h
    mortgage.cpp
    mortgage.h
    movement.cpp
    movement.h
    music.cpp
    music.h
    newgame.cpp
    newgame.h
    options.cpp
    options.h
    palette.cpp
    palette.h
    players.cpp
    players.h
    postmono.cpp
    postmono.h
    property.cpp
    property.h
    railroad.cpp
    railroad.h
    raisecsh.cpp
    raisecsh.h
    rle.cpp
    rle.h
    rules.cpp
    rules.h
    sellbldg.cpp
    sellbldg.h
    shape/drawshp.asm
    shape/drawshp.h
    shape/ds_dn.asm
    shape/ds_dn.h
    shape/ds_dr.asm
    shape/ds_dr.h
    shape/ds_ds.asm
    shape/ds_ds.h
    shape/ds_dsr.asm
    shape/ds_dsr.h
    shape/ds_lrs.asm
    shape/ds_lrs.h
    shape/ds_ls.asm
    shape/ds_ls.h
    shape/ds_lsrs.asm
    shape/ds_lsrs.h
    shape/ds_lss.asm
    shape/ds_lss.h
    shape/ds_rrs.asm
    shape/ds_rrs.h
    shape/ds_rs.asm
    shape/ds_rs.h
    shape/ds_rsrs.asm
    shape/ds_rsrs.h
    shape/ds_rss.asm
    shape/ds_rss.h
    shape/ds_table.asm
    shape/ds_table.h
    shape/getshape.cpp
    shape/getshape.h
    shape/setshape.asm
    shape/setshape.h
    shape.cpp
    shape.h
    showdib.cpp
    showdib.h
    sounds.cpp
    sounds.h
    standard.cpp
    standard.h
    startup.cpp
    startup.h
    status.cpp
    status.h
    stringsjb.cpp
    stringsjb.h
    talk.cpp
    talk.h
    tempcode.cpp
    tempcode.h
    trade.cpp
    trade.h
    utility.cpp
    utility.h
    vq.cpp
    vq.h
    vqa32/audio.cpp
    vqa32/audio.h
    vqa32/config.cpp
    vqa32/config.h
    vqa32/drawer.cpp
    vqa32/drawer.h
    vqa32/loader.cpp
    vqa32/loader.h
    vqa32/monodisp.cpp
    vqa32/monodisp.h
    vqa32/task.cpp
    vqa32/task.h
    vqa32/unvqbuff.asm
    vqa32/unvqbuff.h
    vqa32/unvqrsd.asm
    vqa32/unvqrsd.h
    vqm32/mcgabuf.asm
    vqm32/mcgabuf.h
    vqm32/mono.asm
    vqm32/mono.h
    vqm32/palette.asm
    vqm32/palette.h
    vqm32/portio.asm
    vqm32/portio.h
    vqm32/vb.asm
    vqm32/vb.h
    wallpapr.cpp
    wallpapr.h
    web.cpp
    web.h
    win.cpp
    win.h
    winsock.cpp
    winsock.h
    wm.cpp
    wm.h
    wndproc.cpp
    wndproc.h
    wsa/wsa.cpp
    wsa/wsa.h
)

if(BUILD_STANDALONE)
    if(WINDOWS)
        include(ProductVersion)
        # Generate windows version info.
        generate_product_version(
            JBSTD_RC
            NAME "Business board game simulation"
            BUNDLE "Just Business"
            VERSION_MAJOR 1
            VERSION_MINOR 0
            COMPANY_NAME "Assembly Armarda"
            COMPANY_COPYRIGHT "Built from code released under GPLv3"
            ORIGINAL_FILENAME "justbusiness.exe"
            RCFILE_PREFIX "jbstd"
        )
    endif()

    add_executable(justbusiness main.cpp main.h ${BUSINESS_SRC} ${JBSTD_RC})
    target_link_libraries(justbusiness PRIVATE wing32)
endif()

if(BUILD_DLL)
    if(WINDOWS)
        include(ProductVersion)
        # Generate windows version info.
        generate_product_version(
            JBDLL_RC
            NAME "Business Board Game Simulation"
            BUNDLE "Just Business"
            VERSION_MAJOR 1
            VERSION_MINOR 0
            COMPANY_NAME "Assembly Armarda"
            COMPANY_COPYRIGHT "Built from code released under GPLv3"
            ORIGINAL_FILENAME "justbusiness.dll"
            RCFILE_PREFIX "jbdll"
        )
    endif()

    add_library(justbusiness_dll SHARED dll/dllmain.cpp dll/hookglobals.cpp ${BUSINESS_SRC} ${JBDLL_RC})
    target_compile_definitions(justbusiness_dll PRIVATE DLL_BUILD)
    target_link_libraries(justbusiness_dll PRIVATE wing32)
    set_target_properties(justbusiness_dll PROPERTIES OUTPUT_NAME justbusiness PDB_NAME justbusinessdll)
    target_exports(justbusiness_dll SYMBOLS 
        Setup_Hooks
    )
endif()
