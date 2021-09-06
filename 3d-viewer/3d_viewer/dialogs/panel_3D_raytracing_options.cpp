/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2017 Jean-Pierre Charras, jp.charras at wanadoo.fr
 * Copyright (C) 2014-2021 KiCad Developers, see AUTHORS.txt for contributors.
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

#include <pgm_base.h>
#include <settings/settings_manager.h>
#include <eda_3d_viewer_settings.h>
#include "panel_3D_raytracing_options.h"


PANEL_3D_RAYTRACING_OPTIONS::PANEL_3D_RAYTRACING_OPTIONS( wxWindow* aParent ) :
        PANEL_3D_RAYTRACING_OPTIONS_BASE( aParent )
{
}


void PANEL_3D_RAYTRACING_OPTIONS::ResetPanel()
{
    SETTINGS_MANAGER& mgr = Pgm().GetSettingsManager();
    EDA_3D_VIEWER_SETTINGS* cfg = mgr.GetAppSettings<EDA_3D_VIEWER_SETTINGS>();

    cfg->m_Render.raytrace_lightColorCamera = COLOR4D( 0.2, 0.2, 0.2, 1.0 );
    cfg->m_Render.raytrace_lightColorTop = COLOR4D( 0.247, 0.247, 0.247, 1.0 );
    cfg->m_Render.raytrace_lightColorBottom = COLOR4D( 0.247, 0.247, 0.247, 1.0 );

    const std::vector<int> default_elevation =
    {
        67,  67,  67,  67, -67, -67, -67, -67,
    };

    const std::vector<int> default_azimuth =
    {
        45, 135, 225, 315, 45, 135, 225, 315,
    };

    for( size_t i = 0; i < 8; ++i )
    {
        cfg->m_Render.raytrace_lightElevation[i] = default_elevation[i];
        cfg->m_Render.raytrace_lightAzimuth[i] = default_azimuth[i];
    }

    TransferColorDataToWindow();
}


void PANEL_3D_RAYTRACING_OPTIONS::TransferColorDataToWindow()
{
    SETTINGS_MANAGER& mgr = Pgm().GetSettingsManager();
    EDA_3D_VIEWER_SETTINGS* cfg = mgr.GetAppSettings<EDA_3D_VIEWER_SETTINGS>();

    auto transfer_color = [] ( COLOR4D aColor, COLOR_SWATCH *aTarget )
    {
        aTarget->SetSupportsOpacity( false );
        aTarget->SetDefaultColor( KIGFX::COLOR4D( 0.5, 0.5, 0.5, 1.0 ) );
        aTarget->SetSwatchColor( aColor, false );
    };

    transfer_color( cfg->m_Render.raytrace_lightColorCamera, m_colourPickerCameraLight );
    transfer_color( cfg->m_Render.raytrace_lightColorTop, m_colourPickerTopLight );
    transfer_color( cfg->m_Render.raytrace_lightColorBottom, m_colourPickerBottomLight );

    transfer_color( cfg->m_Render.raytrace_lightColor[0], m_colourPickerLight1 );
    transfer_color( cfg->m_Render.raytrace_lightColor[1], m_colourPickerLight2 );
    transfer_color( cfg->m_Render.raytrace_lightColor[2], m_colourPickerLight3 );
    transfer_color( cfg->m_Render.raytrace_lightColor[3], m_colourPickerLight4 );

    transfer_color( cfg->m_Render.raytrace_lightColor[4], m_colourPickerLight5 );
    transfer_color( cfg->m_Render.raytrace_lightColor[5], m_colourPickerLight6 );
    transfer_color( cfg->m_Render.raytrace_lightColor[6], m_colourPickerLight7 );
    transfer_color( cfg->m_Render.raytrace_lightColor[7], m_colourPickerLight8 );

    m_lightElevation1->SetValue( cfg->m_Render.raytrace_lightElevation[0] );
    m_lightElevation2->SetValue( cfg->m_Render.raytrace_lightElevation[1] );
    m_lightElevation3->SetValue( cfg->m_Render.raytrace_lightElevation[2] );
    m_lightElevation4->SetValue( cfg->m_Render.raytrace_lightElevation[3] );
    m_lightElevation5->SetValue( cfg->m_Render.raytrace_lightElevation[4] );
    m_lightElevation6->SetValue( cfg->m_Render.raytrace_lightElevation[5] );
    m_lightElevation7->SetValue( cfg->m_Render.raytrace_lightElevation[6] );
    m_lightElevation8->SetValue( cfg->m_Render.raytrace_lightElevation[7] );

    m_lightAzimuth1->SetValue( cfg->m_Render.raytrace_lightAzimuth[0] );
    m_lightAzimuth2->SetValue( cfg->m_Render.raytrace_lightAzimuth[1] );
    m_lightAzimuth3->SetValue( cfg->m_Render.raytrace_lightAzimuth[2] );
    m_lightAzimuth4->SetValue( cfg->m_Render.raytrace_lightAzimuth[3] );
    m_lightAzimuth5->SetValue( cfg->m_Render.raytrace_lightAzimuth[4] );
    m_lightAzimuth6->SetValue( cfg->m_Render.raytrace_lightAzimuth[5] );
    m_lightAzimuth7->SetValue( cfg->m_Render.raytrace_lightAzimuth[6] );
    m_lightAzimuth8->SetValue( cfg->m_Render.raytrace_lightAzimuth[7] );
}


bool PANEL_3D_RAYTRACING_OPTIONS::TransferDataToWindow()
{
    SETTINGS_MANAGER& mgr = Pgm().GetSettingsManager();
    EDA_3D_VIEWER_SETTINGS* cfg = mgr.GetAppSettings<EDA_3D_VIEWER_SETTINGS>();

    m_cbRaytracing_renderShadows->SetValue( cfg->m_Render.raytrace_shadows );
    m_cbRaytracing_addFloor->SetValue( cfg->m_Render.raytrace_backfloor );
    m_cbRaytracing_showRefractions->SetValue( cfg->m_Render.raytrace_refractions );
    m_cbRaytracing_showReflections->SetValue( cfg->m_Render.raytrace_reflections );
    m_cbRaytracing_postProcessing->SetValue( cfg->m_Render.raytrace_post_processing );
    m_cbRaytracing_antiAliasing->SetValue( cfg->m_Render.raytrace_anti_aliasing );
    m_cbRaytracing_proceduralTextures->SetValue( cfg->m_Render.raytrace_procedural_textures );

    m_numSamples_Shadows->SetValue( cfg->m_Render.raytrace_nrsamples_shadows );
    m_numSamples_Reflections->SetValue( cfg->m_Render.raytrace_nrsamples_reflections );
    m_numSamples_Refractions->SetValue( cfg->m_Render.raytrace_nrsamples_refractions );

    m_spreadFactor_Shadows->SetValue( cfg->m_Render.raytrace_spread_shadows * 100.0f );
    m_spreadFactor_Reflections->SetValue( cfg->m_Render.raytrace_spread_reflections * 100.0f );
    m_spreadFactor_Refractions->SetValue( cfg->m_Render.raytrace_spread_refractions * 100.0f );

    m_recursiveLevel_Reflections->SetValue( cfg->m_Render.raytrace_recursivelevel_reflections );
    m_recursiveLevel_Refractions->SetValue( cfg->m_Render.raytrace_recursivelevel_refractions );

    TransferColorDataToWindow();

    return true;
}


bool PANEL_3D_RAYTRACING_OPTIONS::TransferDataFromWindow()
{
    SETTINGS_MANAGER& mgr = Pgm().GetSettingsManager();
    EDA_3D_VIEWER_SETTINGS* cfg = mgr.GetAppSettings<EDA_3D_VIEWER_SETTINGS>();

    cfg->m_Render.raytrace_shadows = m_cbRaytracing_renderShadows->GetValue();
    cfg->m_Render.raytrace_backfloor = m_cbRaytracing_addFloor->GetValue();
    cfg->m_Render.raytrace_refractions = m_cbRaytracing_showRefractions->GetValue();
    cfg->m_Render.raytrace_reflections = m_cbRaytracing_showReflections->GetValue();
    cfg->m_Render.raytrace_post_processing = m_cbRaytracing_postProcessing->GetValue();
    cfg->m_Render.raytrace_anti_aliasing = m_cbRaytracing_antiAliasing->GetValue();
    cfg->m_Render.raytrace_procedural_textures = m_cbRaytracing_proceduralTextures->GetValue();

    cfg->m_Render.raytrace_nrsamples_shadows = m_numSamples_Shadows->GetValue();
    cfg->m_Render.raytrace_nrsamples_reflections = m_numSamples_Reflections->GetValue();
    cfg->m_Render.raytrace_nrsamples_refractions = m_numSamples_Refractions->GetValue();

    cfg->m_Render.raytrace_spread_shadows =
            static_cast<float>( m_spreadFactor_Shadows->GetValue() ) / 100.0f;
    cfg->m_Render.raytrace_spread_reflections =
            static_cast<float>( m_spreadFactor_Reflections->GetValue() ) / 100.0f;
    cfg->m_Render.raytrace_spread_refractions =
            static_cast<float>( m_spreadFactor_Refractions->GetValue() ) / 100.0f;

    cfg->m_Render.raytrace_recursivelevel_reflections = m_recursiveLevel_Reflections->GetValue();
    cfg->m_Render.raytrace_recursivelevel_refractions = m_recursiveLevel_Refractions->GetValue();

    cfg->m_Render.raytrace_lightColorCamera = m_colourPickerCameraLight->GetSwatchColor();
    cfg->m_Render.raytrace_lightColorTop = m_colourPickerTopLight->GetSwatchColor();
    cfg->m_Render.raytrace_lightColorBottom = m_colourPickerBottomLight->GetSwatchColor();

    cfg->m_Render.raytrace_lightColor[0] = m_colourPickerLight1->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[1] = m_colourPickerLight2->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[2] = m_colourPickerLight3->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[3] = m_colourPickerLight4->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[4] = m_colourPickerLight5->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[5] = m_colourPickerLight6->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[6] = m_colourPickerLight7->GetSwatchColor();
    cfg->m_Render.raytrace_lightColor[7] = m_colourPickerLight8->GetSwatchColor();

    cfg->m_Render.raytrace_lightElevation[0] = m_lightElevation1->GetValue();
    cfg->m_Render.raytrace_lightElevation[1] = m_lightElevation2->GetValue();
    cfg->m_Render.raytrace_lightElevation[2] = m_lightElevation3->GetValue();
    cfg->m_Render.raytrace_lightElevation[3] = m_lightElevation4->GetValue();
    cfg->m_Render.raytrace_lightElevation[4] = m_lightElevation5->GetValue();
    cfg->m_Render.raytrace_lightElevation[5] = m_lightElevation6->GetValue();
    cfg->m_Render.raytrace_lightElevation[6] = m_lightElevation7->GetValue();
    cfg->m_Render.raytrace_lightElevation[7] = m_lightElevation8->GetValue();

    cfg->m_Render.raytrace_lightAzimuth[0] = m_lightAzimuth1->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[1] = m_lightAzimuth2->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[2] = m_lightAzimuth3->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[3] = m_lightAzimuth4->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[4] = m_lightAzimuth5->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[5] = m_lightAzimuth6->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[6] = m_lightAzimuth7->GetValue();
    cfg->m_Render.raytrace_lightAzimuth[7] = m_lightAzimuth8->GetValue();

    return true;
}
