/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPedalAudioProcessor::DistortionPedalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::mono(), true)
                     #endif
                       ),
#endif
    parameters(*this, nullptr, juce::Identifier("DistortionVst"), {
            // Distortion
            std::make_unique<juce::AudioParameterFloat>("drive-drive", "Distortion",  juce::NormalisableRange<float>(0.0f, 10.0f, 0.001f),  0.5f),
            std::make_unique<juce::AudioParameterFloat>("drive-range", "Range",  juce::NormalisableRange<float>(0.0f, 3000.0f, 0.001f),  300.0f),
            std::make_unique<juce::AudioParameterFloat>("drive-blend", "Blend",  juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f),  0.5f),
            std::make_unique<juce::AudioParameterFloat>("drive-volume", "Volume",  juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f),  1.0f),

            std::make_unique<juce::AudioParameterFloat>("drive-tone-high", "Tone High",  juce::NormalisableRange<float>(500.0f, 900.0f, 1.0f),  580.0f),
            std::make_unique<juce::AudioParameterFloat>("drive-tone-low", "Tone Low",  juce::NormalisableRange<float>(6000.0f, 10000.0f, 1.0f),  8000.0f),
            // Reverb
            std::make_unique<juce::AudioParameterFloat>("reverb-roomSize", "Room Size", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.5f),
            std::make_unique<juce::AudioParameterFloat>("reverb-damping", "Damping", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.5f),
            std::make_unique<juce::AudioParameterFloat>("reverb-wetLevel", "Wet Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.33f),
            std::make_unique<juce::AudioParameterFloat>("reverb-dryLevel", "Dry Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.4f),
            std::make_unique<juce::AudioParameterFloat>("reverb-width", "Width", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 1.0f),
            std::make_unique<juce::AudioParameterFloat>("reverb-freezeMode", "Freeze Mode", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.1f),
            // Delay
            std::make_unique<juce::AudioParameterFloat>("delay-maxDelayTime", "Max Delay Time", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 1.0f),
            std::make_unique<juce::AudioParameterFloat>("delay-delayTime", "Delay Time", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.5f),
            std::make_unique<juce::AudioParameterFloat>("delay-wetLevel", "Wet Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.1f),
            std::make_unique<juce::AudioParameterFloat>("delay-feedback", "Feedback", juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.1f),
        }),
        audioEngine(parameters)
{
    /*
    driveParameter = parameters.getRawParameterValue("drive-drive");
    rangeParameter = parameters.getRawParameterValue("drive-range");
    blendParameter = parameters.getRawParameterValue("drive-blend");
    volumeParameter = parameters.getRawParameterValue("drive-volume");

    roomSizeParameter = parameters.getRawParameterValue("reverb-roomSize");
    dampingParameter = parameters.getRawParameterValue("reverb-damping");
    wetLevelParameter = parameters.getRawParameterValue("reverb-wetLevel");
    dryLevelParameter = parameters.getRawParameterValue("reverb-dryLevel");
    widthParameter = parameters.getRawParameterValue("reverb-width");
    freezeModeParameter = parameters.getRawParameterValue("reverb-freezeMode");

    maxDelayTimeParameter = parameters.getRawParameterValue("delay-maxDelayTime");
    delayTimeParameter = parameters.getRawParameterValue("delay-delayTime");
    wetDelayLevelParameter = parameters.getRawParameterValue("delay-wetLevel");
    feedbackParameter = parameters.getRawParameterValue("delay-feedback");
    */

}

DistortionPedalAudioProcessor::~DistortionPedalAudioProcessor()
{
}

//==============================================================================
const juce::String DistortionPedalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionPedalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionPedalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionPedalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionPedalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionPedalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionPedalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionPedalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistortionPedalAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionPedalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistortionPedalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
   audioEngine.prepare({ sampleRate, (juce::uint32)samplesPerBlock, 2 });
}

void DistortionPedalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionPedalAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void DistortionPedalAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (totalNumInputChannels == 2) {
        // add the right (1) to the left (0)
        // store the sum in the left
      //  buffer.addFrom(0, 0, buffer, 1, 0, buffer.getNumSamples());

        // copy the combined left (0) to the right (1)
     //   buffer.copyFrom(1, 0, buffer, 0, 0, buffer.getNumSamples());
    }
 
    audioEngine.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool DistortionPedalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistortionPedalAudioProcessor::createEditor()
{
    return new DistortionPedalAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void DistortionPedalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
   // std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement("DistortionVst"));
    /*
    xml->setAttribute("drive-drive", (double)*driveParameter);
    xml->setAttribute("drive-range", (double)*rangeParameter);
    xml->setAttribute("drive-blend", (double)*blendParameter);
    xml->setAttribute("drive-volume", (double)*volumeParameter);

    xml->setAttribute("reverb-roomSize", (double)*roomSizeParameter);
    xml->setAttribute("reverb-damping", (double)*dampingParameter);
    xml->setAttribute("reverb-wetLevel", (double)*wetLevelParameter);
    xml->setAttribute("reverb-dryLevel", (double)*dryLevelParameter);
    xml->setAttribute("reverb-width", (double)*widthParameter);
    xml->setAttribute("reverb-freezeMode", (double)*freezeModeParameter);

    xml->setAttribute("delay-maxDelayTime", (double)*maxDelayTimeParameter);
    xml->setAttribute("delay-delayTime", (double)*delayTimeParameter);
    xml->setAttribute("delay-wetLevel", (double)*wetDelayLevelParameter);
    xml->setAttribute("delay-feedback", (double)*feedbackParameter);
    */
   // copyXmlToBinary(*xml, destData);
}

void DistortionPedalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
   // std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    //if (xmlState.get() != nullptr)
       // if (xmlState->hasTagName("DistortionVst"))
            /*
            *driveParameter = (float)xmlState->getDoubleAttribute("drive-drive", 1.0);
            *rangeParameter = (float)xmlState->getDoubleAttribute("drive-range", 1.0);
            *blendParameter = (float)xmlState->getDoubleAttribute("drive-blend", 1.0);
            *volumeParameter = (float)xmlState->getDoubleAttribute("drive-volume", 1.0);

            *roomSizeParameter = (float)xmlState->getDoubleAttribute("reverb-roomSize", 1.0);
            *dampingParameter = (float)xmlState->getDoubleAttribute("reverb-damping", 1.0);
            *wetLevelParameter = (float)xmlState->getDoubleAttribute("reverb-wetLevel", 1.0);
            *dryLevelParameter = (float)xmlState->getDoubleAttribute("reverb-dryLevel", 1.0);
            *widthParameter = (float)xmlState->getDoubleAttribute("reverb-width", 1.0);
            *freezeModeParameter = (float)xmlState->getDoubleAttribute("reverb-freezeMode", 1.0);

            *maxDelayTimeParameter = (float)xmlState->getDoubleAttribute("delay-maxDelayTime", 1.0);
            *delayTimeParameter = (float)xmlState->getDoubleAttribute("delay-delayTime", 1.0);
            *wetDelayLevelParameter = (float)xmlState->getDoubleAttribute("delay-wetLevel", 1.0);
            *feedbackParameter = (float)xmlState->getDoubleAttribute("delay-feedback", 1.0);
            
            */
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionPedalAudioProcessor();
}

