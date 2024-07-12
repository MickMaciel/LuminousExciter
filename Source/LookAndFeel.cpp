#include "LookAndFeel.h"

KnobLookAndFeel::KnobLookAndFeel()
{
}

KnobLookAndFeel::~KnobLookAndFeel()
{
}

void KnobLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                       float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                                       juce::Slider& slider)
{
    auto radius = (float) juce::jmin(width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    g.setColour(juce::Colours::grey);
    g.fillEllipse(rx, ry, rw, rw);

    g.setColour(juce::Colours::black);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    juce::Path filledArc;
    filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.6);
    
    juce::ColourGradient gradient(juce::Colours::lightblue, centreX, centreY,
                                  juce::Colours::orange, centreX, centreY, true);
    gradient.addColour(0.5, juce::Colours::yellow);
    g.setGradientFill(gradient);
    g.fillPath(filledArc);

    juce::Path track;
    track.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.6);
    g.setColour(juce::Colours::darkgrey);
    g.strokePath(track, juce::PathStrokeType(2.0f));

    juce::Path p;
    auto pointerLength = radius * 0.6f;
    auto pointerThickness = 4.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(juce::Colours::lightblue);
    g.fillPath(p);
}
