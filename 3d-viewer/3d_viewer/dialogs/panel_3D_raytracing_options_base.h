///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include "widgets/color_swatch.h"
#include "widgets/resettable_panel.h"
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PANEL_3D_RAYTRACING_OPTIONS_BASE
///////////////////////////////////////////////////////////////////////////////
class PANEL_3D_RAYTRACING_OPTIONS_BASE : public RESETTABLE_PANEL
{
	private:

	protected:
		wxCheckBox* m_cbRaytracing_proceduralTextures;
		wxCheckBox* m_cbRaytracing_addFloor;
		wxCheckBox* m_cbRaytracing_antiAliasing;
		wxCheckBox* m_cbRaytracing_postProcessing;
		wxStaticText* m_staticText19;
		wxStaticText* m_staticText201;
		wxStaticText* m_staticText211;
		wxCheckBox* m_cbRaytracing_renderShadows;
		wxSpinCtrl* m_numSamples_Shadows;
		wxSpinCtrlDouble* m_spreadFactor_Shadows;
		wxCheckBox* m_cbRaytracing_showReflections;
		wxSpinCtrl* m_numSamples_Reflections;
		wxSpinCtrlDouble* m_spreadFactor_Reflections;
		wxSpinCtrl* m_recursiveLevel_Reflections;
		wxCheckBox* m_cbRaytracing_showRefractions;
		wxSpinCtrl* m_numSamples_Refractions;
		wxSpinCtrlDouble* m_spreadFactor_Refractions;
		wxSpinCtrl* m_recursiveLevel_Refractions;
		wxStaticText* m_staticText17;
		COLOR_SWATCH* m_colourPickerCameraLight;
		wxStaticText* m_staticText5;
		COLOR_SWATCH* m_colourPickerTopLight;
		wxStaticText* m_staticText6;
		COLOR_SWATCH* m_colourPickerBottomLight;
		wxStaticText* m_staticText20;
		wxStaticText* m_staticText18;
		wxStaticText* m_staticText27;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText21;
		COLOR_SWATCH* m_colourPickerLight1;
		wxSpinCtrl* m_lightElevation1;
		wxSpinCtrl* m_lightAzimuth1;
		wxStaticText* m_staticText22;
		COLOR_SWATCH* m_colourPickerLight5;
		wxSpinCtrl* m_lightElevation5;
		wxSpinCtrl* m_lightAzimuth5;
		wxStaticText* m_staticText23;
		COLOR_SWATCH* m_colourPickerLight2;
		wxSpinCtrl* m_lightElevation2;
		wxSpinCtrl* m_lightAzimuth2;
		wxStaticText* m_staticText24;
		COLOR_SWATCH* m_colourPickerLight6;
		wxSpinCtrl* m_lightElevation6;
		wxSpinCtrl* m_lightAzimuth6;
		wxStaticText* m_staticText25;
		COLOR_SWATCH* m_colourPickerLight3;
		wxSpinCtrl* m_lightElevation3;
		wxSpinCtrl* m_lightAzimuth3;
		wxStaticText* m_staticText26;
		COLOR_SWATCH* m_colourPickerLight7;
		wxSpinCtrl* m_lightElevation7;
		wxSpinCtrl* m_lightAzimuth7;
		wxStaticText* m_staticText171;
		COLOR_SWATCH* m_colourPickerLight4;
		wxSpinCtrl* m_lightElevation4;
		wxSpinCtrl* m_lightAzimuth4;
		wxStaticText* m_staticText181;
		COLOR_SWATCH* m_colourPickerLight8;
		wxSpinCtrl* m_lightElevation8;
		wxSpinCtrl* m_lightAzimuth8;

	public:

		PANEL_3D_RAYTRACING_OPTIONS_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 795,478 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~PANEL_3D_RAYTRACING_OPTIONS_BASE();

};

