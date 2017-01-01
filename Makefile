CC=g++ -std=c++11
CFLAGS=-g -Wall -w
CPPFLAGS=-I include -I lib/include/
SFMLLIBS=-lsfml-graphics -lsfml-window -lsfml-system
BOX2DLIBS=-lBox2D


all: bin/testGUI

GUI: build/BMLearnMode.o build/BMNeat.o build/BMDriver.o build/BMTrack.o build/FileChooser.o build/MainWindow.o build/InfoWindow.o build/AgentsTreeModel.o build/AgentsTreeView.o

################################################################################
# Bin

bin/main: build/main.o build/AutoDriver.o build/NEAT/network.o build/NEAT/nnode.o build/NEAT/link.o build/NEAT/trait.o build/NEAT/gene.o build/NEAT/genome.o build/NEAT/innovation.o build/NEAT/organism.o build/NEAT/species.o build/NEAT/population.o build/NEAT/neat.o build/Camera.o build/RayVision.o build/SFMLRenderer.o build/SFMLDebugDraw.o build/ASpeedFactory.o build/EntsColListener.o build/Car.o build/CarTire.o build/RayVision.o build/TrackLink.o build/LearnLog.o build/Track.o build/tinyxml2.o build/NodeSpec.o build/CheckpointSpec.o build/Checkpoint.o build/SimMode.o build/LearnMode.o build/HumanDriver.o build/StartPos.o build/StartPosSpec.o build/TrackLinkSpec.o build/Node.o build/TrackSpec.o 
		$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -w $(BOX2DLIBS) $(SFMLLIBS) `pkg-config --libs gtkmm-3.0`

bin/testGUI: build/testGUI.o build/MainWindow.o build/InfoWindow.o build/AgentsTreeModel.o build/AgentsTreeView.o build/BMNeat.o build/BMDriver.o build/BMTrack.o build/Track.o build/tinyxml2.o build/SimMode.o build/NodeSpec.o build/CheckpointSpec.o build/Checkpoint.o build/StartPos.o build/StartPosSpec.o build/SFMLRenderer.o build/SFMLDebugDraw.o build/Camera.o build/Node.o build/TrackLinkSpec.o build/TrackLink.o build/BMLearnMode.o build/NEAT/network.o build/NEAT/nnode.o build/NEAT/link.o build/NEAT/trait.o build/NEAT/gene.o build/NEAT/genome.o build/NEAT/innovation.o build/NEAT/organism.o build/NEAT/species.o build/NEAT/population.o build/NEAT/neat.o build/EntsColListener.o build/TrackSpec.o build/LearnMode.o build/LearnLog.o build/ASpeedFactory.o build/Car.o build/CarTire.o build/RayVision.o build/AutoDriver.o build/SimController.o build/SFMLKeyboard.o build/HumanDriver.o
		$(CC) -pthread $(CFLAGS) $(CPPFLAGS) $^ -o $@ -w $(BOX2DLIBS) $(SFMLLIBS) `pkg-config --libs gtkmm-3.0`

################################################################################
# 

build/main.o: src/main.cpp include/GUI/MainWindow.h src/GUI/MainWindow.cpp
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/testGUI.o: src/testGUI.cpp 
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

################################################################################
# Controller

build/SimController.o: src/SimMode/SimController.cpp include/SimMode/SimController.h 
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

build/SFMLKeyboard.o: src/Controller/SFMLKeyboard.cpp include/Controller/SFMLKeyboard.h 
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`
		
################################################################################
# GUI

build/BMLearnMode.o: src/GUI/Bookmark/BMLearnMode.cpp include/GUI/Bookmark/BMLearnMode.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

build/BMNeat.o: src/GUI/Bookmark/BMNeat.cpp include/GUI/Bookmark/BMNeat.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

build/BMDriver.o: src/GUI/Bookmark/BMDriver.cpp include/GUI/Bookmark/BMDriver.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

build/BMTrack.o: src/GUI/Bookmark/BMTrack.cpp include/GUI/Bookmark/BMTrack.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

build/FileChooser.o: src/GUI/FileChooser.cpp include/GUI/FileChooser.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ `pkg-config --cflags gtkmm-3.0`

build/MainWindow.o: src/GUI/MainWindow.cpp include/GUI/MainWindow.h include/Util/tsqueue.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	`pkg-config --cflags gtkmm-3.0` 

build/InfoWindow.o: src/GUI/InfoWindow.cpp include/GUI/InfoWindow.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	`pkg-config --cflags gtkmm-3.0`

build/AgentsTreeModel.o: src/GUI/AgentsTreeModel.cpp include/GUI/AgentsTreeModel.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	`pkg-config --cflags gtkmm-3.0`

build/AgentsTreeView.o: src/GUI/AgentsTreeView.cpp include/GUI/AgentsTreeView.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	`pkg-config --cflags gtkmm-3.0`

################################################################################
# Drivers

build/AutoDriver.o: src/Drivers/AutoDriver.cpp include/Drivers/AutoDriver.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/HumanDriver.o: src/Drivers/HumanDriver.cpp include/Drivers/HumanDriver.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/ASpeedFactory.o: src/Drivers/ASpeedFactory.cpp include/Drivers/ASpeedFactory.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 


################################################################################
# SimMode

build/LearnLog.o: src/SimMode/LearnLog.cpp include/SimMode/LearnLog.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	-w $(SFMLLIBS)

build/LearnMode.o: src/SimMode/LearnMode.cpp include/SimMode/LearnMode.h include/SimMode/SimMode.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	-w $(SFMLLIBS) 

build/RaceMode.o: src/SimMode/RaceMode.cpp include/SimMode/RaceMode.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	-w $(SFMLLIBS)

build/SimMode.o: src/SimMode/SimMode.cpp include/SimMode/SimMode.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	-w $(SFMLLIBS)

################################################################################
# Renderer 

build/Camera.o: src/Renderer/Camera.cpp include/Renderer/Camera.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	-w $(SFMLLIBS)

build/SFMLRenderer.o: src/Renderer/SFMLRenderer.cpp include/Renderer/SFMLRenderer.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	-w $(SFMLLIBS)

################################################################################
# Entity 

build/Track.o: src/Entity/Track.cpp include/Entity/Track.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/EntsColListener.o: src/Entity/Listener/EntsColListener.cpp include/Entity/Listener/EntsColListener.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/TrackLine.o: src/Entity/TrackLine.cpp include/Entity/TrackLine.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/Cube.o: src/Entity/Cube.cpp include/Entity/Cube.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/TrackLink.o: src/Entity/TrackLink.cpp include/Entity/TrackLink.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/Car.o: src/Entity/Car.cpp include/Entity/Car.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/CarTire.o: src/Entity/CarTire.cpp include/Entity/CarTire.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/Checkpoint.o: src/Entity/Checkpoint.cpp include/Entity/Checkpoint.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/StartPos.o: src/Entity/StartPos.cpp include/Entity/StartPos.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/Node.o: src/Entity/Node.cpp include/Entity/Node.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/RayVision.o: src/Entity/RayVision.cpp include/Entity/RayVision.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

################################################################################

################################################################################
# Entity Spec

build/TrackSpec.o: src/Entity/Spec/TrackSpec.cpp include/Entity/Spec/TrackSpec.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/TrackLinkSpec.o: src/Entity/Spec/TrackLinkSpec.cpp include/Entity/Spec/TrackLinkSpec.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/StartPosSpec.o: src/Entity/Spec/StartPosSpec.cpp include/Entity/Spec/StartPosSpec.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/NodeSpec.o: src/Entity/Spec/NodeSpec.cpp include/Entity/Spec/NodeSpec.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

build/CheckpointSpec.o: src/Entity/Spec/CheckpointSpec.cpp include/Entity/Spec/CheckpointSpec.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

################################################################################

################################################################################
# Libs

build/SFMLDebugDraw.o: lib/src/SFMLDebugDraw.cpp lib/include/SFMLDebugDraw.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	

build/tinyxml2.o: lib/src/tinyxml2.cpp lib/include/tinyxml2.h
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@		

################################################################################
# NEAT

build/NEAT/neat: build/NEAT/neat.o build/NEAT/network.o build/NEAT/nnode.o build/NEAT/link.o build/NEAT/trait.o build/NEAT/gene.o build/NEAT/genome.o build/NEAT/innovation.o build/NEAT/organism.o build/NEAT/species.o build/NEAT/population.o build/NEAT/xor.o build/NEAT/neatmain.o build/NEAT/pole1.o

build/NEAT/neat.o: lib/src/NEAT/neat.cpp lib/include/NEAT/neat.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/network.o: lib/src/NEAT/network.cpp lib/include/NEAT/network.h lib/include/NEAT/neat.h build/NEAT/neat.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/nnode.o: lib/src/NEAT/nnode.cpp lib/include/NEAT/nnode.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/link.o: lib/src/NEAT/link.cpp lib/include/NEAT/link.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/trait.o: lib/src/NEAT/trait.cpp lib/include/NEAT/trait.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/gene.o: lib/src/NEAT/gene.cpp lib/include/NEAT/gene.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/genome.o: lib/src/NEAT/genome.cpp lib/include/NEAT/genome.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/innovation.o: lib/src/NEAT/innovation.cpp lib/include/NEAT/innovation.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/organism.o: lib/src/NEAT/organism.cpp lib/include/NEAT/organism.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/species.o: lib/src/NEAT/species.cpp lib/include/NEAT/species.h lib/include/NEAT/organism.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/population.o: lib/src/NEAT/population.cpp lib/include/NEAT/population.h lib/include/NEAT/organism.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

#build/experiments.o: src/experiments.cpp include/experiments.h include/network.h include/species.h
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/xor.o: lib/src/NEAT/xor.cpp lib/include/NEAT/xor.h lib/include/NEAT/network.h lib/include/NEAT/species.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/pole1.o: lib/src/NEAT/pole1.cpp lib/include/NEAT/pole1.h lib/include/NEAT/network.h lib/include/NEAT/species.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/NEAT/neatmain.o: lib/src/NEAT/neatmain.cpp lib/include/NEAT/neatmain.h lib/include/NEAT/neat.h lib/include/NEAT/population.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# END OF NEAT
################################################################################