# Traffic System Plugin (Experimental)

Spare-time, work-in-progress project exploring a simple traffic system. Intended as a reference and proof of concept rather than a production-ready solution.

---

## Project Status

This project is currently in active experimentation and prototyping.  
Development is done during spare time and focuses on exploring technical concepts rather than delivering a finalized system.

Features, architecture, and APIs may change frequently.

---

## Scope and Goals

The main objectives of this repository are:

- Prototype a lightweight traffic system  
- Explore AI, pathing, and behavior logic  
- Test performance and scalability concepts  
- Validate design ideas for future projects or plugins  

This project is not intended to replace full-featured traffic or simulation frameworks.

---

## Chaos Modular Vehicle – Experimental Tests

This repository includes a series of experimental tests performed with Unreal Engine’s Chaos Modular Vehicle (CMV) plugin.

The goal of these tests was to explore:

* Runtime assembly of GeometryCollection-based vehicle parts
* Suspension constraint behavior and solver stability
* Cluster Union mass and inertia redistribution
* Breakable modular components (e.g., detachable bumper)
* Staged damage system (Intact → Deformed → Critical → Detached)
* Handling changes based on real mass/inertia shifts

These experiments focus on understanding how CMV differs from the classic Chaos Vehicle system, particularly in terms of topology changes, constraint tuning, and destruction-driven gameplay.

The code and setups are intended for research and learning purposes rather than production-ready vehicle implementations.

<img src="Docs/ModularVehicle.gif" width="600"/>

---

## Disclaimer

This repository is provided as-is.

- Code quality may vary  
- Some systems may be incomplete  
- Limited documentation in early stages  
- Not production-ready  

Use this project mainly as a learning resource, reference, or starting point for your own implementations.

---

## Contributions

Contributions, feedback, and ideas are welcome.  
However, this project prioritizes experimentation over long-term maintenance.

## Overview

The **Traffic System Plugin** provides a modular and extensible framework for managing AI-driven traffic in Unreal Engine.  
It is designed to simulate vehicle movement along splines, handle intersections, basic collision awareness, and traffic flow logic in a clean and reusable way.

The system focuses on:
- Clear separation between traffic logic and game-specific rules
- Plugin-level reusability across projects
- Blueprint-friendly workflows for designers
- Performance-aware runtime behavior

The plugin is intended for arcade, simulation, and cinematic use cases where predictable and controllable traffic behavior is required.

---

## Key Features

- Vehicle movement driven by spline-based paths
- Centralized traffic and intersection logic
- Collision detection helpers for vehicle spacing and stopping logic
- Runtime-safe logic suitable for packaged builds
- Blueprint-exposed controls for fast iteration
- Designed to work without replication by default

---

## Demo Content

The plugin includes **demo maps and Blueprint examples** to showcase the system in action.

You can find them in:
Plugins/TrafficSystem/Content/

These demo assets demonstrate:
- Basic traffic setup
- Vehicle movement along splines
- Intersection and stop logic
- Example Blueprint integration for designers

> Demo content is provided for reference and testing only and can be safely removed in production builds.

---

## Intended Usage

- Arcade games with controlled traffic behavior
- Simulation or visualization projects
- Cinematic scenes requiring deterministic vehicle motion
- Prototyping traffic logic without project-specific dependencies

---

## Notes

- This plugin is self-contained and does not rely on external plugins.
- Networking and replication are intentionally not included.
- The architecture allows easy extension with custom rules, signals, or vehicle types.

---

## License

Internal / Project-specific usage.  
