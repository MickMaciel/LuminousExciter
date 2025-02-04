#include "Parameters.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts,
                          const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, gainParamID, gainParam);
    castParameter(apvts, exciterParamID, exciterParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout
Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                           gainParamID,
                                                           "Gain",
                                                           juce::NormalisableRange<float> { -60.0f, 24.0f },
                                                           0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                           exciterParamID,
                                                          "Exciter",
                                                           juce::NormalisableRange<float> { 1.0f, 10.0f },
                                                          1.0f));
    
    return layout;
}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    double duration = 0.02;
    gainSmoother.reset(sampleRate, duration);
    exciterSmoother.reset(sampleRate, duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    exciterAmount = 1.0f;
    
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    exciterSmoother.setCurrentAndTargetValue(exciterParam->get());
}


void Parameters::update() noexcept
{
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    exciterSmoother.setTargetValue(exciterParam->get());
}


void Parameters::smoothen() noexcept
{
    gain = gainSmoother.getNextValue();
    exciterAmount = exciterSmoother.getNextValue();
}


