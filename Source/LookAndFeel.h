#pragma once

#include <JuceHeader.h>

namespace Colors
{
    const juce::Colour background { juce::Colour(1, 1, 1) }; // Very light grey background
    const juce::Colour header { juce::Colour(50, 50, 50) }; // Dark grey header
    
    namespace Knob
    {
        const juce::Colour trackBackground { juce::Colour(220, 220, 220) }; // Light grey track background
        const juce::Colour trackActive { juce::Colour(150, 150, 150) }; // Medium grey track active
        const juce::Colour outline { juce::Colour(240, 240, 240) }; // Light grey outline
        const juce::Colour gradientTop { juce::Colour(180, 180, 180) }; // Medium grey gradient top
        const juce::Colour gradientBottom { juce::Colour(1, 1, 1) }; // Medium grey gradient bottom
        const juce::Colour dial { juce::Colour(10, 10, 10) }; // Almost black dial
        const juce::Colour dropShadow { juce::Colour(150, 150, 150) }; // Medium grey drop shadow
        const juce::Colour label { juce::Colour(60, 60, 60) }; // Dark grey label
        const juce::Colour textBoxBackground { juce::Colour(23, 23, 23) }; // Light grey text box background
        const juce::Colour value { juce::Colour(240, 240, 240) }; // Dark grey value text
        const juce::Colour caret { juce::Colour(60, 60, 60) }; // Dark grey caret
    }
    
    namespace Button
    {
        const juce::Colour text { juce::Colour(60, 60, 60) }; // Dark grey text
        const juce::Colour background { juce::Colour(21, 21, 21) }; // grey background
        const juce::Colour border { juce::Colour(180, 180, 180) }; // Medium grey border
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
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;
    
private:
    juce::DropShadow dropShadow { Colors::Knob::dropShadow, 6, { 0, 3 } };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobLookAndFeel)
};
