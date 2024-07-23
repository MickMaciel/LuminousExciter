#include "LookAndFeel.h"

KnobLookAndFeel::KnobLookAndFeel()
{
    setColour(juce::Label::textColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
    setColour(juce::TextButton::buttonColourId, Colors::Button::background);
    setColour(juce::TextButton::buttonOnColourId, Colors::Button::background.darker());
    setColour(juce::TextButton::textColourOffId, Colors::Button::text);
    setColour(juce::TextButton::textColourOnId, Colors::Button::text);
}

KnobLookAndFeel::~KnobLookAndFeel()
{
}

void KnobLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                       int x, int y, int width, int height,
                                       float sliderPosProportional,
                                       float rotaryStartAngle,
                                       float rotaryEndAngle,
                                       juce::Slider& slider)
{
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    auto knobRect = bounds.reduced(10.0f, 10.0f);
    auto path = juce::Path();
    
    path.addEllipse(knobRect);
    dropShadow.drawForPath(g, path);
    
    g.setColour(Colors::Knob::outline);
    g.fillEllipse(knobRect);
    
    auto innerRect = knobRect.reduced(2.0f, 2.0f);
    auto gradient = juce::ColourGradient(Colors::Knob::gradientTop,
                                         0.0f,
                                         innerRect.getY(),
                                         Colors::Knob::gradientBottom,
                                         0.0f,
                                         innerRect.getBottom(),
                                         false);
    g.setGradientFill(gradient);
    g.fillEllipse(innerRect);
    
    auto center = bounds.getCentre();
    auto radius = bounds.getWidth();
    auto lineWidth = 3.0f;
    auto archRadius = radius - lineWidth / 2.0f;
    
    juce::Path backgroundArch;
    backgroundArch.addCentredArc(center.x,
                                 center.y,
                                 archRadius,
                                 archRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    
    auto strokeType = juce::PathStrokeType(lineWidth,
                                           juce::PathStrokeType::curved,
                                           juce::PathStrokeType::rounded);
    g.setColour(Colors::Knob::trackBackground);
    g.strokePath(backgroundArch, strokeType);
    
    auto dialRadius = innerRect.getHeight() / 2.0f - lineWidth;
    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    juce::Point<float> dialStart(center.x, center.y);
    juce::Point<float> dialEnd(center.x + dialRadius * std::sin(toAngle),
                               center.y - dialRadius * std::cos(toAngle));
    
    juce::Path dialPath;
    dialPath.startNewSubPath(dialStart);
    dialPath.lineTo(dialEnd);
    
    g.setColour(Colors::Knob::dial);
    g.strokePath(dialPath, strokeType);
    
    if (slider.isEnabled())
    {
        juce::Path valueArch;
        valueArch.addCentredArc(center.x, center.y, archRadius, archRadius, 0.0f, rotaryStartAngle, toAngle, true);
        
        g.setColour(Colors::Knob::trackActive);
        g.strokePath(valueArch, strokeType);
    }
}

void KnobLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;
    
    g.setColour(backgroundColour);
    g.fillRoundedRectangle(buttonArea.toFloat(), edge);
    
    g.setColour(Colors::Button::border);
    g.drawRoundedRectangle(buttonArea.toFloat().reduced(0.5f, 0.5f), edge, 1.0f);
}

juce::Font KnobLookAndFeel::getTextButtonFont (juce::TextButton&, int buttonHeight)
{
    return juce::Font(buttonHeight * 0.6f);
}
