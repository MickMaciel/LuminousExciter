#pragma once

#include <JuceHeader.h>

const juce::ParameterID gainParamID ( "Gain", 1 );
const juce::ParameterID exciterParamID ( "Exciter", 1 );

class Parameters
{
public:
    
    Parameters(juce::AudioProcessorValueTreeState& apvts);
    
    static juce::AudioProcessorValueTreeState::ParameterLayout
    createParameterLayout();
    
    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void update() noexcept;
    void smoothen() noexcept;
    
    float gain = 0.0f;
    float exciterAmount = 1.0f;
    juce::AudioParameterFloat* exciterParam;
    
private:
    
    juce::AudioParameterFloat* gainParam;
    
    juce::LinearSmoothedValue<float> gainSmoother;
    juce::LinearSmoothedValue<float> exciterSmoother;
    
    
};
