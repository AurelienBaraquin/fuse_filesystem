#!/bin/bash

echo "Installing dependencies..."

sudo apt-get update
sudo apt-get install -y libfuse-dev check make gcc perl cpanminus libfuse3-dev zlib1g-dev
cpanm --installdeps .

echo "Done."

echo "You can now build the project with 'make'."
