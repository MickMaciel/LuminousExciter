#pragma once

#include <JuceHeader.h>

namespace Colors
{
    const juce::Colour background { };
    const juce::Colour header { };
    
    namespace Knob
    {
        const juce::Colour trackBackground { };
        const juce::Colour trackActive { };
        const juce::Colour outline { };
        const juce::Colour gradientTop { };
        const juce::Colour gradientBottom { };
        const juce::Colour dial { };
        const juce::Colour dropShadow { };
        const juce::Colour label { };
        const juce::Colour texBoxBackground { };
        const juce::Colour value { };
        const juce::Colour caret { };
        
    }
}

class KnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel();
    ~KnobLookAndFeel() override;
    
    static KnobLookAndFeel* get()
    {
        static KnobLookAndFeel instance;
        return  &instance;
    }
    
    void drawRotarySlider(juce::Graphics& g, 
                          int x, int y, int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
    
private:
    
    juce::DropShadow dropShadow { Colors::Knob::dropShadow, 6, { 0, 3 } };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobLookAndFeel)
};
