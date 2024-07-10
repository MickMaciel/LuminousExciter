#pragma once

#include <JuceHeader.h>

const juce::ParameterID gainParamId ( "Gain", 1 );
const juce::ParameterID exciterParamId ( "Exciter", 1 );

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
    
private:
    
    juce::AudioParameterFloat* gainParam;
    juce::AudioParameterFloat* exciterParam;
    juce::LinearSmoothedValue<float> gainSmoother;
    
    
};
