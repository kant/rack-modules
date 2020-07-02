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

#pragma once

#include "IComposite.h"
#include "AudioMath.h"
#include <memory>
#include <vector>
#include <map>
#include <time.h>

namespace rack
{
    namespace engine
    {
        struct Module;
    }
} // namespace rack
using Module = ::rack::engine::Module;
using namespace rack;

template <class TBase>
class LockhartDescription : public IComposite
{
public:
    Config getParam (int i) override;
    int getNumParams() override;
};

/**
 * Complete Lockhart composite
 *
 * If TBase is WidgetComposite, this class is used as the implementation part of the KSDelay module.
 * If TBase is TestComposite, this class may stand alone for unit tests.
 */

template <class TBase>
class LockhartComp : public TBase
{
public:
    LockhartComp (Module* module) : TBase (module)
    {
    }

    LockhartComp() : TBase()
    {
    }

    virtual ~LockhartComp()
    {
    }

    /** Implement IComposite
     */
    static std::shared_ptr<IComposite> getDescription()
    {
        return std::make_shared<LockhartDescription<TBase>>();
    }

    enum ParamIds
    {
        GRID_1_1_PARAM,
        GRID_2_1_PARAM,
        GRID_3_1_PARAM,
        GRID_4_1_PARAM,
        GRID_5_1_PARAM,
        GRID_6_1_PARAM,
        GRID_7_1_PARAM,
        GRID_8_1_PARAM,
        GRID_1_2_PARAM,
        GRID_2_2_PARAM,
        GRID_3_2_PARAM,
        GRID_4_2_PARAM,
        GRID_5_2_PARAM,
        GRID_6_2_PARAM,
        GRID_7_2_PARAM,
        GRID_8_2_PARAM,
        GRID_1_3_PARAM,
        GRID_2_3_PARAM,
        GRID_3_3_PARAM,
        GRID_4_3_PARAM,
        GRID_5_3_PARAM,
        GRID_6_3_PARAM,
        GRID_7_3_PARAM,
        GRID_8_3_PARAM,
        GRID_1_4_PARAM,
        GRID_2_4_PARAM,
        GRID_3_4_PARAM,
        GRID_4_4_PARAM,
        GRID_5_4_PARAM,
        GRID_6_4_PARAM,
        GRID_7_4_PARAM,
        GRID_8_4_PARAM,
        GRID_1_5_PARAM,
        GRID_2_5_PARAM,
        GRID_3_5_PARAM,
        GRID_4_5_PARAM,
        GRID_5_5_PARAM,
        GRID_6_5_PARAM,
        GRID_7_5_PARAM,
        GRID_8_5_PARAM,
        GRID_1_6_PARAM,
        GIRD_2_6_PARAM,
        GRID_3_6_PARAM,
        GRID_4_6_PARAM,
        GRID_5_6_PARAM,
        GRID_6_6_PARAM,
        GRID_7_6_PARAM,
        GRID_8_6_PARAM,
        GRID_1_7_PARAM,
        GRID_2_7_PARAM,
        GRID_3_7_PARAM,
        GRID_4_7_PARAM,
        GRID_5_7_PARAM,
        GRID_6_7_PARAM,
        GRID_7_7_PARAM,
        GRID_8_7_PARAM,
        GRID_1_8_PARAM,
        GRID_2_8_PARAM,
        GRID_3_8_PARAM,
        GRID_4_8_PARAM,
        GRID_5_8_PARAM,
        GRID_6_8_PARAM,
        GRID_7_8_PARAM,
        GRID_8_8_PARAM,
        SELECT_1_PARAM,
        SELECT_2_PARAM,
        SELECT_3_PARAM,
        SELECT_4_PARAM,
        SELECT_5_PARAM,
        SELECT_6_PARAM,
        SELECT_7_PARAM,
        SELECT_8_PARAM,
        L1_PARAM,
        L2_PARAM,
        L3_PARAM,
        L4_PARAM,
        L5_PARAM,
        L6_PARAM,
        L7_PARAM,
        L8_PARAM,
        SHIFT_PARAM,
        NUM_PARAMS
    };
    enum InputIds
    {
        NUM_INPUTS
    };
    enum OutputIds
    {
        NUM_OUTPUTS
    };
    enum LightIds
    {
        GRID_1_1_LIGHT,
        GRID_2_1_LIGHT,
        GRID_3_1_LIGHT,
        GRID_4_1_LIGHT,
        GRID_5_1_LIGHT,
        GRID_6_1_LIGHT,
        GRID_7_1_LIGHT,
        GRID_8_1_LIGHT,
        GRID_1_2_LIGHT,
        GRID_2_2_LIGHT,
        GRID_3_2_LIGHT,
        GRID_4_2_LIGHT,
        GRID_5_2_LIGHT,
        GRID_6_2_LIGHT,
        GRID_7_2_LIGHT,
        GRID_8_2_LIGHT,
        GRID_1_3_LIGHT,
        GRID_2_3_LIGHT,
        GRID_3_3_LIGHT,
        GRID_4_3_LIGHT,
        GRID_5_3_LIGHT,
        GRID_6_3_LIGHT,
        GRID_7_3_LIGHT,
        GRID_8_3_LIGHT,
        GRID_1_4_LIGHT,
        GRID_2_4_LIGHT,
        GRID_3_4_LIGHT,
        GRID_4_4_LIGHT,
        GRID_5_4_LIGHT,
        GRID_6_4_LIGHT,
        GRID_7_4_LIGHT,
        GRID_8_4_LIGHT,
        GRID_1_5_LIGHT,
        GRID_2_5_LIGHT,
        GRID_3_5_LIGHT,
        GRID_4_5_LIGHT,
        GRID_5_5_LIGHT,
        GRID_6_5_LIGHT,
        GRID_7_5_LIGHT,
        GRID_8_5_LIGHT,
        GRID_1_6_LIGHT,
        GIRD_2_6_LIGHT,
        GRID_3_6_LIGHT,
        GRID_4_6_LIGHT,
        GRID_5_6_LIGHT,
        GRID_6_6_LIGHT,
        GRID_7_6_LIGHT,
        GRID_8_6_LIGHT,
        GRID_1_7_LIGHT,
        GRID_2_7_LIGHT,
        GRID_3_7_LIGHT,
        GRID_4_7_LIGHT,
        GRID_5_7_LIGHT,
        GRID_6_7_LIGHT,
        GRID_7_7_LIGHT,
        GRID_8_7_LIGHT,
        GRID_1_8_LIGHT,
        GRID_2_8_LIGHT,
        GRID_3_8_LIGHT,
        GRID_4_8_LIGHT,
        GRID_5_8_LIGHT,
        GRID_6_8_LIGHT,
        GRID_7_8_LIGHT,
        GRID_8_8_LIGHT,
        SELECT_1_LIGHT,
        SELECT_2_LIGHT,
        SELECT_3_LIGHT,
        SELECT_4_LIGHT,
        SELECT_5_LIGHT,
        SELECT_6_LIGHT,
        SELECT_7_LIGHT,
        SELECT_8_LIGHT,
        L1_LIGHT,
        L2_LIGHT,
        L3_LIGHT,
        L4_LIGHT,
        L5_LIGHT,
        L6_LIGHT,
        L7_LIGHT,
        L8_LIGHT,
        SHIFT_LIGHT,
        NUM_LIGHTS
    };

    static constexpr int controllerGridWidth = 8;
    static constexpr int controllerGridHeight = 8;
    static constexpr int gridPages = 4;
    static constexpr int maxLockhartPerExteranlController = 4;

    float sampleRate = 1.0f;
    float sampleTime = 1.0f;
    std::map<int, int> controllerGridMidiKey;

    /// index used for paramid, lightid and controllerGrid index
    static constexpr int getControllerGridIndex (int x, int y) noexcept
    {
        return x + y * controllerGridWidth;
    }

    void setSampleRate (float rate)
    {
        sampleRate = rate;
        sampleTime = 1.0f / rate;
    }

    // must be called after setSampleRate
    void init()
    {
        //TODO
    }

    void step() override;
};

template <class TBase>
inline void LockhartComp<TBase>::step()
{
    //test code for button led's
    for (auto i = 0; i < NUM_LIGHTS; ++i)
        TBase::lights[i].setBrightness (TBase::params[i].getValue());
}

template <class TBase>
int LockhartDescription<TBase>::getNumParams()
{
    return LockhartComp<TBase>::NUM_PARAMS;
}

template <class TBase>
IComposite::Config LockhartDescription<TBase>::getParam (int i)
{
    IComposite::Config ret = { 0.0f, 1.0f, 0.0f, " ", " ", 0.0f, 1.0f, 0.0f };
    // All parameters are simply trigger input buttons, with the same settings
    // these states need not be saved as used to trigger interal states
    // saved internally
    return ret;
}