/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPedalAudioProcessorEditor::DistortionPedalAudioProcessorEditor (DistortionPedalAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts), reverbComponent(vts), delayComponent(vts), distortionComponent(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(distortionComponent);
    addAndMakeVisible(reverbComponent);
    addAndMakeVisible(delayComponent);


    setSize(400, 600);

}

DistortionPedalAudioProcessorEditor::~DistortionPedalAudioProcessorEditor()
{

}

//==============================================================================
void DistortionPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour::fromRGB(17, 17, 17));

    g.setColour(juce::Colours::white);
}

void DistortionPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds().reduced(5.0f, 5.0f);
    auto topArea = area.removeFromTop(300).reduced(5.0f, 5.0f);
    auto bottomArea = area.removeFromBottom(300);

    auto reverbArea = bottomArea.removeFromTop(200).reduced(5.0f, 5.0f);
    auto delayArea = bottomArea.removeFromBottom(100).reduced(5.0f, 5.0f);

    distortionComponent.setBounds(topArea);
    distortionComponent.setSize(topArea.getWidth(), topArea.getHeight());

    reverbComponent.setBounds(reverbArea);
    reverbComponent.setSize(reverbArea.getWidth(), reverbArea.getHeight());

    delayComponent.setBounds(delayArea);
    delayComponent.setSize(delayArea.getWidth(), delayArea.getHeight());


}
