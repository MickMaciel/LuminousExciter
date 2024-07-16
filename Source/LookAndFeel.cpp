#include "LookAndFeel.h"

KnobLookAndFeel::KnobLookAndFeel()
{
    setColour(juce::Label::textColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
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
                                         
    auto dialRadius = innerRect.getHeight() / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    juce::Point<float> dialStart(center.x, center.y);
    juce::Point<float> dialEnd(center.x + dialRadius * std::sin(toAngle),
                               center.y - dialRadius * std::cos(toAngle));
    
    juce::Path dialPath;
    dialPath.startNewSubPath(dialStart);
    dialPath.lineTo(dialEnd);
    
    g.setColour(Colors::Knob::dial);
    g.strokePath(dialPath, strokeType);
}
