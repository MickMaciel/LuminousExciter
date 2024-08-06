#pragma once

#include <JuceHeader.h>

namespace Colors
{
    namespace Knob
    {
        const juce::Colour trackBackground { juce::Colour(220, 220, 220) }; // Fundo do track em cinza claro
        const juce::Colour trackActive { juce::Colour(255, 127, 0) }; // Track ativo em laranja
        const juce::Colour outline { juce::Colour(240, 240, 240) }; // Contorno em cinza claro
        const juce::Colour gradientTop { juce::Colour(200, 200, 200) }; // Gradiente superior em cinza médio
        const juce::Colour gradientBottom { juce::Colour(1, 1, 1) }; // Gradiente inferior em cinza escuro
        const juce::Colour dial { juce::Colour(10, 10, 10) }; // Ponteiro quase preto
        const juce::Colour dropShadow { juce::Colour(150, 150, 150) }; // Sombra em cinza médio
        const juce::Colour label { juce::Colour(60, 60, 60) }; // Cor do rótulo em cinza escuro
        const juce::Colour textBoxBackground { juce::Colour(23, 23, 23) }; // Fundo da caixa de texto em cinza escuro
        const juce::Colour value { juce::Colour(240, 240, 240) }; // Cor do texto de valor em cinza claro
        const juce::Colour caret { juce::Colour(60, 60, 60) }; // Cor do cursor em cinza escuro
    }

    namespace Button
    {
        const juce::Colour text { juce::Colour(60, 60, 60) }; // Texto cinza escuro
        const juce::Colour background { juce::Colour(21, 21, 21) }; // Fundo cinza médio
        const juce::Colour border { juce::Colour(180, 180, 180) }; // Borda cinza médio
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
