#!/usr/local/bin/io

DestinationFile := File clone openForUpdating(System args at(2))
DestinationFile truncateToSize(0)

