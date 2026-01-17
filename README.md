# Enhanced-Traffic-Simulator
## code pen preview - https://codepen.io/MD-Sirajul-Islam-the-builder/full/QwNXEKq

# Enhanced Traffic Simulator

Enhanced Traffic Simulator is a modular, extensible traffic simulation project designed to model and visualize vehicle flow and traffic behavior under realistic scenarios. It supports configurable road networks, multiple vehicle types and driving behaviors, traffic signals, and data collection for experiments and analysis.

This project simulates a traffic network where nodes represent intersections and edges represent roads with distances. The goal is to find the shortest path between a source and a destination, similar to real-world navigation systems.

## What the Video Shows
In the video, only one minimum shortest path is displayed. This is done to keep the visualization simple and easy to understand for viewers.

## Multiple Shortest Path Support
Although the video shows one path, the actual code can find multiple shortest paths. This is possible because I used an extra array to store alternative paths that have the same minimum distance.

## Why Multiple Paths Exist
In traffic networks, more than one route can have the same shortest distance. Instead of stopping after finding the first path, the algorithm continues checking other possible routes and stores them if their distance is equal to the minimum.

## Difference from Normal Shortest Path Algorithms
Normal shortest path algorithms usually return only one path. My enhanced approach keeps track of all optimal paths using an additional data structure, making it more suitable for traffic simulation.

Preview link - https://codepen.io/MD-Sirajul-Islam-the-builder/full/QwNXEKq



## Table of Contents

- [Features](#features)
- [Demo / Screenshots](#demo--screenshots)
- [Tech stack](#tech-stack)
- [Requirements](#requirements)
- [Installation](#installation)
- [Running the simulator](#running-the-simulator)
- [Configuration](#configuration)
- [Usage examples](#usage-examples)
- [Architecture overview](#architecture-overview)
- [Project structure](#project-structure)
- [Development and testing](#development-and-testing)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features

- Configurable road networks (grid, custom graphs, import from map formats)
- Multiple vehicle types with distinct dynamics (cars, buses, trucks)
- Customizable driver behavior models (aggressive, conservative, cooperative)
- Traffic signal control and timing strategies
- Real-time visualization and/or export of simulation traces
- Metrics and analytics: throughput, travel time, congestion heatmaps
- Extensible plugin/module architecture for new models and controllers
