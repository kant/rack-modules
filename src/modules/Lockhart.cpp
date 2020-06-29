/*
 * Copyright (c) 2020 Dave French <contact/dot/dave/dot/french3/at/googlemail/dot/com>
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include "plugin.hpp"
#include "Lockhart.h"
#include "WidgetComposite.h"
#include "ctrl/SqMenuItem.h"

using Comp = LockhartComp<WidgetComposite>;

struct Lockhart : Module
{
    std::shared_ptr<Comp> lh;

    Lockhart()
    {
        config (Comp::NUM_PARAMS, Comp::NUM_INPUTS, Comp::NUM_OUTPUTS, Comp::NUM_LIGHTS);
        lh = std::make_shared<Comp> (this);
        std::shared_ptr<IComposite> icomp = Comp::getDescription();
        SqHelper::setupParams (icomp, this);
        onSampleRateChange();
        lh->init();
    }

    void onSampleRateChange() override
    {
        float rate = SqHelper::engineGetSampleRate();
        lh->setSampleRate (rate);
    }

    void process (const ProcessArgs& args) override
    {
        lh->step();
    }
};

// User Interface *************************************

struct GridButton : app::SvgSwitch
{
    GridButton()
    {
        momentary = true;
        addFrame (APP->window->loadSvg (asset::plugin (pluginInstance, "res/Grid_button_gray.svg")));
    }
};

struct GridButtonRound : app::SvgSwitch
{
    GridButtonRound()
    {
        momentary = true;
        addFrame (APP->window->loadSvg (asset::plugin (pluginInstance, "res/Grid_button_round_gray.svg")));
    }
};

template <typename TBase>
struct GridButtonLight : TBase
{
    GridButtonLight()
    {
        this->bgColor = color::BLACK_TRANSPARENT;
        this->box.size = app::mm2px (math::Vec (8.33, 8.33));
    }
    void drawLight (const widget::Widget::DrawArgs& args) override
    {
        nvgBeginPath (args.vg);
        nvgRoundedRect (args.vg, 0, 0, this->box.size.x, this->box.size.y, 2.0);

        // Background
        if (this->bgColor.a > 0.0)
        {
            nvgFillColor (args.vg, this->bgColor);
            nvgFill (args.vg);
        }

        // Foreground
        if (this->color.a > 0.0)
        {
            nvgFillColor (args.vg, this->color);
            nvgFill (args.vg);
        }

        // Border
        if (this->borderColor.a > 0.0)
        {
            nvgStrokeWidth (args.vg, 0.5);
            nvgStrokeColor (args.vg, this->borderColor);
            nvgStroke (args.vg);
        }
    }
};

template <typename TBase>
struct GridButtonRoundLight : TBase
{
    GridButtonRoundLight()
    {
        this->bgColor = color::BLACK_TRANSPARENT;
        this->box.size = app::mm2px (math::Vec (8.33, 8.33));
    }
};

struct LockhartWidget : ModuleWidget
{
    LockhartWidget (Lockhart* module)
    {
        setModule (module);
        std::shared_ptr<IComposite> icomp = Comp::getDescription();
        box.size = Vec (10 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

        setPanel (APP->window->loadSvg (asset::plugin (pluginInstance, "res/Lockhart.svg")));

        addChild (createWidget<ScrewSilver> (Vec (RACK_GRID_WIDTH, 0)));
        addChild (createWidget<ScrewSilver> (Vec (box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild (createWidget<ScrewSilver> (Vec (RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild (createWidget<ScrewSilver> (Vec (box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 20.2)), module, Comp::GRID_1_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 20.2)), module, Comp::GRID_2_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 20.2)), module, Comp::GRID_3_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 20.2)), module, Comp::GRID_4_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 20.2)), module, Comp::GRID_5_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 20.2)), module, Comp::GRID_6_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 20.2)), module, Comp::GRID_7_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 20.2)), module, Comp::GRID_8_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 30.3)), module, Comp::GRID_1_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 30.3)), module, Comp::GRID_2_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 30.3)), module, Comp::GRID_3_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 30.3)), module, Comp::GRID_4_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 30.3)), module, Comp::GRID_5_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 30.3)), module, Comp::GRID_6_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 30.3)), module, Comp::GRID_7_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 30.3)), module, Comp::GRID_8_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 40.4)), module, Comp::GRID_1_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 40.4)), module, Comp::GRID_2_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 40.4)), module, Comp::GRID_3_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 40.4)), module, Comp::GRID_4_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 40.4)), module, Comp::GRID_5_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 40.4)), module, Comp::GRID_6_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 40.4)), module, Comp::GRID_7_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 40.4)), module, Comp::GRID_8_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 50.5)), module, Comp::GRID_1_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 50.5)), module, Comp::GRID_2_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 50.5)), module, Comp::GRID_3_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 50.5)), module, Comp::GRID_4_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 50.5)), module, Comp::GRID_5_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 50.5)), module, Comp::GRID_6_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 50.5)), module, Comp::GRID_7_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 50.5)), module, Comp::GRID_8_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 60.6)), module, Comp::GRID_1_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 60.6)), module, Comp::GRID_2_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 60.6)), module, Comp::GRID_3_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 60.6)), module, Comp::GRID_4_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 60.6)), module, Comp::GRID_5_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 60.6)), module, Comp::GRID_6_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 60.6)), module, Comp::GRID_7_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 60.6)), module, Comp::GRID_8_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 70.7)), module, Comp::GRID_1_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 70.7)), module, Comp::GIRD_2_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 70.7)), module, Comp::GRID_3_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 70.7)), module, Comp::GRID_4_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 70.7)), module, Comp::GRID_5_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 70.7)), module, Comp::GRID_6_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 70.7)), module, Comp::GRID_7_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 70.7)), module, Comp::GRID_8_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 80.8)), module, Comp::GRID_1_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 80.8)), module, Comp::GRID_2_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 80.8)), module, Comp::GRID_3_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 80.8)), module, Comp::GRID_4_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 80.8)), module, Comp::GRID_5_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 80.8)), module, Comp::GRID_6_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 80.8)), module, Comp::GRID_7_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 80.8)), module, Comp::GRID_8_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (55.88, 90.9)), module, Comp::GRID_1_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (66.04, 90.9)), module, Comp::GRID_2_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (76.2, 90.9)), module, Comp::GRID_3_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (86.36, 90.9)), module, Comp::GRID_4_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (96.52, 90.9)), module, Comp::GRID_5_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (106.68, 90.9)), module, Comp::GRID_6_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (116.84, 90.9)), module, Comp::GRID_7_8_PARAM));
        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (127.0, 90.9)), module, Comp::GRID_8_8_PARAM));

        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 20.2)), module, Comp::L1_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 30.3)), module, Comp::L2_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 40.4)), module, Comp::L3_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 50.5)), module, Comp::L4_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 60.6)), module, Comp::L5_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 70.7)), module, Comp::L6_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 80.8)), module, Comp::L7_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (142.24, 90.9)), module, Comp::L8_PARAM));

        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (55.88, 106.05)), module, Comp::SELECT_1_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (66.04, 106.05)), module, Comp::SELECT_2_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (76.2, 106.05)), module, Comp::SELECT_3_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (86.36, 106.05)), module, Comp::SELECT_4_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (96.52, 106.05)), module, Comp::SELECT_5_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (106.68, 106.05)), module, Comp::SELECT_6_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (116.84, 106.05)), module, Comp::SELECT_7_PARAM));
        addParam (SqHelper::createParamCentered<GridButtonRound> (icomp, mm2px (Vec (127.0, 106.05)), module, Comp::SELECT_8_PARAM));

        addParam (SqHelper::createParamCentered<GridButton> (icomp, mm2px (Vec (142.24, 106.05)), module, Comp::SHIFT_PARAM));

        // LEDS ********************

        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 20.2)), module, Comp::GRID_1_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 20.2)), module, Comp::GRID_2_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 20.2)), module, Comp::GRID_3_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 20.2)), module, Comp::GRID_4_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 20.2)), module, Comp::GRID_5_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 20.2)), module, Comp::GRID_6_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 20.2)), module, Comp::GRID_7_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 20.2)), module, Comp::GRID_8_1_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 30.3)), module, Comp::GRID_1_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 30.3)), module, Comp::GRID_2_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 30.3)), module, Comp::GRID_3_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 30.3)), module, Comp::GRID_4_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 30.3)), module, Comp::GRID_5_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 30.3)), module, Comp::GRID_6_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 30.3)), module, Comp::GRID_7_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 30.3)), module, Comp::GRID_8_2_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 40.4)), module, Comp::GRID_1_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 40.4)), module, Comp::GRID_2_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 40.4)), module, Comp::GRID_3_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 40.4)), module, Comp::GRID_4_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 40.4)), module, Comp::GRID_5_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 40.4)), module, Comp::GRID_6_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 40.4)), module, Comp::GRID_7_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 40.4)), module, Comp::GRID_8_3_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 50.5)), module, Comp::GRID_1_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 50.5)), module, Comp::GRID_2_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 50.5)), module, Comp::GRID_3_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 50.5)), module, Comp::GRID_4_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 50.5)), module, Comp::GRID_5_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 50.5)), module, Comp::GRID_6_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 50.5)), module, Comp::GRID_7_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 50.5)), module, Comp::GRID_8_4_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 60.6)), module, Comp::GRID_1_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 60.6)), module, Comp::GRID_2_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 60.6)), module, Comp::GRID_3_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 60.6)), module, Comp::GRID_4_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 60.6)), module, Comp::GRID_5_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 60.6)), module, Comp::GRID_6_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 60.6)), module, Comp::GRID_7_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 60.6)), module, Comp::GRID_8_5_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 70.7)), module, Comp::GRID_1_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 70.7)), module, Comp::GIRD_2_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 70.7)), module, Comp::GRID_3_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 70.7)), module, Comp::GRID_4_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 70.7)), module, Comp::GRID_5_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 70.7)), module, Comp::GRID_6_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 70.7)), module, Comp::GRID_7_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 70.7)), module, Comp::GRID_8_6_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 80.8)), module, Comp::GRID_1_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 80.8)), module, Comp::GRID_2_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 80.8)), module, Comp::GRID_3_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 80.8)), module, Comp::GRID_4_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 80.8)), module, Comp::GRID_5_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 80.8)), module, Comp::GRID_6_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 80.8)), module, Comp::GRID_7_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 80.8)), module, Comp::GRID_8_7_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (55.88, 90.9)), module, Comp::GRID_1_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (66.04, 90.9)), module, Comp::GRID_2_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (76.2, 90.9)), module, Comp::GRID_3_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (86.36, 90.9)), module, Comp::GRID_4_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (96.52, 90.9)), module, Comp::GRID_5_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (106.68, 90.9)), module, Comp::GRID_6_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (116.84, 90.9)), module, Comp::GRID_7_8_PARAM));
        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (127.0, 90.9)), module, Comp::GRID_8_8_PARAM));

        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 20.2)), module, Comp::L1_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 30.3)), module, Comp::L2_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 40.4)), module, Comp::L3_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 50.5)), module, Comp::L4_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 60.6)), module, Comp::L5_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 70.7)), module, Comp::L6_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 80.8)), module, Comp::L7_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<GreenLight>> (mm2px (Vec (142.24, 90.9)), module, Comp::L8_PARAM));

        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (55.88, 106.05)), module, Comp::SELECT_1_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (66.04, 106.05)), module, Comp::SELECT_2_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (76.2, 106.05)), module, Comp::SELECT_3_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (86.36, 106.05)), module, Comp::SELECT_4_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (96.52, 106.05)), module, Comp::SELECT_5_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (106.68, 106.05)), module, Comp::SELECT_6_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (116.84, 106.05)), module, Comp::SELECT_7_PARAM));
        addChild (createLightCentered<GridButtonRoundLight<RedLight>> (mm2px (Vec (127.0, 106.05)), module, Comp::SELECT_8_PARAM));

        addChild (createLightCentered<GridButtonLight<GreenLight>> (mm2px (Vec (142.24, 106.05)), module, Comp::SHIFT_PARAM));

        // mm2px(Vec(40.727, 18.936))
        addChild (createWidget<Widget> (mm2px (Vec (5.036, 15.782))));
        // mm2px(Vec(40.727, 18.936))
        addChild (createWidget<Widget> (mm2px (Vec (5.036, 35.982))));
    }
};

Model* modelLockhart = createModel<Lockhart, LockhartWidget> ("Lockhart");