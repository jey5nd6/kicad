/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2007-2017 Jean-Pierre Charras, jp.charras at wanadoo.fr
 * Copyright (C) 1992-2021 KiCad Developers, see CHANGELOG.TXT for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef BITMAPS_PNG_BITMAPS_LIST__H
#define BITMAPS_PNG_BITMAPS_LIST__H

/**
 * A list of all bitmap identifiers.  These map to multiple actual images, i.e. light and dark icon
 * themes, and eventually multi-resolution icons.
 */
enum class BITMAPS : unsigned int
{
    /*
     * Bitmap 0 is reserved for the invalid marker, so that classes using BITMAPS can forward-
     * declare this enum and zero-initialize it, which cuts down on the number of files that need
     * to be rebuilt when this enum is changed
     */
    INVALID_BITMAP = 0,

    about,
    add_aligned_dimension,
    add_arc,
    add_board,
    add_bus2bus,
    add_bus,
    add_center_dimension,
    add_circle,
    add_component,
    add_corner,
    add_dashed_line,
    add_document,
    add_gerber,
    add_glabel,
    add_graphical_segments,
    add_graphical_polygon,
    add_hierarchical_label,
    add_hierarchical_subsheet,
    add_hierar_pin,
    add_junction,
    add_keepout_area,
    add_label,
    add_leader,
    add_library,
    add_line2bus,
    add_line_label,
    add_line,
    add_orthogonal_dimension,
    add_pcb_target,
    add_power,
    add_rectangle,
    add_symbol_to_schematic,
    add_tracks,
    add_via,
    add_zone_cutout,
    add_zone,
    anchor,
    annotate_down_right,
    annotate_right_down,
    annotate,
    align_items,
    align_items_left,
    align_items_right,
    align_items_top,
    align_items_bottom,
    align_items_center,
    align_items_middle,
    apply_pad_settings,
    array,
    auto_associate,
    auto_delete_track,
    auto_track_width,
    autoplace_fields,
    axis3d_back,
    axis3d_bottom,
    axis3d_front,
    axis3d_left,
    axis3d_right,
    axis3d_top,
    axis3d,
    break_bus,
    break_line,
    bug,
    bus_definition_tool,
    calculator,
    cancel,
    change_entry_orient,
    change_label,
    change_hlabel,
    change_glabel,
    change_text,
    contrast_mode,
    checked_ok,
    color_materials,
    component_select_alternate_shape,
    component_select_unit,
    config,
    convert,
    copper_layers_setup,
    copy,
    copy_pad_settings,
    cursor_shape,
    custom_pad_to_primitives,
    cursor,
    curved_ratsnest,
    cut,
    datasheet,
    delete_association,
    delete_cursor,
    delete_gerber,
    delete_sheet,
    dialog_warning,
    directory,
    directory_browser,
    directory_open,
    display_options,
    distribute_horizontal,
    distribute_vertical,
    down,
    dummy_item,
    ortho,
    drag,
    drag_segment_withslope,
    drc_off,
    drc,
    duplicate,
    edit_comp_footprint,
    edit_comp_ref,
    edit_comp_value,
    editor,
    edit_cmp_symb_links,
    edit,
    edge_to_copper_clearance,
    eeschema,
    enter_sheet,
    erc,
    ercerr,
    ercwarn,
    erc_green,
    exchange,
    exit,
    export3d,
    export_cmp,
    export_dsn,
    export_idf,
    export_file,
    export_footprint_names,
    export_module,
    export_part,
    export_png,
    export_step,
    export_svg,
    export_to_pcbnew,
    fabrication,
    file_bom,
    file_drl,
    file_dsn,
    file_gbr,
    file_gerber_job,
    file_html,
    file_idf,
    file_pdf,
    file_pos,
    file_svg,
    fill_zone,
    filter,
    find,
    find_replace,
    flag,
    flip_board,
    fonts,
    gbr_select_mode0,
    gbr_select_mode1,
    gbr_select_mode2,
    gerber_file,
    gerbview_clear_layers,
    gerbview_show_negative_objects,
    general_deletions,
    general_ratsnest,
    go_down,
    go_up,
    grid_select_axis,
    grid_select,
    grid,
    group,
    group_enter,
    group_leave,
    group_remove,
    group_ungroup,
    help,
    help_online,
    hidden_pin,
    hide_ratsnest,
    hierarchy_nav,
    hotkeys,
    hole_to_copper_clearance,
    hole_to_hole_clearance,
    icon_cvpcb_24,
    icon_cvpcb,
    icon_eeschema,
    icon_footprint_browser,
    icon_gerbview,
    icon_kicad,
    icon_modedit,
    icon_pcbnew,
    icon_3d,
    icon_bitmap2component,
    icon_libedit,
    icon_pcbcalculator,
    icon_pagelayout_editor,

    icon_bitmap2component_24,
    icon_eeschema_24,
    icon_gerbview_24,
    icon_kicad_24,
    icon_libedit_24,
    icon_modedit_24,
    icon_pagelayout_editor_24,
    icon_pcbcalculator_24,
    icon_pcbnew_24,

    icon_bitmap2component_16,
    icon_eeschema_16,
    icon_gerbview_16,
    icon_kicad_16,
    icon_libedit_16,
    icon_modedit_16,
    icon_pagelayout_editor_16,
    icon_pcbcalculator_16,
    icon_pcbnew_16,

    icon_bitmap2component_32,
    icon_eeschema_32,
    icon_gerbview_32,
    icon_kicad_32,
    icon_libedit_32,
    icon_modedit_32,
    icon_pagelayout_editor_32,
    icon_pcbcalculator_32,
    icon_pcbnew_32,

    image,
    import_brd_file,
    import_document,
    import_footprint_names,
    import_hierarchical_label,
    import_module,
    import_part,
    import_project,
    import_vector,
    import,
    import3d,
    info,
    insert_module_board,
    invisible_text,
    kicad_icon_small,
    language,
    layers_manager,
    leave_sheet,
    left,
    libedit,
    lib_next,
    lib_previous,
    library_browser,
    library_archive,
    library_archive_as,
    library,
    library_table,
    lines90,
    list_nets_16,
    list_nets,
    load_drill,
    load_gerber,
    load_module_board,
    locked,
    lock_unlock,
    measurement,
    minus,
    mirror_h,
    mirror_v,
    mode_module,
    mode_track,
    module_editor,
    module_wizard,
    module_filtered_list,
    module_pin_filtered_list,
    module_library_list,
    module_name_filtered_list,
    module_full_list,
    module_options,
    module,
    morgan1,
    morgan2,
    move_exactly,
    move_relative,
    move,
    mw_add_gap,
    mw_add_line,
    mw_add_shape,
    mw_add_stub_arc,
    mw_add_stub,
    net_highlight,
    net_highlight_schematic,
    netlist,
    net_locked,
    net_unlocked,
    new_board,
    new_component,
    new_document,
    new_footprint,
    new_generic,
    new_library,
    new_page_layout,
    new_project,
    new_python,
    noconn,
    normal,
    open_project,
    options_3drender,
    options_board,
    options_generic_16,
    options_generic,
    options_pad,
    options_schematic,
    opt_show_polygon,
    pad_sketch,
    pad,
    pad_enumerate,
    pad_number,
    pads_mask_layers,
    pads_npth,
    pads_npth_top_bottom,
    pads_npth_top,
    pads_npth_bottom,
    pads_remove,
    pads_remove_unused,
    pads_remove_unused_keep_bottom,
    pads_reset_unused,
    pagelayout_normal_view_mode,
    pagelayout_special_view_mode,
    part_properties,
    paste,
    path,
    pcb_target,
    pcbnew,
    pin2pin,
    pin_size_to,
    pin_show_etype,
    pin_table,
    pinorient_right,
    pinorient_left,
    pinorient_up,
    pinorient_down,
    pinshape_nonlogic,
    pinshape_normal,
    pinshape_invert,
    pinshape_clock_fall,
    pinshape_clock_normal,
    pinshape_clock_invert,
    pinshape_active_low_input,
    pinshape_clock_active_low,
    pinshape_active_low_output,
    pintype_input,
    pintype_output,
    pintype_bidi,
    pintype_3states,
    pintype_passive,
    pintype_notspecif,
    pintype_powerinput,
    pintype_poweroutput,
    pintype_opencoll,
    pintype_openemit,
    pintype_noconnect,
    pintype_nic,
    pin,
    plot,
    polar_coord,
    post_bom,
    post_compo,
    post_drill,
    post_d356,
    post_gerber,
    post_gencad,
    post_module,
    push_pad_settings,
    post_rpt,
    preference,
    primitives_to_custom_pad,
    project,
    project_close,
    project_kicad,
    print_button,
    ps_router,
    ps_diff_pair,
    ps_diff_pair_gap,
    ps_diff_pair_tune_length,
    ps_diff_pair_tune_phase,
    ps_diff_pair_via_gap,
    ps_tune_length,
    puzzle_piece,
    py_script,
    question_mark,
    reannotate_right_down,
    reannotate_left_down,
    reannotate_right_up,
    reannotate_left_up,
    reannotate_down_left,
    reannotate_up_left,
    reannotate_down_right,
    reannotate_up_right,
    recent,
    redo,
    red,
    refresh,
    render_mode,
    reload,
    repaint,
    resize_sheet,
    rescue,
    right,
    router_len_tuner,
    router_len_tuner_setup,
    router_len_tuner_amplitude_decr,
    router_len_tuner_amplitude_incr,
    router_len_tuner_dist_decr,
    router_len_tuner_dist_incr,
    rotate_cw,
    rotate_ccw,
    rotate_cw_x,
    rotate_ccw_x,
    rotate_cw_y,
    rotate_ccw_y,
    rotate_cw_z,
    rotate_ccw_z,
    save_as,
    save,
    search_tree,
    select_layer_pair,
    select_w_layer,
    select_same_sheet,
    sheetset,
    set_origin,
    shape_3d,
    shape_3d_back,
    show_dcodenumber,
    show_footprint,
    show_graphics_mode,
    show_mod_edge,
    show_all_layers,
    show_no_layers,
    show_front_assembly_layers,
    show_back_assembly_layers,
    show_all_front_layers,
    show_all_back_layers,
    show_no_copper_layers,
    show_all_copper_layers,
    show_ratsnest,
    showtrack,
    show_zone,
    show_zone_disable,
    show_zone_outline_only,
    small_down,
    small_edit,
    small_folder,
    small_library,
    small_plus,
    small_refresh,
    small_trash,
    small_up,
    small_warning,
    special_tools,
    spreadsheet,
    stroke_dash,
    stroke_dashdot,
    stroke_dot,
    stroke_solid,
    swap_layer,
    switch_corner_rounding_shape,
    text,
    text_sketch,
    three_d,
    tool_ratsnest,
    tools,
    track_locked,
    track_sketch,
    track_unlocked,
    trash,
    tree_nosel,
    tree_sel,
    triangle_right,
    triangle_down,
    undelete,
    undo,
    unit_inch,
    unit_mil,
    unit_mm,
    unknown,
    unlocked,
    unzip,
    up,
    update_fields,
    update_pcb_from_sch,
    update_sch_from_pcb,
    via,
    via_microvia,
    via_buried,
    via_sketch,
    via_annulus,
    via_diameter,
    via_hole_diameter,
    viewlibs_icon,
    visibility,
    visibility_off,
    width_track_via,
    width_track,
    wizard_add_fplib_icon,
    wizard_add_fplib_small,
    www,
    zip,
    zone_duplicate,
    zone_fillet,
    zone_unfill,
    zoom_area,
    zoom_auto_fit_in_page,
    zoom_center_on_screen,
    zoom_fit_in_page,
    zoom_fit_to_objects,
    zoom_in,
    zoom_out,
    zoom_page,
    zoom_selection,
    zoom,
    tune_diff_pair_length_legend,
    tune_diff_pair_skew_legend,
    tune_single_track_length_legend,
    simulator,
    sim_run,
    sim_stop,
    sim_tune,
    sim_probe,
    sim_add_signal
};


inline bool operator!( const BITMAPS& aBitmap ) { return aBitmap == BITMAPS::INVALID_BITMAP; }

#endif // BITMAPS_PNG_BITMAPS_LIST__H