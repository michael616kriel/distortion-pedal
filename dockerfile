FROM ubuntu

# Copy Juce for linux into container
COPY ./docker-build/juce-7.0.1-linux.zip ./

# Set working directory
WORKDIR ./

# Install dependencies
RUN apt-get update
RUN apt-get install -y build-essential wget git
RUN apt-get install -y unzip g++ libgtk-3-dev libfreetype6-dev libx11-dev libxinerama-dev libxrandr-dev libxcursor-dev mesa-common-dev libasound2-dev freeglut3-dev libxcomposite-dev libcurl4-openssl-dev
RUN apt-get install -y libwebkit2gtk-4.0-37 libwebkit2gtk-4.0-dev 

# Build linux app
RUN git clone https://github.com/michael616kriel/distortion-pedal.git
RUN unzip -l ./juce-7.0.1-linux.zip
RUN ls ./juce-7.0.1-linux.zip/JUCE
RUN cd ./distortion-pedal/Builds/LinuxMakefile
RUN make 