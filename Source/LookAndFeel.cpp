#include "LookAndFeel.h"

KnobLookAndFeel::KnobLookAndFeel()
{
    setColour(juce::Label::textColourId, juce::Colours::white);
    setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkgrey.darker());
    setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setColour(juce::TextButton::textColourOnId, juce::Colours::white);
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
    // Definindo a área do knob
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    auto knobRect = bounds.reduced(10.0f, 10.0f);

    // Adiciona uma sombra ao knob
    juce::DropShadow shadow(juce::Colours::black.withAlpha(0.5f), 8, juce::Point<int>(2, 2));
    shadow.drawForPath(g, juce::Path().addEllipse(knobRect));

    // Desenha o contorno do knob
    g.setColour(juce::Colours::grey);
    g.fillEllipse(knobRect);

    // Desenha o preenchimento gradiente do knob
    auto innerRect = knobRect.reduced(4.0f, 4.0f);
    auto gradient = juce::ColourGradient(juce::Colours::darkgrey.brighter(),
                                         innerRect.getCentreX(), innerRect.getY(),
                                         juce::Colours::darkgrey.darker(),
                                         innerRect.getCentreX(), innerRect.getBottom(),
                                         false);
    g.setGradientFill(gradient);
    g.fillEllipse(innerRect);

    // Desenha o arco de fundo
    auto center = bounds.getCentre();
    auto radius = bounds.getWidth() / 2.0f - 4.0f;
    auto lineWidth = 3.0f;
    auto arcRadius = radius - lineWidth / 2.0f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(center.x, center.y, arcRadius, arcRadius, 0.0f,
                                rotaryStartAngle, rotaryEndAngle, true);

    g.setColour(juce::Colours::darkgrey.darker());
    g.strokePath(backgroundArc, juce::PathStrokeType(lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::butt));

    // Desenha o arco de valor (indicador do knob)
    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    juce::Path valueArc;
    valueArc.addCentredArc(center.x, center.y, arcRadius, arcRadius, 0.0f,
                           rotaryStartAngle, toAngle, true);

    g.setColour(juce::Colours::orange);
    g.strokePath(valueArc, juce::PathStrokeType(lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::butt));

    // Desenha a "agulha" do knob
    auto pointerLength = radius * 0.6f;
    auto pointerThickness = 2.0f;

    juce::Path needle;
    needle.addRoundedRectangle(-pointerThickness * 0.5f, -arcRadius, pointerThickness, pointerLength, pointerThickness * 0.5f);
    needle.applyTransform(juce::AffineTransform::rotation(toAngle).translated(center.x, center.y));

    g.setColour(juce::Colours::black);
    g.fillPath(needle);
}

void KnobLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;
    
    g.setColour(backgroundColour);
    g.fillRoundedRectangle(buttonArea.toFloat(), edge);
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(buttonArea.toFloat().reduced(0.5f, 0.5f), edge, 1.0f);
}

juce::Font KnobLookAndFeel::getTextButtonFont (juce::TextButton&, int buttonHeight)
{
    return juce::Font(buttonHeight * 0.6f);
}
