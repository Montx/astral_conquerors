#!/bin/sh
cd submodules/Ogre3D

echo "Building Ogre3D..."
mkdir -p build && cd build && cmake .. || echo $? && read -p "\n Exit..."
