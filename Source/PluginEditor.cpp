#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

    //==============================================================================
LuminousExciterAudioProcessorEditor::LuminousExciterAudioProcessorEditor (LuminousExciterAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (640, 300);
    
    exciterGroup.setText("Exciter");
    exciterGroup.addAndMakeVisible (exciterSlider);
    addAndMakeVisible(exciterGroup);
    
    luminousGroup.setText("Bias");
    luminousGroup.addAndMakeVisible (brightButton);
    luminousGroup.addAndMakeVisible(eightKButton);
    luminousGroup.addAndMakeVisible(twelveKButton);
    luminousGroup.addAndMakeVisible(sixteenKButton);
    addAndMakeVisible(luminousGroup);
    
    gainGroup.setText("Gain");
    gainGroup.addAndMakeVisible (gainSlider);
    addAndMakeVisible(gainGroup);
    
    addAndMakeVisible(meterL);
    addAndMakeVisible(meterR);
    
        // Aplica a aparência personalizada aos sliders
    exciterSlider.setLookAndFeel(&knobLookAndFeel);
    gainSlider.setLookAndFeel(&knobLookAndFeel);
    brightButton.setLookAndFeel(&knobLookAndFeel);
    eightKButton.setLookAndFeel(&knobLookAndFeel);
    twelveKButton.setLookAndFeel(&knobLookAndFeel);
    sixteenKButton.setLookAndFeel(&knobLookAndFeel);
    meterL.setLookAndFeel(&knobLookAndFeel);
    meterR.setLookAndFeel(&knobLookAndFeel);
    
    startTimer(60);
}

LuminousExciterAudioProcessorEditor::~LuminousExciterAudioProcessorEditor()
{
        // Restaura a aparência padrão dos sliders
    exciterSlider.setLookAndFeel(nullptr);
    gainSlider.setLookAndFeel(nullptr);
    
    stopTimer();
}

    //==============================================================================
void LuminousExciterAudioProcessorEditor::timerCallback()
{
    meterL.setLevel(audioProcessor.getRmsValue(0));
    meterR.setLevel(audioProcessor.getRmsValue(1));
    
    meterL.repaint();
    meterR.repaint();
}

void LuminousExciterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (Colors::background);
    
    exciterSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    exciterSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20 );
    exciterSlider.setRange (1.0f, 10.0f, 1.0f);
    exciterSlider.setNumDecimalPlacesToDisplay(1);
    
    brightButton.setButtonText ("Luminous");
    eightKButton.setButtonText ("8kHz");
    twelveKButton.setButtonText ("12kHz");
    sixteenKButton.setButtonText ("16kHz");
    
    gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20 );
    gainSlider.setRange (-60.0f, 24.0f, 1.0f );
    gainSlider.setNumDecimalPlacesToDisplay(1);
}

void LuminousExciterAudioProcessorEditor::resized()
{
    int margin = 10;
    int groupWidth = 180;
    int groupHeight = 180;
    
    exciterGroup.setBounds (margin, margin, groupWidth, groupHeight);
    exciterSlider.setBounds (margin, margin * 2, 150, 150);
    
    luminousGroup.setBounds (margin * 2 + groupWidth, margin * 7, groupWidth + 40, groupHeight - 60);
    brightButton.setBounds (margin, margin * 3, 200, 30);
    eightKButton.setBounds (margin, margin * 8, 60, 30);
    twelveKButton.setBounds (margin * 2 + 60, margin * 8, 60, 30);
    sixteenKButton.setBounds (margin * 3 + 120, margin * 8, 60, 30);
    
    gainGroup.setBounds (margin * 3 + (groupWidth * 2 + 40), margin, groupWidth, groupHeight);
    gainSlider.setBounds (margin, margin * 2, 150, 150);
    
    meterL.setBounds (margin, 265, getWidth() - margin * 2, 12);
    meterR.setBounds (margin, 280, getWidth() - margin * 2, 12);
}
