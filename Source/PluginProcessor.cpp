/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

//==============================================================================
LuminousExciterAudioProcessor::LuminousExciterAudioProcessor()

     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
                       params(apvts)
{
    auto* param = apvts.getParameter( "Gain" );
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
    
    param = apvts.getParameter( "Exciter" );
    exciterParam = dynamic_cast<juce::AudioParameterFloat*>(param);
    
    
}

LuminousExciterAudioProcessor::~LuminousExciterAudioProcessor()
{
}

//==============================================================================
const juce::String LuminousExciterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LuminousExciterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LuminousExciterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LuminousExciterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LuminousExciterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LuminousExciterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LuminousExciterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LuminousExciterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LuminousExciterAudioProcessor::getProgramName (int index)
{
    return {};
}

void LuminousExciterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LuminousExciterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    params.prepareToPlay(sampleRate);
    params.reset();
    
    rmsLevelLeft.reset(sampleRate);
    rmsLevelRight.reset(sampleRate);
    
    rmsLevelLeft.setCurrentAndTargetValue(-96.f);
    rmsLevelRight.setCurrentAndTargetValue(-96.f);
}

void LuminousExciterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LuminousExciterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void LuminousExciterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
        // Desabilita o modo de denormalização para evitar problemas de desempenho com números muito pequenos.
    juce::ScopedNoDenormals noDenormals;
    
        // Obtém o número total de canais de entrada.
    auto totalNumInputChannels  = getTotalNumInputChannels();
        // Obtém o número total de canais de saída.
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
        // Limpa os canais de saída que não estão sendo usados.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
        // Atualiza os parâmetros (supondo que `params.update()` atualize os parâmetros internos).
    params.update();
    
        // Obtém ponteiros para os dados de escrita dos canais esquerdo e direito do buffer.
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    
        // Loop através de cada amostra no buffer.
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
            // Suaviza os parâmetros (supondo que `params.smoothen()` ajuste os parâmetros internamente).
        params.smoothen();
        
            // Aplica o ganho aos dados dos canais esquerdo e direito.
        channelDataL[sample] *= params.gain;
        channelDataR[sample] *= params.gain;
        
            // Aplica distorção usando a função tanh ao canal esquerdo e direito.
        channelDataL[sample] = std::tanh(params.exciterAmount * channelDataL[sample]);
        channelDataR[sample] = std::tanh(params.exciterAmount * channelDataR[sample]);
    }
    
        // Calcula o nível RMS em decibéis para os canais esquerdo e direito.
    rmsLevelLeft  = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    rmsLevelRight = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
}

//==============================================================================
bool LuminousExciterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LuminousExciterAudioProcessor::createEditor()
{
    return new LuminousExciterAudioProcessorEditor (*this);
}

//==============================================================================
void LuminousExciterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    copyXmlToBinary(*apvts.copyState().createXml(), destData);
}

void LuminousExciterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement>xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName(apvts.state.getType()))
    {
        apvts.replaceState( juce::ValueTree::fromXml(*xml));
    }
}

float LuminousExciterAudioProcessor::getRmsValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return rmsLevelLeft.getCurrentValue();
    if (channel == 1)
        return rmsLevelRight.getCurrentValue();
    
    return 0.f;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LuminousExciterAudioProcessor();
}

