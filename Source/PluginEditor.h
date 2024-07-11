/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUIMeter.h"
#include "Parameters.h"

//==============================================================================
/**
*/
class LuminousExciterAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    LuminousExciterAudioProcessorEditor (LuminousExciterAudioProcessor&);
    ~LuminousExciterAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    LuminousExciterAudioProcessor& audioProcessor;
    
    juce::GroupComponent exciterGroup, luminousGroup, gainGroup;
    
    juce::Slider exciterSlider;
    juce::Slider gainSlider;
    juce::TextButton eightKButton;
    juce::TextButton twelveKButton;
    juce::TextButton sixteenKButton;
    juce::TextButton brightButton;
    
    GUI::GUIMeter meterL, meterR;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment
    {
        audioProcessor.apvts, gainParamId.getParamID(), gainSlider
    };

    juce::AudioProcessorValueTreeState::SliderAttachment exciterAttachment 
    {
        audioProcessor.apvts, exciterParamId.getParamID(), exciterSlider
    };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LuminousExciterAudioProcessorEditor)
};
